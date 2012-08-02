#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "SDL/SDL_image.h"
#include <string>
#include <queue>
#include <map>
#include "sprite.h"

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812f 
#endif

class Renderer
{
	public:
		static void draw(std::queue<Sprite*>* sprites);
		static void init(int w, int h, std::string caption);
		static void toggleFullscreen();
		static void quit();
		static void deleteTexture(std::string path);
		static Image loadImage(std::string path);	
	private:
		static SDL_Surface* s_screen;
		static std::map<std::string,Image>* m_sprites;
};

#endif
