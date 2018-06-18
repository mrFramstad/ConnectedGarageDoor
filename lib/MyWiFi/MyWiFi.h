#ifndef MyWiFi_h
#define MyWiFi_h

#include "Arduino.h"
#include "ESP8266WiFi.h"
#include "PubSubClient.h"

class MyWiFi {
	public:
    MyWiFi(String s, String p);
    void connect();
    String getDeviceId();
		void sendMessage();
		void mqttKeepAlive();

	private:
    String ssid;
    String pwd;
    String deviceId;
		WiFiClient wifiClient;
		PubSubClient mqtt;

		void reconnect();
};
#endif
