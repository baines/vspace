#ifndef _SPRITE_H_
#define _SPRITE_H_
#include <string>

typedef struct{
	float r;
	float g;
	float b;
}Colour;

const Colour RED    = { 1.0f,0.0f,0.0f };
const Colour BLUE   = { 0.0f,0.3f,1.0f };
const Colour GREEN  = { 0.1f,1.0f,0.1f };
const Colour YELLOW = { 1.0f,1.0f,0.1f };

typedef struct{
	unsigned int texture;
	int width;
	int height;
}Image;

class Sprite
{
	public:
		Sprite(std::string path, float x, float y, int w, int h ,float rotation = 0, float alpha = 1.0f);
		~Sprite();
		int width, height;
		float x, y, rotation, alpha;
		void setCrop(int X, int Y);
		void setColour(const Colour& c);
		void setColour(float r, float g, float b);
		
		static bool collision(Sprite* one, Sprite* two);
		
		friend class Renderer;
		
	protected:
		Image img;
		float texX, texY, texW, texH;
		Colour colour;
};

#endif
