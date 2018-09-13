
#include <pch.h>

#include "MusicPlayer.h"
#include<iostream>

MusicPlayer::MusicPlayer()
{
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
	int result = 0;
	int flags = MIX_INIT_MP3;

	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		std::cout << "Failed to init SDL" << std::endl;
		exit(1);
	}

	if (flags != (result = Mix_Init(flags))) {
		std::cout << "Could not initialize mixer, result: " << std::endl;
		std::cout << "Mix_Init: " << Mix_GetError() << std::endl;
		exit(1);
	}
	songs.resize(10);

	songs[0] = Mix_LoadMUS("data/test_song.mp3");

	songs[1] = Mix_LoadMUS("data/test_song2.mp3");

	currentSong = songs[0];
}

MusicPlayer::~MusicPlayer()
{
	Mix_FreeMusic(songs[0]);
	Mix_FreeMusic(songs[1]);
}

void MusicPlayer::PlaySong()
{
	if (!Mix_PlayingMusic())
	{
		std::cout << "Test" << std::endl;
		Mix_FadeInMusic(currentSong, -1, 100);
	}
}

void MusicPlayer::SetSong(int songIn)
{
	if (songs[songIn] != currentSong)
	{
		Mix_FadeOutMusic(500);
		currentSong = songs[songIn];
	}

}