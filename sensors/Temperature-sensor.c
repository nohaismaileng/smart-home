/* ================== PIN DEFINITIONS ================== */
#include <DHT.h>

#define DHTPIN 15       // OUT pin
#define DHTTYPE DHT11  // sensor type 

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float humidity = dht.readHumidity();       // humidity
  float temperature = dht.readTemperature(); // temp °C

  // if the reading failed 
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT11!");
    delay(1000);
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%  |  Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  delay(1000); 
}
