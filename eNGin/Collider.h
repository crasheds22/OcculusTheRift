#ifndef AABB_H
#define AABB_H

#include <gl/glut.h>


#include "Vector3.h"
#include "Projection.h"

/**
 *	@class AABB
 *	@brief Defines the min and max points of a box
 *	@details A box is defined by it's maximum and minimum points
 *
 *	@author Rebecca Lim
 *	@version 1.0
 *	@date 14-08-2018
 *
 *	@author Aaron Thomson
 *	@version 1.1 Changed Set methods from Vector3 type to 3 GLdouble types, Replaced AABBtoAABB function with overloaded < operators
 *	@date 05-09-2018
 */
class AABB {
public:
	/**
	 *	Default constructor
	 */
	AABB();

	//======================================================================
	// Set methods
	/**
	 *	A normal member taking 3 arguments
	 *	Sets the minimum point of the box
	 *	@param tempX The minimum x point
	 *	@param tempY The minimum y point
	 *	@param tempZ The minimum z point
	 */
	void SetMinPoint(GLdouble tempX, GLdouble tempY, GLdouble tempZ);

	/**
	 *	A normal member taking 3 arguments
	 *	Sets the maximum point of the box
	 *	@param tempX The maximum x point
	 *	@param tempY The maximum y point
	 *	@param tempZ The maximum z point
	 */
	void SetMaxPoint(GLdouble tempX, GLdouble tempY, GLdouble tempZ);
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
	bool AABBtoAABB(AABB &objectOther);

	/**
	 *	An overloaded operator function returning a boolean
	 *	Returns the AABB that is less than another AABB
	 *	@return bool If the box is within or outside another box
	 */
	bool operator < (AABB &other);

	/**
	 *	An overloaded operator function returning a boolean
	 *	Returns the AABB that is greater than another AABB
	 *	@return bool If the box is within or outside another box
	 */
	bool operator > (AABB &other);

	/**
	*	@brief to find the orthognoal vector to the projection
	*	@param 
	*	@return vector perpendicular to the projection is returned
	*	@pre
	*	@post
	*/
	Vector3 ProjectionNormal();


	/**
	*	@brief to find the projection between two bounding boxes
	*	@param 
	*	@return projected projection is returned
	*	@pre
	*	@post
	*/
	Projection VectorProjection();

	/**
	*	@brief to find the depth of intersection
	*	@param objectOther target object for comparison
	*	@return a depth of intersection is returned
	*	@pre minimum and maximum points must exist
	*	@post
	*/
	GLdouble ProjectionOverlap(Projection targetProjection);

	/**
	*	@brief to find the depth of intersection
	*	@param objectOther target object for comparison
	*	@return a depth of intersection is returned
	*	@pre minimum and maximum points must exist
	*	@post
	*/
	Vector3 MinimumTranslationVector(AABB &projectTarget);

private:
	Vector3 minPoint,	/*<! The minimum point of the bounding box */
			maxPoint;	/*<! The maximum point of the bounding box */
};

#endif
