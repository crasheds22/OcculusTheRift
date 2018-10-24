#ifndef WALL_H
#define WALL_H

//===========================
#include "Actor.h"
//===========================

/**
 *	@class Wall
 *	@brief Defines a wall in the game
 *	
 *	@author Liam Kinsella
 *	@date 01-10-2018
 *	@version 1.0
 */
class Wall : public Actor
{
public:
	/**
	 *	Constructor with parameters
	 *	Initialises all values with those passed in as specifics
	 *
	 *	@param x The desired x position of the wall
	 *	@param y The desired y position of the wall
	 *	@param z The desired z position of the wall
	 *	@param mod The desired model to use for the wall
	 *	@param tex The desired texture to use on the wall
	 */
	Wall(float x, float y, float z, Model* mod, Texture* tex);

	/**
	 *	An empty overriden member
	 *	Had to be overriden, but does nothing in this case
	 */
	void Update(float deltaTime) override {};

protected:
	float size = 2.2; /*<! size of the wall's hit box */
};
//=========================================================================
#endif
