#ifndef _MENU_H_
#define _MENU_H_

#include "sprite.h"
#include "gamestate.h"
#include <queue>
#include <string>
#include <map>

class Menu : public Gamestate
{
public:	
	Menu();
	~Menu();
	void update(std::map<std::string, bool>* keys, float delta);	
	const void draw(std::queue<Sprite*>* sprites);
	
private:
	Sprite* m_menu;
	Sprite* arrow;
	
	int selection;
	bool released;
	int positions[2];
};

#endif
