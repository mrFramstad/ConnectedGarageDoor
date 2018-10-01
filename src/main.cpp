#include <Arduino.h>
#include <MqttClient.h>
#include <IniFile.h>

MqttClient mqttClient;
const int trigPin = D1;
const int echoPin = D2;
const int releePin = D5;
boolean isOpen = false;
long duration;
int distance;

void triggerGarageDoor () {
  Serial.println("triggering door");
  digitalWrite(releePin, HIGH);
  delay(250);
  digitalWrite(releePin, LOW);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("Entering callback.");
  triggerGarageDoor();
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");

  mqttClient.connect();

  Serial.println("trying to subscribe");
  mqttClient.subscribe("connectedGarageDoor/trigger");
  mqttClient.setCallback(callback);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(releePin, OUTPUT);
}

boolean isGarageDoorOpen () {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  return distance < 30;
}

void loop() {
  mqttClient.mqttKeepAlive();
  boolean currentStatus = isGarageDoorOpen();
  if (currentStatus != isOpen) {
     if (currentStatus) {
        mqttClient.sendMessage("open");
     } else {
        mqttClient.sendMessage("closed");
     }
     delay(1000);
  }
  isOpen = currentStatus;
}
