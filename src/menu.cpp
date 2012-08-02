#include "menu.h"
#include "title.h"

Menu::Menu()
{
	m_menu = new Sprite("menu.png",320,240,256,256);
	arrow = new Sprite("arrow.png",260,220,16,16);
	selection = 0;
	released = false;
	positions[0] = 220;
	positions[1] = 262;
}

Menu::~Menu()
{
	delete arrow;
	delete m_menu;
}

void Menu::update(std::map<std::string, bool>* keys, float delta)
{
	if((*keys)["enter"]){
		switch(selection){
			case 0:
				(*keys)["enter"] = false;
				Gamestate::pop(1);
				Sound::play("select2.wav");
				break;
			case 1:
				(*keys)["enter"] = false;
				Sound::play("select2.wav");
				Gamestate::pop(2);
				Gamestate::push(new Title());
				break;
		}
	}
	if((*keys)["up"] && released){
		selection--;
		Sound::play("select1.wav");
		if(selection == -1) selection = 1;
		released = false;
	}
	if((*keys)["down"] && released){
		selection++;
		Sound::play("select1.wav");
		if(selection == 2) selection = 0;
		released = false;
	}
	if(!(*keys)["down"] && !(*keys)["up"])
		released = true;
		
	if((*keys)["esc"]){
		(*keys)["esc"] = false;
		Gamestate::pop(1);
	}
	
	arrow->y = positions[selection];
}

const void Menu::draw(std::queue<Sprite*>* sprites)
{
	sprites->push(m_menu);	
	sprites->push(arrow);	
}
