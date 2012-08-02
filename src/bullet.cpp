#include "bullet.h"

Bullet::Bullet(float x, float y, float xVel, float yVel, float dir, Colour& c) : Sprite("bullet.png",x,y,4,4){
	this->xVel = xVel + BULLET_SPEED * sin(dir * M_PI / 180.0f);
	this->yVel = yVel + BULLET_SPEED * cos(dir * M_PI / 180.0f);
	
	ttl = 60;
	
	setColour(c);
}

void Bullet::update(float delta){
	this->x += xVel * 120.0f * delta;
	this->y -= yVel * 120.0f * delta;
	
	if(x > 640){ x = 0;}
	if(x < 0){ x = 640;}
	if(y > 480){ y = 0;}
	if(y < 0){ y = 480;}
	
	ttl -= 125.0f * delta;
}
