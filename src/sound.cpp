#include "sound.h"
#include "SDL/SDL.h"
#include <string>

bool Sound::enabled = false;
Mix_Music* Sound::music;
std::map<std::string, Mix_Chunk*> Sound::sfx;

void Sound::init(){
	if(SDL_Init(SDL_INIT_AUDIO) != 0){
	    fprintf(stderr, "Unable to open audio: %s\n",SDL_GetError());
	    return;
	}
	
	if(Mix_OpenAudio(44100, AUDIO_S16, 2, 1024) != 0) {
    	fprintf(stderr, "Unable to open audio: %s\n",Mix_GetError());
    	enabled = false;
	}else{
		music = Mix_LoadMUS("./media/snd/vspace.xm");
		
		loadSFX("explode.wav");
		loadSFX("death.wav");
		loadSFX("select1.wav");
		loadSFX("select2.wav");
		loadSFX("fire.wav");
		loadSFX("switch.wav");
		loadSFX("win.wav");
		enabled = true;
	}
}

void Sound::playMusic(){
	if(enabled) Mix_PlayMusic(music, -1);
}
void Sound::stopMusic(){
	if(enabled) Mix_HaltMusic();
}

void Sound::quit(){
	if(enabled){
		Mix_FreeMusic(music);
		Mix_CloseAudio();
	
		for(std::map<std::string, Mix_Chunk*>::iterator it = sfx.begin(); it != sfx.end(); it++)
			Mix_FreeChunk(it->second);
	}	
}

void Sound::play(const std::string& filename){
	if(enabled){
		std::map<std::string, Mix_Chunk*>::iterator it = sfx.find(filename);
 
		int channel = Mix_PlayChannel(-1, it->second, 0);
		if(channel == -1) {
			fprintf(stderr, "Unable to play WAV file: %s\n", Mix_GetError());
		}
	}
}

void Sound::loadSFX(const std::string& filename){
	Mix_Chunk* tmp = Mix_LoadWAV(("./media/snd/"+filename).c_str());
	if(!tmp){
		fprintf(stderr, "Unable to load WAV file: %s\n", filename.c_str());
	}else{
		sfx[filename] = tmp;
	}
}
