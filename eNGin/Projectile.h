#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Actor.h"
#include "Vector3.h"

/**
 *	@class Projectile
 *	@brief Defines the behaviour of a projectile
 *	
 *	@author Aaron Thomson
 *	@date 15-10-2018
 *	@version 1.0
 */
class Projectile : public Actor {
public:
	/**
	 *	Constructor with paramters
	 *	Initialises values to those passed in 
	 *
	 *	@param act The Actor owner to this projectile
	 *	@param mod The model to use
	 *	@param tex The texture to use on the model
	 *	@param spd The speed to move along at
	 *	@param dir The direction to move in
	 *	@param start The location to start moving from
	 */
	Projectile(Actor* act, Model *mod, Texture *tex, double spd, Vector3 dir, Vector3 start);

	/**
	 *	A normal destructor
	 *	Deletes the instance of the projectile when it is out of scope
	 */
	~Projectile();

	/**
	 *	An overridden member taking one parameter
	 *	
	 *	@param deltaTime The time interval between successive calls
	 */
	void Update(float deltaTime) override;

	/**
	 *	Defines the way the projectile will move
	 */
	void Move();

	/**
	 *	A normal function returning a double
	 *	Returns the current time alive for the projectile
	 */
	double GetTime();

private:
	Actor* owner;	/*<! The owner of the projectile */

	double timeAlive;	/*<! The amount of time it has been alive */
	double dT;	/*<! A staple for holding delta time */

	Vector3 direction;	/*<! The direction to move in */

};

#endif
