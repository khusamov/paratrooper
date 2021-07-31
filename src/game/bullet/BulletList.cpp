#include "BulletList.h"

BulletList::BulletList() {}

BulletList::~BulletList() {
	this->clear();
}

Bullet *BulletList::newBullet(BulletType type, float angle, float radius) {
	return new Bullet(type, angle, radius);
}

Bullet *BulletList::addBullet(Bullet *newBullet) {
	if (this->firstBullet == nullptr) {
		this->firstBullet = newBullet;
		this->lastBullet = newBullet;
	} else {
		newBullet->prev = this->lastBullet;
		this->lastBullet->next = newBullet;
		this->lastBullet = newBullet;
	}
	return newBullet;
}

void BulletList::deleteBullet(Bullet *bullet) {
	if (this->firstBullet == this->lastBullet) {
		delete this->firstBullet;
		this->firstBullet = nullptr;
		this->lastBullet = nullptr;
	} else {
		if (bullet == this->firstBullet) {
			this->firstBullet = bullet->next;
			this->firstBullet->prev = nullptr;
		} else if (bullet == this->lastBullet) {
			this->lastBullet = bullet->prev;
			this->lastBullet->next = nullptr;
		} else {
			bullet->prev->next = bullet->next;
			bullet->next->prev = bullet->prev;
		}
		delete bullet;
	}
}

void BulletList::clear() {
	Bullet *currentBullet = this->firstBullet;
	while (currentBullet != nullptr) {
		Bullet *nextBullet = currentBullet->next;
		this->deleteBullet(currentBullet);
		currentBullet = nextBullet;
	}
}

unsigned int BulletList::count() {
	unsigned int result = 0;
	Bullet *currentBullet = this->firstBullet;
	while (currentBullet != nullptr) {
		currentBullet = currentBullet->next;
		result++;
	}
	return result;
}