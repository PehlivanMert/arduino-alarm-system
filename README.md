# Ultrasonik Mesafe Sensörlü Alarm Sistemi

Bu proje, HC-SR04 ultrasonik mesafe sensörü kullanarak bir alarm sistemi oluşturur. Sistem, belirli bir mesafenin altında bir nesne algıladığında alarm çalar ve LED uyarısı verir.

## Özellikler

- HC-SR04 ultrasonik mesafe sensörü ile mesafe ölçümü
- 60 cm mesafe eşiği
- 10 saniye süren alarm
- Melodik alarm tonları (2000Hz, 1500Hz, 1000Hz, 1500Hz)
- Çift buzzer sistemi (pasif ve aktif)
- LED durum göstergesi
- Düşük güç tüketimli uyku modu
- Buton ile alarm kontrolü
- Uzun batarya ömrü

## Donanım Gereksinimleri

- Arduino (Uno, Nano veya benzeri)
- HC-SR04 Ultrasonik Mesafe Sensörü
- 2 adet Buzzer (1 pasif, 1 aktif)
- LED
- Buton
- Bağlantı kabloları
- Breadboard (isteğe bağlı)
- Batarya (önerilen: 10000mAh Li-ion)

## Bağlantılar

### HC-SR04 Sensör
- VCC -> Arduino 5V
- GND -> Arduino GND
- TRIG -> Arduino Pin 9
- ECHO -> Arduino Pin 10

### Buzzerlar
- Pasif Buzzer -> Arduino Pin 3
- Aktif Buzzer -> Arduino Pin 4

### LED
- Anot (+) -> Arduino Pin 7
- Katot (-) -> 220Ω direnç -> Arduino GND

### Buton
- Bir ucu -> Arduino Pin 2
- Diğer ucu -> Arduino GND

## Çalışma Prensibi

1. **Uyku Modu**
   - Sistem başlangıçta uyku modundadır
   - LED sönük durumda
   - Düşük güç tüketimi

2. **Aktif Mod**
   - Butona basıldığında sistem aktif olur
   - LED sürekli yanık durumda
   - Mesafe sürekli ölçülür

3. **Alarm Durumu**
   - 60 cm'den yakın mesafede nesne algılandığında:
     - Alarm 10 saniye boyunca çalar
     - LED alarm ile senkronize yanıp söner
     - Melodik tonlar sırayla çalınır
   - Nesne uzaklaşsa bile alarm süresi dolana kadar çalmaya devam eder
   - Alarm süresi bittiğinde LED tekrar sürekli yanık duruma geçer

4. **Kontrol**
   - Buton ile alarm aktif/pasif yapılabilir
   - Pasif modda sistem uyku moduna geçer

## Güç Tüketimi ve Batarya Ömrü

### Güç Tüketimi
- Uyku modunda: ~0.1mA
- Aktif modda: ~20mA
- Alarm çalarken: ~50mA

### Batarya Ömrü Hesaplaması (10000mAh Batarya ile)
1. **Günlük Tüketim (12 saat aktif + 12 saat uyku)**
   - Aktif mod: 20mA × 12 saat = 240mAh
   - Uyku modu: 0.1mA × 12 saat = 1.2mAh
   - Toplam günlük tüketim: 241.2mAh/gün

2. **Çalışma Süresi**
   - 10000mAh ÷ 241.2mAh/gün = 41.46 gün
   - Yaklaşık 41-42 gün kesintisiz çalışma

### Notlar
- Hesaplanan süre alarm çalma durumlarını içermez
- Gerçek kullanımda süre şu faktörlere bağlı olarak değişebilir:
  - Alarm çalma sıklığı ve süresi
  - Bataryanın yaşlanması
  - Ortam sıcaklığı
  - Batarya verimliliği

## Notlar

- Mesafe ölçümü 2-400 cm arasında yapılabilir
- Alarm tonları 200ms aralıklarla değişir
- Sistem 50ms'de bir mesafe kontrolü yapar
- Buton debounce süresi 50ms'dir

## Geliştirme

Projeyi geliştirmek için yapılabilecekler:
- Farklı alarm tonları eklenebilir
- Alarm süresi değiştirilebilir
- Mesafe eşiği ayarlanabilir
- Farklı LED efektleri eklenebilir
- Güç tüketimi daha da optimize edilebilir
- Batarya ömrünü uzatmak için:
  - Uyku modu süresini artırabilirsiniz
  - Daha büyük kapasiteli batarya kullanabilirsiniz
  - Güç tüketimini optimize edebilirsiniz
