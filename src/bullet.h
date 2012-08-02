#ifndef _BULLET_H_
#define _BULLET_H_

#include "sprite.h"
#include <cmath>

#define BULLET_SPEED 5.0f

class Bullet : public Sprite {
	public:
		Bullet(float x, float y, float xVel, float yVel, float dir, Colour& c);
		~Bullet(){};
		void update(float delta);
		float ttl;
	private:
		float xVel;
		float yVel;
};

#endif		
