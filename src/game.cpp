#include "game.h"
#include "failure.h"

Game::Game(){
	player = new Player(320,280);
	
	numAsteroids = 3;
		
	border[0] = new Sprite("dot.png",320,8,625,2);
	border[0]->setColour(RED);
	border[1] = new Sprite("dot.png",320,471,625,2);
	border[1]->setColour(GREEN);
	border[2] = new Sprite("dot.png",8,240,2,465);
	border[2]->setColour(BLUE);
	border[3] = new Sprite("dot.png",632,240,2,465);
	border[3]->setColour(YELLOW);
	
	asteroids = new std::vector<Asteroid*>;
	
	for(int i=0; i<40; i++){
		stars[i] = new Sprite("dot.png",rand()%640,rand()%480,2,2);
	}
	
	for(int i=0; i<numAsteroids; i++){
		asteroids->push_back(new Asteroid(rand()%640,rand()%480,32));
	}
	
	for(int i=0; i<3; i++){
		lives[i] = new Sprite("ship.png",20+(20*i),460,16,16);
	}
	
	numLives = 3;
}

Game::~Game(){
	delete player;
	for(int i=0; i<4; i++){
		delete border[i];
	}
	for(int i=asteroids->size()-1; i>=0; i--){
		delete asteroids->at(i);
	}
	for(int i=0; i<40; i++){
		delete stars[i];
	}
	for(int i=0; i<3; i++){
		delete lives[i];
	}
	delete asteroids;
}

void Game::update(std::map<std::string, bool>* keys, float delta){			
	if((*keys)["menu"] || (*keys)["esc"]){
		(*keys)["esc"] = false;
		(*keys)["menu"] = false;
		Sound::play("select2.wav");
		Gamestate::push(new Menu());
	}
	if((*keys)["left"]){	
		player->rotation -= (250.0f*delta);
		if(player->rotation < 0)
			player->rotation+=360;
	}
	if((*keys)["right"]){	
		player->rotation += (250.0f*delta);
		if(player->rotation > 360)
			player->rotation-=360;
	}
	if((*keys)["space"]){
		player->shoot();
		(*keys)["space"] = false;
	}
	if(player->update((*keys)["up"] ? 5.0f * delta : 0.0f, delta))
		randomiseStars();
		
	for(int i=asteroids->size()-1; i>=0; i--){
		asteroids->at(i)->update(delta);
		if(Sprite::collision(player,asteroids->at(i))){
			numLives--;
			player->reset();
			Sound::play("death.wav");
		}
		for(std::list<Bullet*>::const_iterator j = player->ammo->begin(); j != player->ammo->end(); j++){
			if(Sprite::collision((*j),asteroids->at(i))){
				Sound::play("explode.wav");
				int tmpx = asteroids->at(i)->x;
				int tmpy = asteroids->at(i)->y;
				int tmpsize = asteroids->at(i)->width;
				delete asteroids->at(i);
				asteroids->erase(asteroids->begin()+i);
				if(tmpsize == 32){
					asteroids->push_back(new Asteroid(tmpx,tmpy,16));
					asteroids->push_back(new Asteroid(tmpx,tmpy,16));
					asteroids->push_back(new Asteroid(tmpx,tmpy,16));
				}
				break;
			}
		}		
	}
	
	if(numLives == -1){
		Gamestate::pop(1);
		Sound::stopMusic();
		Gamestate::push(new Failure);
	}
	
	if(asteroids->empty()){
		Sound::play("win.wav");
		player->setColour(1.0f,1.0f,1.0f);
		
		numAsteroids+=3;
		
		for(int i = 0; i<numAsteroids; i++){
			asteroids->push_back(new Asteroid(rand()%640,rand()%480,32));
		}
	}
}

const void Game::draw(std::queue<Sprite*>* sprites)
{
	player->draw(sprites);
	for(int i=0; i<40; i++)
		sprites->push(stars[i]);

	sprites->push(player);
	
	for(int i=0; i<4; i++)
		sprites->push(border[i]);
		
	for(int i=asteroids->size()-1; i>=0; i--)
		sprites->push(asteroids->at(i));
		
	for(int i=0; i<numLives; i++){
		sprites->push(lives[i]);
	}

}

void Game::randomiseStars()
{
	for(int i=0; i<40; i++){
		stars[i]->x = rand()%640;
		stars[i]->y = rand()%480;
	}
	Sound::play("switch.wav");
}
