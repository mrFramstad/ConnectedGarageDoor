#include <Arduino.h>
#include <MyWiFi.h>

MyWiFi myWifi("Batman", "superman");
const int ledPin = D1;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");
  myWifi.connect();

  pinMode(D1, OUTPUT);
}

void loop() {
  myWifi.mqttKeepAlive();
  delay(5000);
  //myWifi.sendMessage();
}
