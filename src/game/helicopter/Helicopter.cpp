#include "Helicopter.h"

Helicopter::Helicopter(Screen *screen) : Object(screen) {}

void Helicopter::update() {
	const int screenWidth = this->screen->buffer->width();
	const int screenHeight = this->screen->buffer->height();

	this->x += this->vx;
	if (this->x > screenWidth) {
		this->vx *= -1;
	}
	if (this->x < 0) {
		this->vx *= -1;
	}
}

void Helicopter::draw() {
	const int screenWidth = this->screen->buffer->width();
	const int screenHeight = this->screen->buffer->height();
	
	this->screen->buffer->drawRect(this->x, this->y + 10, 15, 15, 1);
}