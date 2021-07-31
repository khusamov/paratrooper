#include "Screen.h"

Screen::Screen() {
	this->tft = new TFT_eSPI;
	this->buffer = new TFT_eSprite(this->tft);
}

void Screen::begin() {
	this->tft->init();
	this->tft->setRotation(3);
	this->tft->fillScreen(TFT_BLACK);
	
	this->buffer->setColorDepth(1);
	this->buffer->createSprite(this->tft->width(), this->tft->height());

	this->buffer->setTextColor(TFT_WHITE, TFT_BLACK);
	this->buffer->setTextSize(1);
	this->buffer->setCursor(0, 0, 2);
}

void Screen::update() {
	this->buffer->pushSprite(0, 0);
}

void Screen::clear() {
	this->buffer->fillSprite(TFT_BLACK);
	this->update();
}