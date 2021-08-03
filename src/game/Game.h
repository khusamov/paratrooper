#pragma once
#include <Arduino.h>
#include "../screen/Screen.h"
#include "../gamepad/Gamepad.h"
#include "./game/bullet/BulletList.h"
#include "./game/gun/Gun.h"
#include "./game/helicopter/Helicopter.h"

class Game {
	public:
		Game(Screen *screen, Gamepad *gamepad);
		~Game();
		void begin();
		void tick();
		void draw();
		void loop();
	private:
		Screen *screen = nullptr;
		Gamepad *gamepad = nullptr;
		BulletList *bulletList = nullptr;
		Gun *gun = nullptr;
		Helicopter *helicopter = nullptr;
		float gun_angle = PI / 2;
		int fireCounter = 100;
		int bombCounter = 30;
		int ammuWagonX = 0;
		int ammuWagonSpeedX = 1;
};