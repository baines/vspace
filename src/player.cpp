#include "player.h"

Player::Player(float x, float y) : Sprite("ship.png",x,y,16,16){
	ammo = new std::list<Bullet*>;
	xVel = 0.0f;
	yVel = 0.3f;
}
Player::~Player(){
	while(!ammo->empty()){
		delete ammo->front();
		ammo->pop_front();
	}
	delete ammo;
}

bool Player::update(float speed, float delta){
	xVel += speed * sin(rotation * M_PI / 180.0f);
	yVel += speed * cos(rotation * M_PI / 180.0f);
	
	if(xVel > 4.0f) xVel = 4.0f;
	if(yVel > 4.0f) yVel = 4.0f;
	if(xVel < -4.0f) xVel = -4.0f;
	if(yVel < -4.0f) yVel = -4.0f;
	
	this->x += xVel * 120.0f * delta;
	this->y -= yVel * 120.0f * delta;
	
	if(!ammo->empty() && ammo->front()->ttl <= 0){
		delete ammo->front();
		ammo->pop_front();
	}
	
    for(std::list<Bullet*>::const_iterator it = ammo->begin(); it != ammo->end(); it++)
		(*it)->update(delta);

	if(x > 640){ x = 0; setColour(YELLOW); return true;}
	if(x < 0){ x = 640; setColour(BLUE); return true;}
	if(y > 480){ y = 0; setColour(GREEN); return true;}
	if(y < 0){ y = 480; setColour(RED); return true;}
	
	return false;
}

void Player::shoot(){
	ammo->push_back(new Bullet(x,y,xVel,yVel,rotation,colour));
	Sound::play("fire.wav");
}

const void Player::draw(std::queue<Sprite*>* sprites){
    for(std::list<Bullet*>::const_iterator it = ammo->begin(); it != ammo->end(); it++)
    	sprites->push(*it);
}

void Player::reset(){
	x = 320;
	y = 260;
	xVel = 0.0f;
	yVel = 0.3f;
	setColour(1.0f,1.0f,1.0f);
}
