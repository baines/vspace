#include "gamestate.h"

Gamestate* Gamestate::nextState = NULL;
std::vector<Gamestate*>* Gamestate::stateStack = new std::vector<Gamestate*>;
int Gamestate::schedulePop = 0;

Gamestate::Gamestate()
{

}

Gamestate::~Gamestate()
{

}

void Gamestate::update(std::map<std::string, bool>* keys, float delta)
{

}

const void Gamestate::draw(std::queue<Sprite*>* sprites)
{
	
}

void Gamestate::push(Gamestate* newState)
{
	nextState = newState;
}

void Gamestate::quit()
{
	while (!stateStack->empty()){
		delete stateStack->back();
    	stateStack->pop_back();
	}
	
	delete stateStack;

}
