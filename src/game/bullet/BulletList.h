#pragma once

#include "Bullet.h"

class BulletList {
	public:
		Bullet *firstBullet = nullptr;
		Bullet *lastBullet = nullptr;
		BulletList();
		~BulletList();
		Bullet *newBullet(BulletType type, float angle = 0, float radius = 0);
		Bullet *addBullet(Bullet *bullet);
		void deleteBullet(Bullet *bullet);
		void clear();
		unsigned int count();
	private:
};