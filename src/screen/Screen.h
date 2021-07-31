#pragma once
#include <Arduino.h>
#include <TFT_eSPI.h>

class Screen {
	public:
		Screen();
		void begin();
		void update();
		void clear();
		TFT_eSprite *buffer = nullptr;
	private:
		TFT_eSPI *tft = nullptr;
};