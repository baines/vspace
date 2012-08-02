#ifndef _SPLASH_H_
#define _SPLASH_H_

#include "sprite.h"
#include "timer.h"
#include <queue>
#include "title.h"

class Splash : public Gamestate
{
public:	
	Splash()
	{ 
		m_splash = new Sprite("splash.png", 320, 240, 512, 512, 0, 0);
		m_timer = new Timer();
		phase = 0;
	}
	
	~Splash()
	{
		delete m_timer;
		delete m_splash;
	}
	
	void update(std::map<std::string, bool>* keys, float delta)
	{
		if((*keys)["esc"] || (*keys)["enter"]){
			phase = 250;
			(*keys)["esc"] = false;
			(*keys)["enter"] = false;
		}
			
		if(m_timer->elapsed() > 0.01f)
		{
			phase++;
			if(phase < 100) m_splash->alpha+=0.01;
			if(phase > 150) m_splash->alpha-=0.01;
			if(phase >= 250)
			{
				m_splash->alpha = 0.0f;
				Renderer::deleteTexture("splash.png");
				Gamestate::pop(1);
				Gamestate::push(new Title());
			}
			m_timer->reset();
		}
	}
	
	const void draw(std::queue<Sprite*>* sprites)
	{
		sprites->push(m_splash);		
	}
	
private:
	Sprite* m_splash;
	Timer* m_timer;
	int phase;
};

#endif
