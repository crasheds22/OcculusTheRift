#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <vector>

#include "SDL.h"
#include "SDL_mixer.h"

/**
 *	@class MusicPlayer
 *	@brief Controls music in the Game
 *	
 *	@author Liam Kinsella
 *	@date 09-09-2018
 *	@version 1.0
 *
 *	@author Liam Kinsella
 *	@date 16-10-2018
 *	@version 2.0: Added extra music, fade in/out
 */
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

	/**
	*	Normal member function
	*	Called by game to stop the music
	*/
	void StopMusic();

	/**
	*	Normal member function
	*	Called by game to resume music
	*/
	void ResumeMusic();

private:
	Mix_Music * currentSong;		/*<! Song currently being played by the MusicPlayer>*/
	std::vector<Mix_Music*> songs;	/*<! Vector of all songs used in game>*/
	bool menuCheck;					/*<! check to prevent menu music from looping>*/
};

#endif