#include "Gun.h"
#include "Constants.h"

Gun::Gun(Screen *screen) : Object(screen) {}

void Gun::draw() {
	const int screenWidth = this->screen->buffer->width();
	const int screenHeight = this->screen->buffer->height();
	int gun_length1 = 15;
	int gun_x1 = screenWidth / 2;
	int gun_y1 = screenHeight;
	int gun_x2 = gun_length1 * cos(this->angle) + screenWidth / 2;
	int gun_y2 = screenHeight - gun_length1 * sin(this->angle);
	this->screen->buffer->drawLine(gun_x1, gun_y1, gun_x2, gun_y2, 1);
}

float Gun::getAngle() {
	return this->angle;
}

void Gun::changeAngle(float angle) {
	this->angle += angle;
	if (this->angle >= 2 * PI) this->angle = 0;
}