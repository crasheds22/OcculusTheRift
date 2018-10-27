#ifndef LEVELEXIT_H
#define LEVELEXIT_H

#include "Actor.h"

/**
 *	@class levelExit
 *	@brief Defines the level's exit portal ook and location
 *
 *	@author Liam Kinsella
 *	@date 04-10-2018
 *	@veriosn 1.0
 */
class LevelExit : public Actor
{
public:
	/**
	 *	a constructor with parameters
	 *	@param x The x position
	 *	@param y The y position
	 *	@param z The z position
	 *	@param mod The model to use
	 *	@param tex The texture to use on the model
	 */
	LevelExit(float x, float y, float z, Model* mod, Texture* tex);

	/**
	 *	An empty overridden function
	 *	Would be used to update the level exit
	 */
	void Update(float deltaTime) override {};

	/**
	 *	An empty overriden member
	 *	Had to be overriden, but does nothing in this case
	 */
	void Update(float deltaTime, std::map<int, std::vector<Actor*>> eMap) override {};

protected:
	float size = 1; /*<! The size of the level exit hit box*/
};

#endif
