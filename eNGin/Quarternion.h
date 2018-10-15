#pragma once

#include <math.h>
#include <gl/glut.h>
#include "Vector3.h"

class Quarternion
{
	public:
		Quarternion();
		/**
		*	@brief contructor with parameters for the creation of quarternions
		*	@param inputX 
		*	@param inputY
		*	@param inputZ
		*	@param inputW
		*	@return the angle in degrees? is returned
		*	@pre the comparison vector must exist
		*	@post
		*/
		Quarternion(GLdouble inputX, GLdouble inputY, GLdouble inputZ, GLdouble inputW);
		~Quarternion();

		/**
		*	@brief accessor for 
		*	@param inputX
		*	@param inputY
		*	@param inputZ
		*	@param inputW
		*	@return the angle in degrees? is returned
		*	@pre the comparison vector must exist
		*	@post
		*/
		void SetQuartX(GLdouble quartX);
		/**
		*	@brief accessor for
		*	@param inputX
		*	@param inputY
		*	@param inputZ
		*	@param inputW
		*	@return the angle in degrees? is returned
		*	@pre the comparison vector must exist
		*	@post
		*/
		void SetQuartY(GLdouble quartY);
		/**
		*	@brief accessor for
		*	@param inputX
		*	@param inputY
		*	@param inputZ
		*	@param inputW
		*	@return the angle in degrees? is returned
		*	@pre the comparison vector must exist
		*	@post
		*/
		void SetQuartZ(GLdouble quartZ);
		/**
		*	@brief accessor for
		*	@param inputX
		*	@param inputY
		*	@param inputZ
		*	@param inputW
		*	@return the angle in degrees? is returned
		*	@pre the comparison vector must exist
		*	@post
		*/
		void SetQuartW(GLdouble quartW);
		/**
		*	@brief accessor for
		*	@param inputX
		*	@param inputY
		*	@param inputZ
		*	@param inputW
		*	@return the angle in degrees? is returned
		*	@pre the comparison vector must exist
		*	@post
		*/
		GLdouble GetQuartX();
		/**
		*	@brief accessor for
		*	@param inputX
		*	@param inputY
		*	@param inputZ
		*	@param inputW
		*	@return the angle in degrees? is returned
		*	@pre the comparison vector must exist
		*	@post
		*/
		GLdouble GetQuartY();
		/**
		*	@brief accessor for
		*	@param inputX
		*	@param inputY
		*	@param inputZ
		*	@param inputW
		*	@return the angle in degrees? is returned
		*	@pre the comparison vector must exist
		*	@post
		*/
		GLdouble GetQuartZ();
		/**
		*	@brief accessor for
		*	@param inputX
		*	@param inputY
		*	@param inputZ
		*	@param inputW
		*	@return the angle in degrees? is returned
		*	@pre the comparison vector must exist
		*	@post
		*/
		GLdouble GetQuartW();

		/**
		*	@brief addition for quarternions
		*	@param inputQuart
		*	@return quarternion translation
		*	@pre 
		*	@post
		*/
		Quarternion operator+(Quarternion inputQuart);
		/**
		*	@brief subtraction for quarternions
		*	@param inputQuart
		*	@return quarternion translation
		*	@pre
		*	@post
		*/
		Quarternion operator-(Quarternion inputQuart);

		/**
		*	@brief pre-calculation for quarternion magnitude
		*	@param 
		*	@return quarternion squared
		*	@pre
		*	@post
		*/
		GLdouble QuartSquared();
		/**
		*	@brief calculation for quarternion magnitude
		*	@param
		*	@return quarternion magnitude
		*	@pre QuartSquared must return a valid value
		*	@post
		*/
		GLdouble QuartMagnitude();
		/**
		*	@brief calculation for quarternion normal
		*	@param
		*	@return quarternion normal
		*	@pre 
		*	@post
		*/
		Quarternion Normal();

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
		GLdouble DotProduct(Quarternion inputQuart);

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
		Quarternion ScalarProduct(GLdouble theScalar);

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
		*	@brief spherical linear interpolation
		*	@return quarternion
		*	@pre
		*	@post
		*/
		Quarternion Slerp(Quarternion targetQuart, GLdouble t);

	private:
		GLdouble x;
		GLdouble y;
		GLdouble z;
		GLdouble w;
};

