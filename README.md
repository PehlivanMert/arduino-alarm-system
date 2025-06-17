# Arduino Alarm Sistemi

Bu proje, Arduino tabanlı bir hareket algılama ve alarm sistemidir. HC-SR04 ultrasonik mesafe sensörü kullanarak yakındaki hareketleri algılar ve alarm durumunda sesli ve görsel uyarılar verir.

## 🎯 Projenin Amacı

Bu alarm sistemi, aşağıdaki durumlarda kullanılmak üzere tasarlanmıştır:
- Ev ve işyeri güvenliği
- Değerli eşyaların korunması
- Kapı ve pencere güvenliği
- Hareket algılama gerektiren diğer güvenlik uygulamaları

## 💡 Özellikler

- Ultrasonik mesafe sensörü ile hassas hareket algılama
- Çift buzzer sistemi (pasif ve aktif) ile yüksek sesli uyarı
- LED ile görsel uyarı
- Düşük güç tüketimli uyku modu
- Tek buton ile kolay kontrol
- Serial monitör üzerinden durum takibi

## 🛠️ Donanım Gereksinimleri

- Arduino Uno/Nano
- HC-SR04 Ultrasonik Mesafe Sensörü
- 2x Buzzer (1x Pasif, 1x Aktif)
- 1x LED
- 1x Buton
- 1x 220Ω Direnç (LED için)
- 1x 10kΩ Direnç (Buton için)
- Bağlantı kabloları
- Breadboard

## 📋 Bağlantı Şeması

```
Arduino Pinleri:
- Pin 2  -> Buton (GND'ye 10kΩ pull-down direnci ile)
- Pin 3  -> Pasif Buzzer
- Pin 4  -> Aktif Buzzer
- Pin 7  -> LED (220Ω direnç ile)
- Pin 9  -> HC-SR04 TRIG
- Pin 10 -> HC-SR04 ECHO
- 5V     -> HC-SR04 VCC
- GND    -> HC-SR04 GND, Buton, LED, Buzzerlar
```

## ⚙️ Teknik Özellikler

- Algılama mesafesi: 60cm
- Alarm süresi: 10 saniye (kesintisiz)
- Uyku modu: SLEEP_MODE_IDLE
- Buton debounce süresi: 50ms
- LED yanıp sönme sıklığı: 100ms
- Alarm sesi değişim sıklığı: 200ms
- Serial haberleşme hızı: 9600 baud

## 🔄 Çalışma Prensibi

1. **Başlangıç Durumu:**
   - Sistem ilk açıldığında alarm pasif durumda başlar
   - LED sönük durumda
   - Buzzerlar kapalı

2. **Alarm Aktifleştirme:**
   - Butona basıldığında alarm aktif olur
   - LED sürekli yanar
   - Sistem mesafe ölçümüne başlar

3. **Alarm Durumu:**
   - Mesafe 60cm'den az olduğunda:
     - Alarm tetiklenir
     - LED yanıp söner
     - Buzzerlar 10 saniye boyunca kesintisiz çalar
     - Serial monitörde uyarı mesajı görüntülenir
   - 10 saniye sonra alarm otomatik olarak durur
   - Yeni bir nesne algılanana kadar alarm çalmaz

4. **Uyku Modu:**
   - Alarm aktifken butona basıldığında:
     - Alarm pasif olur
     - Sistem uyku moduna geçer
     - Tüm çıkışlar kapanır
   - Uyku modundan çıkış:
     - Butona basıldığında sistem uyanır
     - Alarm tekrar aktif olur

## 💪 Faydaları

1. **Güvenlik:**
   - Hassas hareket algılama
   - Anında uyarı sistemi
   - Görsel ve sesli bildirimler

2. **Enerji Verimliliği:**
   - Düşük güç tüketimli uyku modu
   - Akıllı güç yönetimi
   - Uzun pil ömrü

3. **Kullanım Kolaylığı:**
   - Tek buton kontrolü
   - Basit kurulum
   - Kolay bakım

4. **Özelleştirilebilirlik:**
   - Mesafe hassasiyeti ayarlanabilir
   - Ses ve ışık modları değiştirilebilir
   - Farklı sensörler eklenebilir


## ⚠️ Dikkat Edilmesi Gerekenler

1. **Kurulum:**
   - Bağlantıları doğru yapın
   - Dirençleri unutmayın
   - Güç kaynağını kontrol edin

2. **Kullanım:**
   - Mesafe sensörünü temiz tutun
   - Butonun düzgün çalıştığından emin olun
   - Serial monitörü kontrol edin

3. **Bakım:**
   - Düzenli sensör temizliği
   - Bağlantı kontrolü
   - Pil durumu takibi
