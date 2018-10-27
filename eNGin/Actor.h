#ifndef ACTOR_H
#define ACTOR_H

#include <vector>
#include <map>

#include "Collider.h"
#include "Vector3.h"
#include "Model.h"
#include "Texture.h"

/**
 *	@class Actor
 *	@brief Base class for all objects in a scene: ie enemies, the player, items
 *	@details Holds positional, textural and model information about an Actor
 *
 *	@author Aaron Thomson
 *	@version 1.0
 *	@date 14-08-2018
 *	
 *	@author Aaron Thomson
 *	@version 2.0 Changed the position type to a Vector3, added AABB 
 *	@date 05-09-2018
 *
 *	@author Aaron Thomson
 *	@version 3.0 Added Model and Texture pointer
 *	@date 06-09-2018
 *
 *	@author Aaron Thomson
 *	@version 3.1 Updated constructors
 *	@date 10-09-2018
 *
 *	@author Vincent Tan
 *	@version 4.0 Added collisions
 *	@date 28-09-2018
 *
 *	@author Vincent Tan
 *	@version 4.1 Move collisions out of Actor class
 *	@date 29-09-2018
 *
 *	@author Aaron Thomson
 *	@version 4.2 Added extra set/get functions for health, Changed draw function to translate, rotate then draw
 *	@date 22-10-2018
 */
class Actor {
public:
	/**
	 *	Default constructor
	 *	Initialises member variables
	 */
	Actor();

	/**
	 *	Constructor with parameters
	 *	Assigns a model and a texture to the actor
	 */
	Actor(Model* mod, Texture* tex);

	/**
	 *	A virtual member taking no arguments
	 *	Every Actor has to override the Update function for their own unique reasons
	 */
	virtual void Update(float deltaTime) = 0;

	virtual void Update(float deltaTime, std::map<int, std::vector<Actor*>> entityMap) = 0;

	/**
	 *	A virtual member taking no arguments
	 *	Every Actor can override the Draw function for their own unique models and textures
	 */
	virtual void Draw();

	//================================================================================
	// Set methods
	/**
	 *	A normal member taking one argument
	 *	Sets the move speed for the actor
	 *	@param spd The desired speed of the actor
	 */
	void SetMoveSpeed(double spd);

	/**
	 *	A normal member taking one argument
	 *	Sets the rotate speed of the Actor
	 *	@param spd The desired rotation speed of the ACtor
	 */
	void SetRotateSpeed(double spd);

	/**
	 *	A normal member taking one argument
	 *	Sets the Actor's position in the 3D world
	 *	@param pos The desired Point to place the Actor
	 */
	void SetPos(Vector3 pos);

	/**
	 *	A normal member taking 3 arguments
	 *	Sets the Actor's position in the 3D world
	 *	@param tempX The desired x position
	 *	@param tempY The desired y position
	 *	@param tempZ The desired z position
	 */
	void SetPos(double tempX, double tempY, double tempZs);

	/**
	 *	A normal member taking one argument
	 *	Sets the Actor's rotation in the world
	 *	@param rot The desired rotations around each axis
	 */
	void SetRot(Vector3 rot);

	/**
	 *	A normal member taking 3 arguments
	 *	Sets the Actor's rotation values about each axis
	 *	@param rotX The rotation about the x axis
	 *	@param rotY The rotation about the y axis
	 *	@param rotZ The rotation about the z axis
	 */
	void SetRot(double rotX, double rotY, double rotZ);

	/**
	 *	A normal member taking one argument
	 *	Sets the Actor's scale in the world
	 *	@param sca The desired scale values on each axis
	 */
	void SetScale(Vector3 sca);

	/**
	 *	A normal member taking 3 arguments
	 *	Sets the Actor's scale in the world along each axis
	 *	@param scaX The Scaling along the x axis
	 *	@param scaY The Scaling along the y axis
	 *	@param scaZ The scaling along the z axis
	 */
	void SetScale(double scaX, double scaY, double scaZ);

	/**
	 *	A normal function taking one argument
	 *	Sets the Actors maximum health
	 *	@param max The Value of maximum health
	 */
	void SetMaxHealth(int max);

	/**
	 *	A normal function returning an int
	 *	@return The mmaximum health of the actor
	 */
	int GetMaxHealth();

	/**
	 *	A normal fucntion taking one argument
	 *	Sets the actors current health
	 *	@param cur The value to change the actors health too
	 */
	void SetCurrentHealth(int cur);

	/**
	 *	A normal function returning an int
	 *	@return The actor's current health
	 */
	int GetCurrentHealth();
	//================================================================================

	//================================================================================
	// Get methods
	/**
	 *	A normal member returning a Vector
	 *	Returns the values relating to the Actor's position
	 *	@return The position values
	 */
	Vector3 GetPos();

	/**
	 *	A normal member returning a Vector
	 *	Returns the values relating to the Actor's rotation
	 *	@return The rotation values
	 */
	Vector3 GetRot();

	/**
	 *	A normal member returning a Vector
	 *	Returns the values relating to the Actor's scale
	 *	@return The scale values
	 */
	Vector3 GetScale();
	//================================================================================

	/**
	 *	A normal fucntion returning a Collider
	 *	Returns the values relating to the Actor's collision coords
	 *	@return The collider values
	 */
	Collider GetCollider();

	/**
	 *	A normal fucntion returning a double
	 *	@return The rotate speed of the actor
	 */
	double GetRotateSpeed();

	/**
	 *	A normal function returning a double
	 *	@return The movement speed of the actor
	 */
	double GetMoveSpeed();

protected:
	Vector3 position;	/*<! The position of the Actor */
	Vector3 rotations;	/*<! The rotation of the Actor */
	Vector3	scale;		/*<! The scale of the Actor */

	Collider collisionBox;	/*<! The collider box associated with the Actor */

	Model *model = NULL;		/*<! The model owned by this instance of Actor */
	Texture *texture = NULL;	/*<! The texture to be used for this Actor's Model */

	//========================================
	//Speeds
	double moveSpeed,		/*<! The Actor's movement speed */
		rotateSpeed;	/*<! The Actor's rotation speed */
	//========================================
	
	int maxHealth,	/*<! The actor's maximum health */
		health;		/*<! The actor's current health */
};

#endif
