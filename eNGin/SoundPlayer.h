#ifndef SoundPlayer_h
#define SoundPlayer_h


#include <vector>

#include "SDL.h"
#include "SDL_mixer.h"

class SoundPlayer
{
public:
	SoundPlayer();

	~SoundPlayer();

	void PlaySound(int soundId);

private:
	std::vector<Mix_Chunk*> sounds;
};

#endif
