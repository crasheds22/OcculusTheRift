#include <math.h>
#include <pch.h>


#include "Quarternion.h"



Quarternion::Quarternion()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
	w = 0.0;
}

Quarternion::Quarternion(GLdouble inputW, GLdouble inputX, GLdouble inputY, GLdouble inputZ)
{
	w = inputW;
	x = inputX;
	y = inputY;
	z = inputZ;
	
}

Quarternion::~Quarternion()
{

}

void Quarternion::SetQuartX(GLdouble quartX)
{
	x = quartX;
}

void Quarternion::SetQuartY(GLdouble quartY)
{
	y = quartY;
}

void Quarternion::SetQuartZ(GLdouble quartZ)
{
	z = quartZ;
}

void Quarternion::SetQuartW(GLdouble quartW)
{
	w = quartW;
}

GLdouble Quarternion::GetQuartX()
{
	return x;
}

GLdouble Quarternion::GetQuartY()
{
	return y;
}

GLdouble Quarternion::GetQuartZ()
{
	return z;
}

GLdouble Quarternion::GetQuartW()
{
	return w;
}

Quarternion Quarternion::operator+(Quarternion inputQuart)
{
	Quarternion resultQuart;

	resultQuart.x = x + inputQuart.GetQuartX();
	resultQuart.y = y + inputQuart.GetQuartY();
	resultQuart.z = z + inputQuart.GetQuartZ();
	resultQuart.w = w + inputQuart.GetQuartW();

	return resultQuart;
}

Quarternion Quarternion::operator-(Quarternion inputQuart)
{
	Quarternion resultQuart;

	resultQuart.x = x - inputQuart.GetQuartX();
	resultQuart.y = y - inputQuart.GetQuartY();
	resultQuart.z = z - inputQuart.GetQuartZ();
	resultQuart.w = w - inputQuart.GetQuartW();

	return resultQuart;
}

GLdouble Quarternion::QuartSquared()
{
	GLdouble resultQuart;

	resultQuart = x * x + y * y + z * z + w * w;
	
	return resultQuart;
}

GLdouble Quarternion::QuartMagnitude()
{
	return sqrt(QuartSquared());
}

Quarternion Quarternion::Normal()
{
	GLdouble inverseMagnitude;
	Quarternion resultQuart;

	inverseMagnitude = 1.0 / QuartMagnitude();

	resultQuart.x = x * inverseMagnitude;
	resultQuart.y = y * inverseMagnitude;
	resultQuart.z = z * inverseMagnitude;
	resultQuart.w = w * inverseMagnitude;
	
	return resultQuart;
}

Quarternion Quarternion::Conjugate()
{
	Quarternion resultQuart;

	resultQuart.x = -x;
	resultQuart.y = -y;
	resultQuart.z = -z;
	resultQuart.w = w;

	return resultQuart;
}

GLdouble Quarternion::DotProduct(Quarternion inputQuart)
{
	return x * inputQuart.GetQuartX() + y * inputQuart.GetQuartY() + z * inputQuart.GetQuartZ() + w * inputQuart.GetQuartW();
}


//w = a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z;
//x = a.y*b.z - a.z*b.y + a.w*b.x + a.x*b.w;
//y = a.z*b.x - a.x*b.z + a.w*b.y + a.y*b.w;
//z = a.x*b.y - a.y*b.x + a.w*b.z + a.z*b.w;

Quarternion Quarternion::CrossProduct(Quarternion inputQuart)
{
	Quarternion resultQuart;

	resultQuart.w = w * inputQuart.GetQuartW() - x * inputQuart.GetQuartX() - y * inputQuart.GetQuartY() - z * inputQuart.GetQuartZ();
	resultQuart.x = y * inputQuart.GetQuartZ() - z * inputQuart.GetQuartY() + w * inputQuart.GetQuartX() + x * inputQuart.GetQuartW();
	resultQuart.y = z * inputQuart.GetQuartX() - x * inputQuart.GetQuartZ() + w * inputQuart.GetQuartY() + y * inputQuart.GetQuartW();
	resultQuart.z = x * inputQuart.GetQuartY() - y * inputQuart.GetQuartX() + w * inputQuart.GetQuartZ() + z * inputQuart.GetQuartW();
	 
	return resultQuart;
}

Quarternion Quarternion::ScalarProduct(GLdouble theScalar)
{
	Quarternion resultQuart;

	resultQuart.x = x * theScalar;
	resultQuart.y = y * theScalar;
	resultQuart.z = z * theScalar;
	resultQuart.w = w * theScalar;

	return resultQuart;
}

Quarternion Quarternion::Inverse()
{
	Quarternion theConjugate;
	GLdouble theSquaredMagnitude;
	Quarternion resultQuart;

	theConjugate = Conjugate();
	theSquaredMagnitude = 1.0 / QuartSquared();
	resultQuart = theConjugate.ScalarProduct(theSquaredMagnitude);

	return resultQuart;
}

Quarternion Quarternion::QRotation(double theTheta, Vector3 theAxis)
{
	Quarternion rotationQuart, axisQuart, pqQuart, quartResult;
	Vector3 theNormal;
	double theRadian, sinTheta;

	// Normalise rotation axis to have unit length
	theNormal = theAxis.UnitVector();
	
	sinTheta = sin(theTheta / 2);

	// Convert to rotation quaternion
	rotationQuart.SetQuartX(theNormal.GetPointX() * sinTheta);  // theTheta should be in radians
	rotationQuart.SetQuartY(theNormal.GetPointY() * sinTheta);
	rotationQuart.SetQuartZ(theNormal.GetPointZ() * sinTheta);
	rotationQuart.SetQuartW(cos(theTheta / 2));

	return rotationQuart;
}

Quarternion Quarternion::Normalize()
{
	Quarternion tempQuat;

	tempQuat.x = x / QuartMagnitude();
	tempQuat.y = y / QuartMagnitude();
	tempQuat.z = z / QuartMagnitude();
	tempQuat.w = w / QuartMagnitude();

	return tempQuat;
}