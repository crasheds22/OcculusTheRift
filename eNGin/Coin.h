#ifndef COIN_H
#define COIN_H

#include "Actor.h"

/**
 *	@clas Coin
 *	@brief Defiens a coin in the Game world
 *
 *	@author Liam Kinsella
 *	@version 1.0
 *	@date 17-10-2018
 */
class Coin : public Actor
{
public:
	/**
	 *	A constructor with arguments
	 *	Builds a coin with the values passed in
	 *	@param x The x position in the world
	 *	@param y The y position in the world
	 *	@param z The z position in the world
	 *	@param mod The model to use for the coin
	 *	@param tex The texture to use on the model 
	 */
	Coin(float x, float y, float z, Model* mod, Texture* tex);

	/**
	 *	A normal function returning an int
	 *	@return The value of the coin
	 */
	int GetValue();

	/**
	 *	An overridden function taking one argument
	 *	@param deltaTime The time between successive calls
	 */
	void Update(float deltaTime) override;

	/**
	 *	An empty overriden member
	 *	Had to be overriden, but does nothing in this case
	 */
	void Update(float deltaTime, std::map<int, std::vector<Actor*>> eMap) override {};

protected:
	float size = 2; /*<! size of the coin's hit box>*/

	int value = 20;	/*<! The value of the coin for score */

	float rotSpeed = 90; /*<! The speed at which the coin rotates */
};

#endif