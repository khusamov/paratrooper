#pragma once
#include <Arduino.h>
#include "../object/Object.h"

class Helicopter : Object {
	public:
		Helicopter(Screen *screen);
		~Helicopter();
		void update();
		void draw();
	private:
		int x = 0;
		int y = 0;
		int vx = 3;
};