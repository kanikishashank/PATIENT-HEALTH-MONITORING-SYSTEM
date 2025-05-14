#define BLYNK_TEMPLATE_ID "TMPLxRANDOM123"
#define BLYNK_DEVICE_NAME "Health Monitor"
#define BLYNK_AUTH_TOKEN "a1b2c3d4e5f6g7h8i9j0k1l2"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "MyWiFi";
char pass[] = "MyWiFiPassword";
#define DHTPIN D4 // DHT11 sensor pin
#define DHTTYPE DHT11
#define HEARTBEAT_PIN A0 // Heartbeat sensor connected to A0
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
void sendSensorData() {
float h = dht.readHumidity();
float t = dht.readTemperature();
int heartbeat = analogRead(HEARTBEAT_PIN);
if (isnan(h) || isnan(t)) {
Serial.println("Failed to read from DHT sensor!");
return;
}
Blynk.virtualWrite(V0, t);
Blynk.virtualWrite(V1, h);
Blynk.virtualWrite(V2, heartbeat);
Serial.print("Temp: ");
Serial.print(t);
Serial.print(" °C, Humidity: ");
Serial.print(h);
Serial.print(" %, Heartbeat: ");
Serial.println(heartbeat);
}
void setup() {
Serial.begin(9600);
Blynk.begin(auth, ssid, pass);
dht.begin();
timer.setInterval(2000L, sendSensorData); // send every 2 seconds
}
void loop() {
Blynk.run();
timer.run();
}