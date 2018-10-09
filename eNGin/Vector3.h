#ifndef VECTOR3_H
#define VECTOR3_H

#include <gl/glut.h>

/**
 *	@class Vector3
 *
 *
 *	@author Rebecca Lim
 *	@version 1.0
 *	@date 14-08-2018
 *
 *	@author Aaron Thomson
 *	@version 1.1: Changed Dot and Cross product to pass by reference
 *	@date 05-09-2018
 */
class Vector3 {
public:
	/**
	 *	Default constructor
	 *	Advisable to use the constructor with parameters
	 */
	Vector3();

	/**
	 *	Constructor with parameters
	 *	@param posX The x position
	 *	@param posY The y position
	 *	@param posZ The z position
	 */
	Vector3(GLdouble posX, GLdouble posY, GLdouble posZ);

	//========================================
	// Set Methods
	/**
	 *	A normal member taking one argument
	 *	Sets the x point value
	 *	@param posX The desired x value
	 */
	void SetPointX(GLdouble posX);

	/**
	 *	A normal member taking one argument
	 *	Sets the y point value
	 *	@param posY The desired y value
	 */
	void SetPointY(GLdouble posY);

	/**
	 *	A normal member taking one argument
	 *	Sets the z point value
	 *	@param posZ The desired z value
	 */
	void SetPointZ(GLdouble posZ);
	//========================================

	//========================================
	// Get Methods
	/**
	 *	A normal member returning a GLdouble
	 *	@return The x point value
	 */
	GLdouble GetPointX() const;

	/**
	 *	A normal member returning a GLdouble
	 *	@return The y point value
	 */
	GLdouble GetPointY() const;

	/**
	 *	A normal member returning a GLdouble
	 *	@return The z point value
	 */
	GLdouble GetPointZ() const;
	//========================================

	//========================================
	// Utility
	/**
	 *	A utility function returning a GLdouble
	 *	Calculates the magnitude of the current vector
	 *	@return GLdouble The magnitude of the vector
	 */
	GLdouble VectorMagnitude();

	/**
	 *	A utility function taking one argument and returning a GLdouble
	 *	Calculates the value of two vectors
	 *	@param in The Vector3 to multiply by
	 *	@return GLdouble The result of multiplying the two Vector3's
	 */
	GLdouble DotProduct(Vector3 &in);

	/**
	*	A utility function taking one argument and returning a Vector3
	*	Calculates the resultant vector of two other vectors
	*	@param in The vector to multiply by
	*	@return Vector3 The resultant vector
	*/
	Vector3 CrossProduct(Vector3 &in);

	/**
	*	A utility function taking one argument and returning a Vector3
	*	Calculates the result of multiplying a Vector by a scalar
	*	@param scalar The scalar to multiply the Vector by
	*	@return Vector3 The resultof multiplying the Vector by the scalar
	*/
	Vector3 MultiplyByScalar(GLdouble scalar);

	/**
	*	A utility function returning a Vector3
	*	Calculates the vector equal to one unit in the same direction of the vector
	*	@return Vector3 The unit normal
	*/
	Vector3 UnitNormal(Vector3 &inputVector);


	/**
	*	@brief calculates the angle of a vector in relation to another 
	*	@param targetVector the comparison vector
	*	@return the angle in degrees? is returned
	*	@pre the comparison vector must exist
	*	@post 
	*/
	GLdouble VectorAngle(Vector3 targetVector);
	
	/**
	*	@brief to calculate the difference between two vectors
	*	@param theInputVector target vector
	*	@return a vector
	*	@pre minimum and maximum points must exist
	*	@post
	*/
	Vector3 SubtractVector(Vector3 theInputVector);

	/**
	*	@brief to calculate the sum of two vectors
	*	@param theInputVector target vector
	*	@return a vector
	*	@pre minimum and maximum points must exist
	*	@post
	*/
	Vector3 AddVector(Vector3 theInputVector);

	/**
	*	@brief operator to calculate the difference between two vectors
	*	@param theInputVector target vector
	*	@return a vector
	*	@pre minimum and maximum points must exist
	*	@post
	*/
	Vector3 operator-(Vector3 theInputVector);

	/**
	*	@brief operator to calculate the difference between two vectors
	*	@param theInputVector target vector
	*	@return a vector
	*	@pre minimum and maximum points must exist
	*	@post
	*/
	Vector3 operator+(Vector3 theInputVector);

	/**
	*	@brief operator to calculate the cross product of two vectors
	*	@param theInputVector target vector
	*	@return a vector
	*	@pre 
	*	@post
	*/
	Vector3 operator*(Vector3 &theInputVector);

	/**
	*	@brief operator that calculates the multiplication of vector with a scalar
	*	@param theInputVector target vector
	*	@return a vector scaled
	*	@pre
	*	@post
	*/
	Vector3 operator*(GLdouble &scalar);

	Vector3& operator-=(const Vector3 &rhs);

private:
	GLdouble x;	/*<! The x point value */
	GLdouble y; /*<! The y point value */
	GLdouble z; /*<! The z point value */
};

Vector3 operator-(const Vector3 &lhs, const Vector3 &rhs);

#endif
