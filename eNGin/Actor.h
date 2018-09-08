#ifndef ACTOR_H
#define ACTOR_H

#include <math.h>
#include <gl\glut.h>

#include "Collider.h"
#include "Vector3.h"
#include "Model.h"
#include "Texture.h"

const float PI = 3.141592654;

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
	/**
	 *	Default constructor
	 *	Initialises member variables
	 */
	Actor();

	/**
	 *	A pure virtual member taking no arguments
	 *	Every Actor needs to override the Update function for their own unique reasons
	 */
	virtual void Update() = 0;

	/**
	 *	A pure virtual member taking no arguments
	 *	Every Actor need to override te Draw function tor their own unique models and textures
	 */
	virtual void Draw() = 0;

	//================================================================================
	// Set methods
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
	void SetRot(Point rot);

	/**
	 *	A normal member taking 3 arguments
	 *	Sets the Actor's rotation values about each axis
	 *	@param rotX The rotation about the x axis
	 *	@param rotY The rotation about the y axis
	 *	@param rotZ The rotation about the z axis
	 */
	void SetRot(GLdouble rotX, GLdouble rotY, GLdouble rotZ);

	/**
	 *	A normal member taking one argument
	 *	Sets the Actor's scale in the world
	 *	@param sca The desired scale values on each axis
	 */
	void SetScale(Point sca);

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
	Point GetRot();

	/**
	 *	A normal member returning a Point value
	 *	Returns the values relating to the Actor's scale
	 *	@return The scale values
	 */
	Point GetScale();
	//================================================================================

protected:
	Vector3 position;	/*<! The position of the Actor */
	Point rotations,	/*<! The rotation of the Actor */
		  scale;		/*<! The scale of the Actor */

	Collider collisionBox;	/*<! The collider box associated with the Actor */

	Model *model;		/*<! The model owned by this instance of Actor */
	Texture *texture;	/*<! The texture to be used for this Actor's Model */
};

#endif
