#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

unsigned long previousMillis = 0;
const long interval = 2000;

float maxTemp = -100;
float minTemp = 100;

float maxHum = 0;
float minHum = 100;

void setup() {

  Serial.begin(115200);

  Serial.println();
  Serial.println("==================================");
  Serial.println(" SMART ENVIRONMENTAL MONITOR");
  Serial.println(" Decode Labs Internship Project");
  Serial.println("==================================");

  dht.begin();
}

void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {

    previousMillis = currentMillis;

    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("Sensor Read Failed");
      return;
    }

    if (temperature > maxTemp) maxTemp = temperature;
    if (temperature < minTemp) minTemp = temperature;

    if (humidity > maxHum) maxHum = humidity;
    if (humidity < minHum) minHum = humidity;

    String tempStatus;
    String humStatus;

    if (temperature > 35)
      tempStatus = "HOT";
    else if (temperature < 20)
      tempStatus = "COLD";
    else
      tempStatus = "NORMAL";

    if (humidity > 70)
      humStatus = "HUMID";
    else if (humidity < 30)
      humStatus = "DRY";
    else
      humStatus = "GOOD";

    Serial.println("----------------------------------");

    Serial.print("Temperature : ");
    Serial.print(temperature);
    Serial.println(" C");

    Serial.print("Humidity    : ");
    Serial.print(humidity);
    Serial.println(" %");

    Serial.print("Temp Status : ");
    Serial.println(tempStatus);

    Serial.print("Hum Status  : ");
    Serial.println(humStatus);

    Serial.println();

    Serial.print("Min Temp : ");
    Serial.print(minTemp);
    Serial.println(" C");

    Serial.print("Max Temp : ");
    Serial.print(maxTemp);
    Serial.println(" C");

    Serial.print("Min Hum  : ");
    Serial.print(minHum);
    Serial.println(" %");

    Serial.print("Max Hum  : ");
    Serial.print(maxHum);
    Serial.println(" %");

    Serial.println("----------------------------------");
  }
}
