#include "Arduino.h"
#include "Credentials.h"
#include "ESP8266WiFi.h"
#include "PubSubClient.h"
#include "MqttClient.h"


MqttClient::MqttClient() {
  ssid = SSID;
  pwd = WIFI_PWD;
  mqttBroker = MQTT_BROKER;
  mqttPort = MQTT_PORT;
  mqttUser = MQTT_USER;
  mqttPwd = MQTT_PWD;

  deviceId = "esp-" + String(ESP.getChipId(), HEX);

  mqtt = PubSubClient (wifiClient);
  mqtt.setServer(mqttBroker.c_str(), mqttPort);
}

String MqttClient::getDeviceId() {
  return deviceId;
}

void MqttClient::connect() {
  Serial.println("Entering initWIFI...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), pwd.c_str());

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.print("IP adress: ");
  Serial.println(WiFi.localIP());
  Serial.print("deviceId: ");
  Serial.println(deviceId);
}

void MqttClient::sendMessage() {
  Serial.println("Sending message...");
  String topic = "connectedGarageDoor/" + getDeviceId() + "/status";
  mqtt.publish(topic.c_str(), "1");
}

void MqttClient::reconnect() {
  do {
    Serial.println("Connecting to MQTT");
    delay(1000);
  } while (!mqtt.connect(getDeviceId().c_str(), mqttUser.c_str(), mqttPwd.c_str()));

  Serial.println("Connected to MQTT");
}

void MqttClient::mqttKeepAlive() {
  if (!mqtt.connected()) {
    reconnect();
  } else {
    mqtt.loop();
  }
}
