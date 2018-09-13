#ifndef MusicPlayer_h
#define MusicPlayer_h

#include "SDL2_Mixer\include\SDL_mixer.h"
#include "SDL_mixer.h"
#include <SDL.h>
#include<vector>

class MusicPlayer
{
public:
	/**
	*	Default constructor
	*	Sets up required SDL Audio and loads music tracks
	*/
	MusicPlayer();
	
	/**
	*	Default destructor
	*	Frees music from memory
	*/
	~MusicPlayer();

	/**
	*	Normal member function
	*	Called by game to play the currentSong, briefly fades music in if no song is playing
	*/
	void PlaySong();


	/**
	*	A normal member taking 1 argument
	*	Used to set the current song
	*	@param songIn the index of the next song to be played on the music player
	*/
	void SetSong(int songIn);

private:
	Mix_Music * currentSong; /*<! Song currently being played by the MusicPlayer>*/
	std::vector<Mix_Music*> songs; /*<! Vector of all songs used in game>*/
};

#endif