#include "SoundPlayer.h"

SoundPlayer::SoundPlayer()
{
	if (SDL_Init(SDL_INIT_AUDIO) != 0)
	{
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
	}

	int audio_rate = 22050; 
	Uint16 audio_format = AUDIO_S16SYS; 
	int audio_channels = 2; 
	int audio_buffers = 4096;

	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0)
	{
		fprintf(stderr, "Unable to initialize audio: %s\n", Mix_GetError());
	}

	sounds.emplace_back(Mix_LoadWAV("data/coin.wav"));
}

SoundPlayer::~SoundPlayer()
{
	for (int i = 0; i < sounds.size(); i++)
	{
		Mix_FreeChunk(sounds[i]);
	}
}

void SoundPlayer::PlaySound(int soundId)
{
	int channel;
	channel = Mix_PlayChannel(-1, sounds[soundId], 0);
}