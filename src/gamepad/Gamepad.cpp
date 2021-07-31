#include <Arduino.h>
#include "Gamepad.h"
#include "Constants.h"

#define ARRAY_LENGTH(array) sizeof array / sizeof array[0]

// volatile bool flag = false;
// void IRAM_ATTR onD3Interrupt();
// void IRAM_ATTR onD3Interrupt() {
// 	flag = true;
// }

Gamepad::Gamepad() {
	this->pcf20 = new PCF8574(PCF8574_ADDRESS);
}

Gamepad::~Gamepad() {
	delete this->pcf20;
}

void Gamepad::begin() {
	this->pcf20->begin();
	// pinMode(PCF8574_INT_PIN, INPUT_PULLUP);
	// attachInterrupt(digitalPinToInterrupt(PCF8574_INT_PIN), onD3Interrupt, FALLING);
}

void Gamepad::tick() {
	for (unsigned int i = 0; i < ARRAY_LENGTH(this->buttons); i++) {
		this->buttons[i]->tick(!this->pcf20->readButton(i));
	}
}

bool Gamepad::isButtonPress(int index) {
	return this->buttons[index]->isPress();
}

bool Gamepad::isButtonHold(int index) {
	return this->buttons[index]->isHold();
}

bool Gamepad::isButtonHolded(int index) {
	return this->buttons[index]->isHolded();
}