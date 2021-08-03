#include "Ota.h"

Ota::Ota(Screen *screen) {
	this->screen = screen;
}

void Ota::loop() {
	ArduinoOTA.handle();
}

void Ota::onStart(THandlerFunction fn) {
	this->_start_callback = fn;
	this->defineArduinoOtaOnStartHandler();
}

void Ota::onEnd(THandlerFunction fn) {
	this->_end_callback = fn;
	this->defineArduinoOtaOnEndHandler();
}

void Ota::begin(const char* ssid, const char* password) {
	Serial.println("Connect to WiFi...");
	this->screen->buffer->println("Connect to WiFi...");
	this->screen->update();

	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);
	
	while (WiFi.waitForConnectResult() != WL_CONNECTED) {
		Serial.println("Connection Failed! Rebooting...");
		this->screen->buffer->println("Connection Failed! Rebooting...");
		this->screen->update();
		delay(5000);
		ESP.restart();
	}
	
	ArduinoOTA.setHostname("Paratrooper Game Console");

	this->defineArduinoOtaOnStartHandler();
	this->defineArduinoOtaOnEndHandler();
	this->defineArduinoOtaOnProgressHandler();
	this->defineArduinoOtaOnErrorHandler();
	
	ArduinoOTA.begin();

	Serial.println("Ready");
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
	this->screen->buffer->println("Ready");
	this->screen->buffer->print("IP: ");
	this->screen->buffer->println(WiFi.localIP());
	this->screen->update();
	delay(2000);
}

void Ota::defineArduinoOtaOnStartHandler() {
	Screen *screen = this->screen;
	THandlerFunction _start_callback = this->_start_callback;
	ArduinoOTA.onStart([screen, _start_callback]() {
		if (_start_callback) {
			_start_callback();
		}
		String type;
		if (ArduinoOTA.getCommand() == U_FLASH) {
			type = "sketch";
		} else { // U_FS
			type = "filesystem";
		}

		// NOTE: if updating FS this would be the place to unmount FS using FS.end()
		Serial.println("Start updating " + type + ":");

		screen->clear();
		screen->buffer->setTextColor(1, 0);
		screen->buffer->setTextSize(1);
		screen->buffer->setCursor(0, 0);
		screen->buffer->println("Start updating " + type);
		screen->update();
	});
}

void Ota::defineArduinoOtaOnEndHandler() {
	Screen *screen = this->screen;
	THandlerFunction _end_callback = this->_end_callback;
	ArduinoOTA.onEnd([screen, _end_callback]() {
		Serial.println("\nEnd");
		screen->buffer->println("\nEnd");
		screen->update();
		if (_end_callback) {
			_end_callback();
		}
	});
}

void Ota::defineArduinoOtaOnProgressHandler() {
	Screen *screen = this->screen;
	ArduinoOTA.onProgress([screen](unsigned int progress, unsigned int total) {
		Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
		screen->buffer->setCursor(0, 0);
		screen->buffer->println();
		screen->buffer->print("Progress: ");
		screen->buffer->println(progress);
		screen->buffer->print("Total: ");
		screen->buffer->println(total);
		screen->update();
	});
}

void Ota::defineArduinoOtaOnErrorHandler() {
	Screen *screen = this->screen;
	ArduinoOTA.onError([screen](ota_error_t error) {
		Serial.printf("Error[%u]: ", error);
		if (error == OTA_AUTH_ERROR) {
			Serial.println("Auth Failed");
			screen->buffer->println("\nAuth Failed");
		} else if (error == OTA_BEGIN_ERROR) {
			Serial.println("Begin Failed");
			screen->buffer->println("\nBegin Failed");
		} else if (error == OTA_CONNECT_ERROR) {
			Serial.println("Connect Failed");
			screen->buffer->println("\nConnect Failed");
		} else if (error == OTA_RECEIVE_ERROR) {
			Serial.println("Receive Failed");
			screen->buffer->println("\nReceive Failed");
		} else if (error == OTA_END_ERROR) {
			Serial.println("End Failed");
			screen->buffer->println("\nEnd Failed");
		}
		screen->update();
	});
}