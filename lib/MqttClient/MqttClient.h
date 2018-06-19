#ifndef MqttClient_h
#define MqttClient_h

#include "Arduino.h"
#include "ESP8266WiFi.h"
#include "PubSubClient.h"

class MqttClient {
	public:
    MqttClient();
    void connect();
    String getDeviceId();
		void sendMessage();
		void mqttKeepAlive();

	private:
    String ssid;
    String pwd;
    String deviceId;
		String mqttBroker;
		int mqttPort;
		String mqttUser;
		String mqttPwd;
		WiFiClient wifiClient;
		PubSubClient mqtt;

		void reconnect();
};
#endif
