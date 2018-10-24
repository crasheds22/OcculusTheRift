#ifndef QUATERNION_H
#define QUATERNION_H

#include <math.h>
#include "Vector3.h"

/**
 *	@class Quaternion
 *	@brief A utility class for Quaternion math
 *	
 *	@author Rebecca Lim
 *	@date 09-10-2018
 *	@version 1.0
 *
 *	@author Vincent T
 *	@date 12-10-2018
 *	@version 1.1: Fixed LR mouse movement
 */
class Quarternion
{
public:
	/**
	 *	Default constructor
	 *	Initialises all values to 0
	 */
	Quarternion();

	/**
	 *	Constructor with parameters
	 *	Initialises values to those passed in
	 *	@param inputX The x axis value
	 *	@param inputY The y axis value
	 *	@param inputZ The z axis value
	 *	@param inputW The angle around the axis
	 */
	Quarternion(double inputX, double inputY, double inputZ, double inputW);

	//=============================================================================
	// Set methods
	/**
	 *	A normal member taking one argument
	 *	Sets the quaternion x value
	 *	@param quartX The x value of the axis
	 */
	void SetQuartX(double quartX);

	/**
	*	A normal member taking one argument
	*	Sets the quaternion y value
	*	@param quartY The y value of the axis
	*/
	void SetQuartY(double quartY);

	/**
	*	A normal member taking one argument
	*	Sets the quaternion z value
	*	@param quartX The z value of the axis
	*/
	void SetQuartZ(double quartZ);

	/**
	*	A normal member taking one argument
	*	Sets the quaternion w value
	*	@param quartX The rotation value
	*/
	void SetQuartW(double quartW);
	//=============================================================================

	//=============================================================================
	// Get methods
	/**
	 *	A normal member returning a double value
	 *	@return The x value of the axis
	 */
	double GetQuartX();

	/**
	*	A normal member returning a double value
	*	@return The y value of the axis
	*/
	double GetQuartY();

	/**
	*	A normal member returning a double value
	*	@return The z value of the axis
	*/
	double GetQuartZ();

	/**
	*	A normal member returning a double value
	*	@return The rotation value around the axis
	*/
	double GetQuartW();
	//=============================================================================

	//=============================================================================
	// Utility
	/**
	*	Function returns the squared magnitude value of the Quaternion
	*	@return The squared magnitude value
	*/
	double QuartSquared();

	/**
	*	Function returns the actual magnitude of the quaternion
	*	@return The magnitude of the quaternion
	*/
	double QuartMagnitude();

	/**
	*	@brief calculation for quarternion conjugate
	*	@param
	*	@return quarternion conjugate
	*	@pre
	*	@post
	*/
	Quarternion Conjugate();

	/**
	*	@brief dot product for quarternions
	*	@param
	*	@return quarternion scalar
	*	@pre
	*	@post
	*/
	double DotProduct(Quarternion inputQuart);

	/**
	*	@brief cross product for quarternions
	*	@param inputQuart
	*	@return quarternion 
	*	@pre
	*	@post
	*/
	Quarternion CrossProduct(Quarternion inputQuart);

	/**
	*	@brief scalar product for quarternions
	*	@param inputQuart
	*	@return quarternion 
	*	@pre
	*	@post
	*/
	Quarternion ScalarProduct(double theScalar);

	/**
	*	@brief inverse for quarternions
	*	@param inputQuart
	*	@return quarternion
	*	@pre
	*	@post
	*/
	Quarternion Inverse();

	/**
	*	@brief rotation for quarternions
	*	@param theTheta angle in 
	*	@param theAxis the axis to rotate on 
	*	@return quarternion
	*	@pre
	*	@post
	*/
	Quarternion QRotation(double theTheta, Vector3 theAxis);

	/**
	*	@brief normalization for quarternions
	*	@return quarternion
	*	@pre
	*	@post
	*/
	Quarternion Normalize();

	/**
	*	Function for Spherical Linear Interpolation
	*
	*	@param targetQuart The quaternion to rotate to
	*	@param t The time to take to get there
	*	@return The resultant quaternion
	*/
	Quarternion Slerp(Quarternion targetQuart, double t);

private:
	double x; /*<! The x value */
	double y; /*<! The y value */
	double z; /*<! The z value */
	double w; /*<! The w value */
};

#endif
