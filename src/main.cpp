#include <Arduino.h>
#include <MqttClient.h>
#include <IniFile.h>

MqttClient mqttClient;
const int ledPin = D1;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");
  mqttClient.connect();

  pinMode(D1, OUTPUT);
}

void loop() {
  mqttClient.mqttKeepAlive();
  delay(5000);
  mqttClient.sendMessage();
}
