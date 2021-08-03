#include "Screen.h"

Screen::Screen() {
	this->tft = new TFT_eSPI;
	this->buffer = new TFT_eSprite(this->tft);
}

void Screen::begin() {
	this->tft->init();
	this->tft->setRotation(3);
	this->tft->fillScreen(TFT_BLACK);
	
	this->buffer->setColorDepth(2);

	uint16_t palette[4];
	palette[0] = TFT_BLACK;
	palette[1] = TFT_WHITE;
	palette[2] = TFT_DARKGREY;
	palette[3] = TFT_YELLOW;
	this->buffer->createPalette(palette);

	this->buffer->createSprite(this->tft->width(), this->tft->height());

	this->buffer->setTextColor(1, 0);
	this->buffer->setTextSize(1);
	this->buffer->setCursor(0, 0, 2);
}

void Screen::update() {
	this->buffer->pushSprite(0, 0);
}

void Screen::clear() {
	this->buffer->fillSprite(0);
	this->update();
}