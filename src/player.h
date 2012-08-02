#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "sprite.h"
#include "bullet.h"
#include "sound.h"
#include <list>
#include <queue>
#include <cmath>

class Player : public Sprite {
	public:
		Player(float x, float y);
		~Player();
		bool update(float speed, float delta);
		void shoot();
		const void draw(std::queue<Sprite*>* sprites);
		std::list<Bullet*>* ammo;
		void reset();
	private:
		float xVel;
		float yVel;
};

#endif		
