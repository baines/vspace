#ifndef _TIMER_H_
#define _TIMER_H_
#include "SDL/SDL.h"

class Timer
{
	public:
		Timer(){ reset(); }
		float elapsed(){ return (SDL_GetTicks() - m_time)/1000.0f; }
		void reset(){ m_time = SDL_GetTicks(); }
	private:
		float m_time;
};

#endif
