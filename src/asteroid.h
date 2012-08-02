#ifndef _ASTEROID_H_
#define _ASTEROID_H_

#include "sprite.h"
#include <cmath>

class Asteroid : public Sprite {
	public:
		Asteroid(float x, float y, int size);
		~Asteroid(){};
		void update(float delta);
	private:
		float xVel;
		float yVel;
		float rotationSpeed;
};

#endif		
