#pragma once
#include "../../screen/Screen.h"

class Object {
	public:
		Object(Screen *screen);
		void update();
		void draw();
	protected:
		Screen *screen = nullptr;
};