# Mesafe Sensörlü LED Kontrol Projesi

Bu proje, HC-SR04 mesafe sensörü kullanarak LED'lerin parlaklığını mesafeye göre kontrol eden bir Arduino uygulamasıdır.

## Donanım Gereksinimleri

- Arduino Uno
- HC-SR04 Ultrasonik Mesafe Sensörü
- 6 adet LED
- 6 adet 220 ohm direnç
- Breadboard
- Jumper kablolar

## HC-SR04 Sensör Özellikleri

- Çalışma voltajı: 5V DC
- Çalışma akımı: 15mA
- Ölçüm açısı: 15 derece
- Ölçüm aralığı: 2cm - 400cm
- Ölçüm hassasiyeti: 0.3cm
- Ölçüm sıklığı: 40Hz (25ms)
- Tetikleme sinyali: 10μS TTL pulse
- Echo sinyali: TTL level signal, time proportional to distance

## Bağlantılar

### HC-SR04 Sensör Bağlantıları
- VCC -> Arduino 5V
- TRIG -> Arduino pin 9
- ECHO -> Arduino pin 10
- GND -> Arduino GND

### LED Bağlantıları
- LED 1 -> Arduino pin 8 (220 ohm direnç ile)
- LED 2 -> Arduino pin 7 (220 ohm direnç ile)
- LED 3 -> Arduino pin 6 (220 ohm direnç ile)
- LED 4 -> Arduino pin 4 (220 ohm direnç ile)
- LED 5 -> Arduino pin 3 (220 ohm direnç ile)
- LED 6 -> Arduino pin 2 (220 ohm direnç ile)

## Çalışma Prensibi

Proje, mesafe sensöründen gelen veriye göre LED'lerin parlaklığını kademeli olarak kontrol eder:

- Mesafe 5 cm'de: Maksimum parlaklık (255)
- Mesafe 10 cm'de: %80 parlaklık (204)
- Mesafe 15 cm'de: %60 parlaklık (153)
- Mesafe 20 cm'de: %40 parlaklık (102)
- Mesafe 25 cm'de: %20 parlaklık (51)
- Mesafe 30 cm ve üzeri: LED'ler sönük (0)

## Özellikler

- Mesafe ölçümü: 5 cm - 45 cm arası
- LED parlaklığı: Mesafeye göre 0-255 arası değişken
- Ölçüm sıklığı: 100ms
- Serial monitörde mesafe ve parlaklık değeri gösterimi

## Kurulum

1. Arduino IDE'yi açın
2. Kodu yükleyin
3. Bağlantıları yapın
4. Serial monitörü açın (9600 baud)
5. Kodu Arduino'ya yükleyin

## Notlar

- LED'ler tersten bağlanmıştır (8'den 2'ye doğru)
- Mesafe ölçümü için ses hızı (340 m/s) kullanılmaktadır
- Sensörün ölçüm hassasiyeti 0.3cm'dir
- Sensörün önünde engel olmamasına dikkat edin
- Ölçüm sırasında sensörün sabit durması önemlidir 