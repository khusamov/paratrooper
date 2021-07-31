#pragma once

// https://github.com/GyverLibs/EncButton/issues/3
#define EB_DEB 30

#define EB_HOLD 0

#include <EncButton.h>
#include <PCF8574.h>
#include <Arduino.h>
#include "Constants.h"

/**
 * Контроллер ввода команд в игру.
 */
class Gamepad {
	public:
		Gamepad();
		~Gamepad();
		void begin();
		void tick();
		bool isButtonPress(int index);
		bool isButtonHold(int index);
		bool isButtonHolded(int index);
	private:
		PCF8574 *pcf20 = nullptr;
		EncButton<EB_TICK, VIRT_BTN> *buttons[8] {
			new EncButton<EB_TICK, VIRT_BTN>,
			new EncButton<EB_TICK, VIRT_BTN>,
			new EncButton<EB_TICK, VIRT_BTN>,
			new EncButton<EB_TICK, VIRT_BTN>,
			new EncButton<EB_TICK, VIRT_BTN>,
			new EncButton<EB_TICK, VIRT_BTN>,
			new EncButton<EB_TICK, VIRT_BTN>,
			new EncButton<EB_TICK, VIRT_BTN>
		};
};