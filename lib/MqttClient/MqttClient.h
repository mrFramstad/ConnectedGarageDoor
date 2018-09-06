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
		void sendMessage(String status);
		void mqttKeepAlive();
		boolean subscribe(String topic);
		void setCallback(std::function<void(char*, uint8_t*, unsigned int)> callback);

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
