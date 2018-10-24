#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <vector>

#include "SDL.h"
#include "SDL_mixer.h"

/**
 *	@class SoundPlayer
 *	@brief Plays and controls sounds
 *	
 *	@author Liam Kinsella
 *	@date 10-10-2018
 *	@version 1.0
 */
class SoundPlayer
{
public:
	/**
	*	Default constructor
	*	Sets up required SDL Audio and loads sound files
	*/
	SoundPlayer();

	/**
	*	Default destructor
	*	Frees sounds from memory
	*/
	~SoundPlayer();

	/**
	*	A normal member taking 1 argument
	*	Called by game to play the sound at point soundId, automatically plays on an available sound channel
	*	@param soundId the index of the sound to be played
	*/
	void PlaySound(int soundId);

private:
	std::vector<Mix_Chunk*> sounds; /*<! Vector of all sounds used in game>*/
};

#endif






