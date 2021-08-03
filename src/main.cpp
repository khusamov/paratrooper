#include <Arduino.h>
#include "gamepad/Gamepad.h"
#include "screen/Screen.h"
#include "ota/Ota.h"
#include "game/Game.h"

const char* ssid = "Khusamov";
const char* password = "9653911487";

Gamepad gamepad;
Screen screen;
Ota ota(&screen);
Game *game = nullptr;

void setup(void) {
	Serial.begin(115200);
	Serial.println("\n\n");
	screen.begin();

	ota.begin(ssid, password);
	ota.onStart([]() {
		delete game;
		game = nullptr;
	});

	gamepad.begin();

	game = new Game(&screen, &gamepad);
	game->begin();
}

void loop() {
	gamepad.tick();
	ota.loop();
	if (game) {
		game->loop();
	}
}