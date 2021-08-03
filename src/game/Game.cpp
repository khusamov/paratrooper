#include <user_interface.h>
#include "Game.h"
#include "Functions.h"

Game::Game(Screen *screen, Gamepad *gamepad) {
	this->screen = screen;
	this->gamepad = gamepad;
	this->bulletList = new BulletList;
	this->gun = new Gun(screen);
}

Game::~Game() {
	delete this->bulletList;
	delete this->gun;
}

void Game::begin() {
	this->screen->buffer->fillScreen(0);
	this->screen->buffer->setTextColor(1, 0);
	this->screen->buffer->setTextSize(1);
	this->screen->buffer->setCursor(0, 0, 2);
	this->screen->buffer->print("Paratrooper Game!");
	this->screen->update();
	delay(2000);
}

void Game::loop() {
	this->tick();
	this->draw();
	this->screen->update();
}

bool pointOffScreen(int x, int y, TFT_eSprite *buffer) {
	const int screenWidth = buffer->width();
	const int screenHeight = buffer->height();
	return (
		false
		|| x > screenWidth 
		|| x < 0 
		|| y > screenHeight 
		|| y < 0
	);
}

void Game::tick() {
	const int screenWidth = this->screen->buffer->width();
	const int screenHeight = this->screen->buffer->height();

	// Изменение состояния пушки.
	float gun_angle_speed = 0;
	if (this->gamepad->isButtonHold(LEFT_BUTTON_PIN)) {
		gun_angle_speed = PI / 40;
	}
	if (this->gamepad->isButtonHold(RIGHT_BUTTON_PIN)) {
		gun_angle_speed = -PI / 40;
	}
	this->gun->changeAngle(gun_angle_speed);
	
	// Создание пуль и бомб в момент нажатия на кнопки геймпада.
	if (this->gamepad->isButtonPress(FIRE_BUTTON_PIN) && fireCounter > 0) {
		tone(BUZZER_PIN, 120, 15);
		this->fireCounter--;
		this->bulletList->addBullet(this->bulletList->newBullet(Fire, this->gun->getAngle(), 15));
	}
	if (this->gamepad->isButtonPress(JUMP_BUTTON_PIN) && bombCounter > 0) {
		tone(BUZZER_PIN, 50, 30);
		this->bombCounter--;
		this->bulletList->addBullet(this->bulletList->newBullet(Bomb, this->gun->getAngle(), 15));
	}

	// Цикл по всем пулям: 
	// 1) перемещение пуль, 
	// 2) удаление пуль, которые вылетили за экран.
	Bullet *currentBullet = this->bulletList->firstBullet;
	while (currentBullet != nullptr) {
		// Передвигаем пулю на 3 единицы.
		currentBullet->radius += 3;
		// Запоминаем ссылку на следующую пулю. При удалении текущей пули эта ссылка будет недоступна, 
		// поэтому запоминать ссылку на следующую пулю надо перед удалением текущей пули.
		Bullet *nextBullet = currentBullet->next;
		// Проверяем, вылетела ли текущая пуля за пределы экрана или нет.
		int bullet_x1 = currentBullet->radius * cos(currentBullet->angle) + screenWidth / 2;
		int bullet_y1 = screenHeight - currentBullet->radius * sin(currentBullet->angle);
		if (pointOffScreen(bullet_x1, bullet_y1, this->screen->buffer)) {
			// Если вылетела, то удаляем пулю.
			this->bulletList->deleteBullet(currentBullet);
		}
		// Переходим к следующей пуле.
		currentBullet = nextBullet;
	}

	// Расчет вагонетки.
	ammuWagonX += ammuWagonSpeedX;
	if (ammuWagonX < screenWidth / 2 + 8 || ammuWagonX > screenWidth - 16) {
		ammuWagonSpeedX = -ammuWagonSpeedX;
	}
	if (ammuWagonX < screenWidth / 2 + 8) ammuWagonX = screenWidth / 2 + 8;
	if (ammuWagonX > screenWidth - 16) ammuWagonX = screenWidth - 16;
	if (ammuWagonX == screenWidth / 2 + 8 && ammuWagonSpeedX == -1 && (bombCounter < 30 || fireCounter < 100)) {
		bombCounter++;
		fireCounter++;
	}
}

void Game::draw() {
	const int screenWidth = this->screen->buffer->width();
	const int screenHeight = this->screen->buffer->height();

	this->screen->buffer->fillSprite(0);

	// Статусная строка.
	this->screen->buffer->setCursor(3, 0);
	this->screen->buffer->print(PSTR("Fire: "));
	this->screen->buffer->print(this->fireCounter);
	this->screen->buffer->setCursor(3, 15);
	this->screen->buffer->print(PSTR("Bomb: "));
	this->screen->buffer->print(this->bombCounter);
	this->screen->buffer->setCursor(3, 30);
	this->screen->buffer->print(PSTR("Free: "));
	this->screen->buffer->print(system_get_free_heap_size());

	this->gun->draw();
	// tv.bitmap(ammuWagonX, SCREEN_HEIGHT - 9, AmmuWagonImage);
	
	// Цикл отрисовки пуль на экране.
	Bullet *currentBullet = this->bulletList->firstBullet;
	while (currentBullet != nullptr) {
		switch (currentBullet->type) {
			case Fire: {
				int fireSize = 5;
				int bullet_x1 = currentBullet->radius * cos(currentBullet->angle) + screenWidth / 2;
				int bullet_y1 = screenHeight - currentBullet->radius * sin(currentBullet->angle);
				int bullet_x2 = (currentBullet->radius + fireSize) * cos(currentBullet->angle) + screenWidth / 2;
				int bullet_y2 = screenHeight - (currentBullet->radius + fireSize) * sin(currentBullet->angle);
				this->screen->buffer->drawLine(bullet_x1, bullet_y1, bullet_x2, bullet_y2, 3);
				break;
			}
			case Bomb: {
				int bombSize = 1;
				int bullet_x1 = (currentBullet->radius + bombSize) * cos(currentBullet->angle) + screenWidth / 2;
				int bullet_y1 = screenHeight - (currentBullet->radius + bombSize) * sin(currentBullet->angle);
				this->screen->buffer->drawCircle(bullet_x1, bullet_y1, bombSize, 2);
				break;
			}
		}
		currentBullet = currentBullet->next;
	}

	// Земля.
	this->screen->buffer->drawLine(0, screenHeight - 1, screenWidth - 1, screenHeight - 1, 1);
}