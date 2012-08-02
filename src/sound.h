#ifndef _SOUND_H_
#define _SOUND_H_

#include <SDL/SDL_mixer.h>
#include <map>
#include <string>

class Sound {
	public:
		static void init();
		static void quit();
		static void play(const std::string& filename);
		static void playMusic();
		static void stopMusic();
		static void pauseMusic();
	private:
		static std::map<std::string, Mix_Chunk*> sfx;
		static Mix_Music* music;
		static bool enabled;
		static void loadSFX(const std::string& filename);
};
#endif
