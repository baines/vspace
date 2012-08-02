#include "sprite.h"
#include "renderer.h"

Sprite::Sprite(std::string path, float x, float y, int w, int h, float rotation, float alpha)
{	
	width = w;
	height = h;
	this->x = x;
	this->y = y;
	this->alpha = alpha;
	this->rotation = rotation;
	colour.r = colour.g = colour.b = 1.0f;
	
	img = Renderer::loadImage(path);
	
	texX = texY = 0.0f;
	texW = texH = 1.0f;
}

Sprite::~Sprite(){}

void Sprite::setColour(const Colour& c){
	colour = c;
}

void Sprite::setColour(float r, float g, float b){
	colour.r = r;
	colour.g = g;
	colour.b = b;
}

void Sprite::setCrop(int X, int Y){
	texX = (float)X / (float)img.width;
	texY = (float)Y / (float)img.height;
	
	texW = ((float)width / (float)img.width) + texX;
	texH = ((float)height / (float)img.height) + texY;
}

bool Sprite::collision(Sprite* one, Sprite* two){
	if((one->x + one->width / 2 < two->x - two->width / 2) ||
	   (one->x - one->width / 2 > two->x + two->width / 2) ||
	   (one->y + one->height /2 < two->y - two->width / 2) ||
	   (one->y - one->height /2 > two->y + two->width / 2))
		return false;
	else if((one->colour.r == two->colour.r) &&
			(one->colour.g == two->colour.g) &&
			(one->colour.b == two->colour.b))
		return true;
	else
		return false;
}
