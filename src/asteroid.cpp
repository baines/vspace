#include "asteroid.h"
#include <cstdlib>

Asteroid::Asteroid(float x, float y, int size) : Sprite("asteroid.png",x,y,size,size){
	float speed = ((rand()%150)+20)/ 100.0f;
	float dir = rand()%360;
	
	this->xVel = speed * sin(dir * M_PI / 180.0f);
	this->yVel = speed * cos(dir * M_PI / 180.0f);
	
	this->rotation = rand()%360;
	
	rotationSpeed = ((rand()%40)-20) / 10.0f;
	
	switch(rand()%4){
		case 0: colour = RED; break;
		case 1: colour = GREEN; break;
		case 2: colour = BLUE; break;
		case 3: colour = YELLOW; break;
	}
}

void Asteroid::update(float delta){
	this->x += xVel * 120.0f * delta;
	this->y -= yVel * 120.0f * delta;
	
	rotation += rotationSpeed * 120.0f * delta;
	
	if(x > 640){ x = 0;}
	if(x < 0){ x = 640;}
	if(y > 480){ y = 0;}
	if(y < 0){ y = 480;}
}
