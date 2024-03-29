#include <Arduino.h>
#include <DHT.h>

#define DHTTYPE DHT11
#define RED_LED D7   //led warna merah
#define GREEN_LED D0 //led warna hijau

DHT dht(D4, DHTTYPE);

void setup()
{
  // put your setup code here, to run once:
  dht.begin();
  Serial.begin(115200);
  pinMode(RED_LED, OUTPUT); //atur pin-pin digital sebagai output
  pinMode(GREEN_LED, OUTPUT);
  Serial.println("Menggunakan DHT11");
}

void loop()
{
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) and isnan(t) and isnan(f))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  if (t <= 20)
  {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
  }
  else if (t > 20 && t < 40)
  {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
  }
  else
  {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
  }
}
