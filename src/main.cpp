#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

// LED pini
const int ledPin = 7;  // LED pini
const int buzzerPin1 = 3;  // Pasif buzzer pini
const int buzzerPin2 = 4;  // HSD aktif buzzer pini
const int buttonPin = 2;  // Buton pini

// HC-SR04 Sensör pinleri
const int trigPin = 9;
const int echoPin = 10;

// Alarm değişkenleri
unsigned long previousAlarmTime = 0;
unsigned long previousLedTime = 0;
unsigned long alarmStartTime = 0;  // Alarm başlangıç zamanı
int alarmState = 0;
int ledState = 0;
bool alarmActive = false;  // Alarm durumu
bool alarmSounding = false;  // Alarm çalma durumu
int lastButtonState = HIGH;  // Butonun son durumu
unsigned long lastDebounceTime = 0;  // Son debounce zamanı
const unsigned long debounceDelay = 50;  // Debounce süresi
const unsigned long alarmDuration = 10000;  // Alarm süresi (10 saniye)

// Alarm tonları
const int alarmTones[] = {2000, 1500, 1000, 1500};  // Daha melodik tonlar
const int toneCount = sizeof(alarmTones) / sizeof(alarmTones[0]);

void setup() {
  // LED pinini çıkış olarak ayarla
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  // Buzzer pinlerini çıkış olarak ayarla
  pinMode(buzzerPin1, OUTPUT);
  pinMode(buzzerPin2, OUTPUT);
  digitalWrite(buzzerPin1, LOW);
  digitalWrite(buzzerPin2, LOW);
  
  // Buton pinini giriş olarak ayarla ve pull-up direnci aktif et
  pinMode(buttonPin, INPUT_PULLUP);
  
  // HC-SR04 pinlerini ayarla
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Serial haberleşmeyi başlat
  Serial.begin(9600);
  Serial.println("Alarm Sistemi Başladı!");
  Serial.println("Buton basılırsa alarm aktif/pasif olacak");
}

// Mesafe ölçme fonksiyonu
float measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;
  
  return distance;
}

void enterSleep() {
  Serial.println("Uyku moduna geçiliyor...");
  delay(100);  // Serial mesajın gönderilmesi için kısa bekleme
  
  // Tüm çıkışları düşük seviyeye çek
  digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin1, LOW);
  digitalWrite(buzzerPin2, LOW);
  noTone(buzzerPin1);
  
  // Düşük güç tüketimli uyku modu
  set_sleep_mode(SLEEP_MODE_IDLE);
  sleep_enable();
  
  while (!alarmActive) {
    sleep_mode();  // Uyku moduna geç
    
    // Buton durumunu kontrol et
    if (digitalRead(buttonPin) == LOW) {
      delay(50);  // Debounce için kısa bekleme
      if (digitalRead(buttonPin) == LOW) {
        alarmActive = true;
        Serial.println("Uyandı - Alarm Aktif!");
        delay(300);  // Butonun tekrar basılmasını önle
      }
    }
  }
  
  sleep_disable();  // Uyku modunu devre dışı bırak
}

void loop() {
  float distance = measureDistance();
  unsigned long currentTime = millis();
  
  // Buton durumunu kontrol et
  int buttonState = digitalRead(buttonPin);
  
  // Buton basıldığında alarm durumunu değiştir
  if (buttonState == LOW && lastButtonState == HIGH) {
    delay(50); // Debounce için kısa bekleme
    if (digitalRead(buttonPin) == LOW) { // Buton hala basılı mı kontrol et
      if (alarmActive) {  // Alarm aktifse pasife çevir ve uyku moduna geç
        alarmActive = false;
        alarmSounding = false;  // Alarmı durdur
        digitalWrite(ledPin, LOW);  // LED'i söndür
        Serial.println("Alarm Pasif - Uyku Moduna Geçiliyor...");
        enterSleep();
      } else {  // Alarm pasifse aktif et
        alarmActive = true;
        digitalWrite(ledPin, HIGH);  // LED'i yak
        Serial.println("Alarm AKTIF!");
      }
      delay(300); // Butonun tekrar basılmasını önle
    }
  }
  lastButtonState = buttonState;
  
  // Alarm aktif değilse LED'i söndür ve çık
  if (!alarmActive) {
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin1);
    digitalWrite(buzzerPin2, LOW);
    return;
  }
  
  // Mesafe kontrolü ve alarm sesi
  if (distance < 60) {  // Mesafe 60cm'den az ise
    if (!alarmSounding) {
      alarmStartTime = currentTime;  // Alarm başlangıç zamanını kaydet
      alarmSounding = true;
    }
    
    // Alarm süresi kontrolü
    if (currentTime - alarmStartTime < alarmDuration) {
      // Alarm sesi ve LED
      if (currentTime - previousAlarmTime >= 200) {
        previousAlarmTime = currentTime;
        
        tone(buzzerPin1, alarmTones[alarmState]);
        digitalWrite(buzzerPin2, alarmState % 2 == 0 ? HIGH : LOW);
        digitalWrite(ledPin, alarmState % 2 == 0 ? HIGH : LOW);  // LED'i alarm ile senkronize et
        
        alarmState = (alarmState + 1) % toneCount;
      }
      
      Serial.print("Mesafe: ");
      Serial.print(distance);
      Serial.println(" cm - ALARM!");
    } else {
      alarmSounding = false;
      noTone(buzzerPin1);
      digitalWrite(buzzerPin2, LOW);
      digitalWrite(ledPin, HIGH);  // Alarm bittiğinde LED'i yak
      alarmState = 0;
    }
  } else {
    if (alarmSounding && currentTime - alarmStartTime < alarmDuration) {
      // Alarm süresi dolmamışsa çalmaya devam et
      if (currentTime - previousAlarmTime >= 200) {
        previousAlarmTime = currentTime;
        
        tone(buzzerPin1, alarmTones[alarmState]);
        digitalWrite(buzzerPin2, alarmState % 2 == 0 ? HIGH : LOW);
        digitalWrite(ledPin, alarmState % 2 == 0 ? HIGH : LOW);  // LED'i alarm ile senkronize et
        
        alarmState = (alarmState + 1) % toneCount;
      }
    } else {
      alarmSounding = false;
      noTone(buzzerPin1);
      digitalWrite(buzzerPin2, LOW);
      digitalWrite(ledPin, HIGH);  // Alarm bittiğinde LED'i yak
      alarmState = 0;
    }
    Serial.print("Mesafe: ");
    Serial.print(distance);
    Serial.println(" cm - Alarm Aktif");
  }
  
  delay(50);
}
