// Menambahkan library sensor DHT
#include <SimpleDHT.h>
#include <LiquidCrystal_I2C.h>

// Mendefinsikan alamat pin
#define RED_LED D7   //led warna merah
#define GREEN_LED D0 //led warna hijau
#define pinDHT D4 // SD3 pin signal sensor DHT

// Deklarasi variabel global
byte temperature = 0;
byte humidity = 0;

// Deklarasi instance object constructor DHT11
SimpleDHT11 dht11(pinDHT);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Membuat kustom karakter derajat
// https://maxpromer.github.io/LCD-Character-Creator/
byte derajat[] = {
 B01110,
 B10001,
 B10001,
 B10001,
 B01110,
 B00000,
 B00000,
 B00000
};

void setup() {
 // Mengatur baudrate serial Monitor
 Serial.begin(115200);
 // Mengatur mode pin LED sebagai output
 pinMode(RED_LED, OUTPUT);
 pinMode(GREEN_LED, OUTPUT);
 // Mengatur mode pin DHT sebagai input
 pinMode(pinDHT, INPUT);

 lcd.begin(); // Inisialisasi LCD
 lcd.clear(); // Bersihkan layar
 lcd.createChar(0, derajat);
 lcd.setCursor(0, 0); // Kursor X,Y
 lcd.print("Humidity"); // Tampilkan ke layar
 lcd.setCursor(0, 1);
 lcd.print("Sensor");

 // Tunda untuk tampil selama 5 detik
 delay(5000);
 // Bersihkan layat
 lcd.clear();
}
void loop() {
 // Memanggil fungsi suhu dan kelembaban
 // yang akan dipanggil berulang-ulang
 KelembabanSuhu();
}
void KelembabanSuhu()
{
 int err = SimpleDHTErrSuccess;
 if ((err = dht11.read(&temperature, &humidity, NULL)) != 
SimpleDHTErrSuccess)
 {
 Serial.print("Pembacaan DHT11 gagal, err=");
 Serial.println(err);
 delay(1000);
 return;
 }
 // Tampilkan hasil pembacaan sensor ke serial monitor
 digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
 Serial.print("Sample OK: ");
 Serial.print((int)temperature);
 Serial.print(" *C, ");
 Serial.print((int)humidity);
 Serial.println(" H");
 // Tampilkan hasil pembacaan sensor ke LCD
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("Temp: " + String((int)temperature));
 lcd.write(0); // Simbol derajat
 lcd.print("C ");
 lcd.setCursor(0, 1);
 lcd.print("Humi: " + String((int)humidity) + "H");
 delay(1500);
 // Tunda pembacaan setiap 2 detik
 // kemampuan baca DHT11 idealnya adalah 1,5 detik
 delay(2000);
}
