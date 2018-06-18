#include "Arduino.h"
#include "ESP8266WiFi.h"
#include "PubSubClient.h"
#include "MyWiFi.h"

MyWiFi::MyWiFi(String s, String p) {
  ssid = s;
  pwd = p;
  deviceId = "esp-" + String(ESP.getChipId(), HEX);

  mqtt = PubSubClient (wifiClient);
  mqtt.setServer("broker.hivemq.com", 1883);
}

String MyWiFi::getDeviceId() {
  return deviceId;
}

void MyWiFi::connect() {
  Serial.println("Entering initWIFI...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), pwd.c_str());

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP adress: ");
  Serial.println(WiFi.localIP());
  Serial.print("deviceId: ");
  Serial.println(deviceId);
}

void MyWiFi::sendMessage() {
  Serial.println("Sending message...");
  String topic = "ndc/" + getDeviceId() + "led";
  mqtt.publish(topic.c_str(), "1");
}

void MyWiFi::reconnect() {
  do {
    Serial.println("Connecting to MQTT");
    delay(1000);
  } while (!mqtt.connect(getDeviceId().c_str()));

  Serial.println("Connected to MQTT");
}

void MyWiFi::mqttKeepAlive() {
  if (!mqtt.connected()) {
    reconnect();
  } else {
    mqtt.loop();
  }
}
