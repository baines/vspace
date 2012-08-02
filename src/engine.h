#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "SDL/SDL.h"
#include "SDL/SDL_thread.h"
#include "renderer.h"
#include "gamestate.h"
#include "sprite.h"
#include <iostream>
#include <string>
#include <queue>
#include <map>

class Engine
{
	public:
		static void init();
		static void run();
		static void exit();
		static bool running;
	private:
		static void handleInput(bool toggle);
		static void update(float delta);
		static void draw();
		static std::queue<Sprite*>* sprites;
		static std::map<std::string, bool>* keys;
		static SDL_Event e;
		static unsigned int m_time;
		static SDL_Thread* sndThread;
		
};

#endif
