#ifndef Collider_H
#define Collider_H

class Actor;

#include "Vector3.h"

/**
 *	@class Collider
 *	@brief Defines the min and max points of a box
 *	@details A box is defined by it's maximum and minimum points
 *
 *	@author Rebecca Lim
 *	@version 1.0
 *	@date 14-08-2018
 *
 *	@author Aaron Thomson
 *	@version 1.1 Changed Set methods from Vector3 type to 3 double types, Replaced AABBtoAABB function with overloaded < operators
 *	@date 05-09-2018
 *
 *	@author Rebecca Lim
 *	@version 2.0 Renamed class from AABB to Collider
 *	@date 08-09-2018
 */
class Collider {
public:
	/**
	 *	Default constructor
	 */
	Collider();

	//======================================================================
	// Set methods
	/**
	 *	A normal member taking 3 arguments
	 *	Sets the minimum point of the box
	 *	@param tempX The minimum x point
	 *	@param tempY The minimum y point
	 *	@param tempZ The minimum z point
	 */
	void SetMinPoint(double tempX, double tempY, double tempZ);

	/**
	 *	A normal member taking 3 arguments
	 *	Sets the maximum point of the box
	 *	@param tempX The maximum x point
	 *	@param tempY The maximum y point
	 *	@param tempZ The maximum z point
	 */
	void SetMaxPoint(double tempX, double tempY, double tempZ);
	//======================================================================

	//============================================================
	// Get Methods
	/**
	 *	A normal member return a Vector3
	 *	Returns the minimum point of the box
	 *	@return Vector3 The minimum point
	 */
	Vector3 GetMinPoint();

	/**
	 *	A normal member returning a Vector3
	 *	Returns the maximum point of the box
	 *	@return Vector3 The maximum point
	 */
	Vector3 GetMaxPoint();
	//============================================================

	/**
	*	@brief collision detection function
	*	@param objectOther target object for comparison
	*	@return a boolean of intersection is returned
	*	@pre minimum and maximum points must exist
	*	@post
	*/
	bool AABBtoAABB(Collider objectOther);

	/**
	 *	An overloaded operator function returning a boolean
	 *	Returns if AABB is less than another AABB
	 *	@return If the box is within or outside another box
	 */
	bool operator < (Collider &other);

	/**
	 *	An overloaded operator function returning a boolean
	 *	Returns if AABB is greater than another AABB
	 *	@return If the box is within or outside another box
	 */
	bool operator > (Collider &other);

	/**
	*	Culls the number of objects within the player's vicinity
	*/
	bool ProximityCull(Vector3 actorPosition, Vector3 &inputObject);

	/**
	*	A normal function taking 2 arguments
	*	Prevents an object from intersecting with another object during collision
	*	@param thisObject The original object
	*	@param otherObject The object to collide with
	*/
	void CollideWith(Actor *thisObject, Actor &otherObject);


private:
	Vector3 minPoint,	/*<! The minimum point of the bounding box */
			maxPoint;	/*<! The maximum point of the bounding box */
};

#endif
