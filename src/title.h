#ifndef _TITLE_H_
#define _TITLE_H_

#include "sprite.h"
#include "timer.h"
#include <queue>
#include "game.h"
#include "renderer.h"

class Title : public Gamestate
{
public:	
	Title()
	{ 
		for(int i=0; i<40; i++){
			stars[i] = new Sprite("dot.png",rand()%640,rand()%480,2,2);
		}
		bg = new Sprite("title.png",320,240,512,512);
		bg_info = new Sprite("info.png",320,240,512,512);
		arrow = new Sprite("arrow.png",260,285,16,16);
		Sound::playMusic();
		released = true;
		positions[0] = 285;
		positions[1] = 327;
		positions[2] = 369;
		selection = 0;
		info = false;
	}
	
	~Title()
	{
		for(int i=0; i<40; i++){
			delete stars[i];
		}
		delete bg;
		delete bg_info;
		delete arrow;
	}
	
	void update(std::map<std::string, bool>* keys, float delta)
	{
		for(int i=0; i<40; i++){
			stars[i]->y -= (250.0f*delta);
			if(stars[i]->y < 0){
				stars[i]->y +=480;
				stars[i]->x = rand()%640;
			}
		}
		if(!info){
			if((*keys)["enter"]){
				switch(selection){
					case 0:
						Renderer::deleteTexture("title.png");
						Gamestate::pop(1);
						Sound::play("select2.wav");
						Gamestate::push(new Game());
						break;
					case 1:
						info = true;
						Sound::play("select2.wav");
						(*keys)["enter"] = false;
						break;
					case 2:
						Sound::play("select2.wav");
						exit(0);
						break;
				}
			}
			if((*keys)["up"] && released){
				selection--;
				Sound::play("select1.wav");
				if(selection == -1) selection = 2;
				released = false;
			}
			if((*keys)["down"] && released){
				selection++;
				Sound::play("select1.wav");
				if(selection == 3)	selection = 0;
				released = false;
			}
			if(!(*keys)["down"] && !(*keys)["up"])
				released = true;
			
			if((*keys)["esc"])
				exit(0);
			
			arrow->y = positions[selection];
		}else{
			if((*keys)["enter"] || (*keys)["esc"]){
				Sound::play("select2.wav");
				info = false;
				(*keys)["enter"] = false;
				(*keys)["esc"] = false;
			}
		}
	}
	
	const void draw(std::queue<Sprite*>* sprites)
	{
		if(info)
			sprites->push(bg_info);
		else{
			sprites->push(bg);
			sprites->push(arrow);
		}
		
		for(int i=0; i<40; i++){
			sprites->push(stars[i]);
		}		
	}
	
private:
	Sprite* stars[40];
	Sprite* arrow;
	Sprite* bg;
	Sprite* bg_info;
	bool released;
	bool info;
	int selection;
	int positions[3];
};

#endif
