#ifndef _GAME_H_
#define _GAME_H_

#include "sprite.h"
#include "player.h"
#include "asteroid.h"
#include "menu.h"
#include "sound.h"
#include <queue>
#include <cmath>

class Game : public Gamestate
{
public:	
	Game();
	~Game();
	void update(std::map<std::string, bool>* keys, float delta);
	const void draw(std::queue<Sprite*>* sprites);
	void randomiseStars();
	
private:
	Player* player;
	Sprite* border[4];
	Sprite* stars[40];
	Sprite* lives[3];
	std::vector<Asteroid*>* asteroids;
	int numLives;
	int numAsteroids;
};

#endif
