#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include "SDL/SDL.h"
#include "sprite.h"
#include <map>
#include <queue>
#include <vector>
#include <string>

class Gamestate
{
public:
	Gamestate();
	virtual ~Gamestate();
	static std::vector<Gamestate*>* stateStack;
	static Gamestate* nextState;
	virtual void update(std::map<std::string, bool>* keys, float delta);
	virtual const void draw(std::queue<Sprite*>* sprites);
	static void pop(int amount){ schedulePop = amount; }
	static void push(Gamestate* newState);
	static void quit();
	static int schedulePop;
};

#endif
