#ifndef ACTOR_H
#define ACTOR_H

#include <math.h>
#include <gl\glut.h>

#include "Collider.h"
#include "Vector3.h"
#include "Model.h"
#include "Texture.h"

//const float PI = 3.141592654;

/**
 *	@struct Point
 *	Defines a point in 3D space
 */
struct Point {
	GLdouble x, /*<! Position on the x plane */
			 y, /*<! Position on the y plane */
			 z; /*<! Position of the z plane */
};

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
 *	@version 2.0 Changed the position type to a Vector 3, added AABB 
 *	@date 05-09-2018
 *
 *	@author Aaron Thomson
 *	@version 3.0 Added Model and Texture pointer
 *	@date 06-09-2018
 */
class Actor {
public:

	enum ActorTag { Walls, Object, Camera };

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
	 *	Every Actor can override the Update function for their own unique reasons
	 */
	virtual void Update();

	/**
	 *	A virtual member taking no arguments
	 *	Every Actor can override the Draw function for their own unique models and textures
	 */
	virtual void Draw();

	//================================================================================
	// Set methods
	/**
	 *	A normal member taking one argument
	 *	Sets the move speed for the Player
	 *	@param spd The desired speed of the Player
	 */
	void SetMoveSpeed(GLdouble spd);

	/**
	 *	A normal member taking one argument
	 *	Sets the rotate speed of the Player
	 *	@param spd The desired rotation speed of the Player
	 */
	void SetRotateSpeed(GLdouble spd);

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
	void SetPos(GLdouble tempX, GLdouble tempY, GLdouble tempZs);

	/**
	 *	A normal member taking one argument
	 *	Sets the Actor's rotation in the world
	 *	@param rot The desired rotations around each axis
	 */
	virtual void SetRot(Vector3 rot);

	/**
	 *	A normal member taking 3 arguments
	 *	Sets the Actor's rotation values about each axis
	 *	@param rotX The rotation about the x axis
	 *	@param rotY The rotation about the y axis
	 *	@param rotZ The rotation about the z axis
	 */
	virtual void SetRot(GLdouble rotX, GLdouble rotY, GLdouble rotZ);

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
	void SetScale(GLdouble scaX, GLdouble scaY, GLdouble scaZ);
	//================================================================================

	//================================================================================
	// Get methods
	/**
	 *	A normal member returning a Point value
	 *	Returns the values relating to the Actor's position
	 *	@return The position values
	 */
	Vector3 GetPos();

	/**
	 *	A normal member returning a Point value
	 *	Returns the values relating to the Actor's rotation
	 *	@return The rotation values
	 */
	Vector3 GetRot();

	/**
	 *	A normal member returning a Point value
	 *	Returns the values relating to the Actor's scale
	 *	@return The scale values
	 */
	Vector3 GetScale();
	//================================================================================

	/**
	 *	A collider getter
	 *	Returns the values relating to the Actor's collision coords
	 *	@return The collider values
	 */
	Collider GetCollider();


protected:

	
	Vector3 position;	/*<! The position of the Actor */
	Vector3 rotations;	/*<! The rotation of the Actor */
	Vector3	scale;		/*<! The scale of the Actor */

	Collider collisionBox;	/*<! The collider box associated with the Actor */

	Model *model = NULL;		/*<! The model owned by this instance of Actor */
	Texture *texture = NULL;	/*<! The texture to be used for this Actor's Model */

	

	//========================================
	//Speeds
	GLdouble moveSpeed,		/*<! The Actor's movement speed */
		rotateSpeed;	/*<! The Actor's rotation speed */
	//========================================
};

#endif
