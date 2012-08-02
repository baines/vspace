#include "engine.h"
#include "splash.h"
#include "sound.h"
//#include "title.h"

bool Engine::running = false;
SDL_Event Engine::e = { };
std::queue<Sprite*>* Engine::sprites = new std::queue<Sprite*>;
std::map<std::string, bool>* Engine::keys = new std::map<std::string, bool>;
SDL_Thread* Engine::sndThread;
unsigned int Engine::m_time = 0;

void Engine::init()
{
	running = true;
	Renderer::init(640,480,"Vector Space");
	Sound::init();
	Gamestate::stateStack->push_back(new Splash());
	//sndThread = SDL_CreateThread(Sound::update,NULL);
	atexit(Engine::exit);
	SDL_ShowCursor(SDL_DISABLE);
}

void Engine::handleInput(bool toggle)
{
	switch(e.key.keysym.sym)
	{
		case SDLK_RETURN: 
			/*if(toggle && e.key.keysym.mod && KMOD_ALT){
				Renderer::toggleFullscreen();
				 break;
			}*/
		case SDLK_KP_ENTER: (*(keys))["enter"] = toggle; break;
		case SDLK_ESCAPE: (*(keys))["esc"] = toggle; break;
		case SDLK_UP:
		case SDLK_w: (*(keys))["up"] = toggle; break;
		case SDLK_DOWN:
		case SDLK_s: (*(keys))["down"] = toggle; break;
		case SDLK_LEFT:
		case SDLK_a: (*(keys))["left"] = toggle; break;
		case SDLK_RIGHT:
		case SDLK_d: (*(keys))["right"] = toggle; break;
		case SDLK_p: (*(keys))["menu"] = toggle; break;
		case SDLK_SPACE: (*(keys))["space"] = toggle; break;
	}
}

void Engine::update(float delta)
{
	if(Gamestate::schedulePop > 0)
	{
		for(int i = 0; i < Gamestate::schedulePop; i++){
			delete Gamestate::stateStack->back();
			Gamestate::stateStack->pop_back();
		}
		Gamestate::schedulePop = 0;
	}
	if(Gamestate::nextState)
	{
		Gamestate::stateStack->push_back(Gamestate::nextState);
		Gamestate::nextState = NULL;
	}

	Gamestate::stateStack->back()->update(keys,delta);
}

void Engine::draw()
{
	for(std::vector<Gamestate*>::const_iterator itr = Gamestate::stateStack->begin(); itr != Gamestate::stateStack->end(); ++itr){
		(*itr)->draw(sprites);
	}
}

void Engine::run()
{
	float delta;
	while (SDL_PollEvent(&Engine::e))
	{
		switch (e.type)
		{
			case SDL_QUIT: running = false; break;
			case SDL_KEYDOWN: handleInput(true); break;
			case SDL_KEYUP: handleInput(false); break;
		}
	}
	if(SDL_GetTicks() >= (m_time + 8)) // 125 fps cap
	{
		delta = (float)(SDL_GetTicks() - m_time);
		m_time +=delta;
		update(delta * 0.001f);
		draw();
		Renderer::draw(sprites);
	}else
	{
		SDL_Delay(1);
	}
}

void Engine::exit()
{
	running = false;
	
	delete keys;
	delete sprites;
	
	Gamestate::quit();
	Sound::quit();
	Renderer::quit();
	//SDL_WaitThread(sndThread, NULL);	
}
