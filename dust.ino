#include <ESP8266WiFi.h>
#include <KiwisIoT.h>

// WiFi details
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// KiwisIoT topic
const char* topic = "YOUR_TOPIC_ID";

// MQ-5 sensor
#define MQ5_PIN A0

KiwisIoT kiwisiot(ssid, password, topic);

void setup() {
  Serial.begin(115200);

  pinMode(MQ5_PIN, INPUT);

  Serial.println("Smart Gas Monitoring System");

  kiwisiot.begin();
}

void loop() {
  kiwisiot.run();

  int gasValue = analogRead(MQ5_PIN);

  Serial.print("MQ-5 Gas Sensor Value: ");
  Serial.println(gasValue);

  // Send sensor value to KiwisIoT
  kiwisiot.send("0", gasValue);

  if (gasValue > 500) {
    Serial.println("WARNING: Gas Level HIGH!");
  } else {
    Serial.println("STATUS: NORMAL");
  }

  delay(2000);
}
