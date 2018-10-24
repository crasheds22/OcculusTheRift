#ifndef VECTOR3_H
#define VECTOR3_H

/**
 *	@class Vector3
 *	@brief Defines a 3D vector by a point in space
 *
 *	@author Rebecca Lim
 *	@version 1.0
 *	@date 14-08-2018
 *
 *	@author Aaron Thomson
 *	@version 1.1: Changed Dot and Cross product to pass by reference
 *	@date 05-09-2018
 *
 *	@author Aaron Thomson
 *	@version 1.2: Added in additional operator overloads, removed function counterparts
 *	@date 24-10-2018
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
	Vector3(double posX, double posY, double posZ);

	//========================================
	// Set Methods
	/**
	 *	A normal member taking one argument
	 *	Sets the x point value
	 *	@param posX The desired x value
	 */
	void SetPointX(double posX);

	/**
	 *	A normal member taking one argument
	 *	Sets the y point value
	 *	@param posY The desired y value
	 */
	void SetPointY(double posY);

	/**
	 *	A normal member taking one argument
	 *	Sets the z point value
	 *	@param posZ The desired z value
	 */
	void SetPointZ(double posZ);
	//========================================

	//========================================
	// Get Methods
	/**
	 *	A normal member returning a double
	 *	@return The x point value
	 */
	double GetPointX() const;

	/**
	 *	A normal member returning a double
	 *	@return The y point value
	 */
	double GetPointY() const;

	/**
	 *	A normal member returning a double
	 *	@return The z point value
	 */
	double GetPointZ() const;
	//========================================

	//========================================
	// Utility
	/**
	 *	A utility function returning a double
	 *	Calculates the magnitude of the current vector
	 *
	 *	@return The magnitude of the vector
	 */
	double VectorMagnitude();

	/**
	 *	A utility function taking one argument and returning a double
	 *	Calculates the value of two vectors
	 *
	 *	@param in The Vector3 to multiply by
	 *	@return The result of the dot product of the two Vector3s
	 */
	double DotProduct(Vector3 &in);

	/**
	 *	A utility function taking one argument and returning a Vector3
	 *	Calculates the vector perpendicular of two other vectors
	 *
	 *	@param in The vector to multiply by
	 *	@return The resultant vector at 90 degrees to the other 2
	 */
	Vector3 CrossProduct(Vector3 in);

	/**
	 *	A utility function to calculate the unit vector 
	 *
	 *	@return The current vector at unit length
	 */
	Vector3 UnitVector();

	/**
	 *	Member overloaded -= operator
	 *	Returns the current vector subtracted by another vector
	 *
	 *	@param rhs The vector to subtract by
	 *	@return A reference to the new vector
	 */
	Vector3& operator-=(const Vector3 &rhs);

	/**
	 *	Member overloaded += operator
	 *	Returns the current vector added by another vector
	 *
	 *	@param rhs The vector to add by
	 *	@return A reference to the new vector
	 */
	Vector3& operator+=(const Vector3 &rhs);

	/**
	 *	Member overloaded *= operator
	 *	Returns the current vector multiplied by a scalar
	 *
	 *	@param rhs The value to multiply by
	 *	@return A reference to the new vector
	 */
	Vector3& operator*=(const double &rhs);

private:
	double x;	/*<! The x point value */
	double y; /*<! The y point value */
	double z; /*<! The z point value */
};

//===================================================================
// Non member operator overloads
Vector3 operator-(const Vector3 &lhs, const Vector3 &rhs);
Vector3 operator+(const Vector3 &lhs, const Vector3 &rhs);
Vector3 operator*(const Vector3 &lhs, double rhs);
Vector3 operator*(double lhs, const Vector3 &rhs);

#endif
