#pragma once

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include "../screen/Screen.h"

typedef std::function<void(void)> THandlerFunction;

class Ota {
	public:
		Ota(Screen *screen);
		void begin(const char* ssid, const char* password);
		void loop();
		void onStart(THandlerFunction fn);
		void onEnd(THandlerFunction fn);
	private:
		Screen *screen = nullptr;
		THandlerFunction _start_callback = nullptr;
		THandlerFunction _end_callback = nullptr;
		void defineArduinoOtaOnStartHandler();
		void defineArduinoOtaOnEndHandler();
		void defineArduinoOtaOnProgressHandler();
		void defineArduinoOtaOnErrorHandler();
};