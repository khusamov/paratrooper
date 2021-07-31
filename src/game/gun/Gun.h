#pragma once
#include <Arduino.h>
#include "../../screen/Screen.h"
#include "../object/Object.h"

/**
 * Пушка.
 */
class Gun : Object {
	public:
		Gun(Screen *screen);
		void update();
		void draw();
		float getAngle();
		void changeAngle(float angle);
	private:
		float angle = PI / 2;
};