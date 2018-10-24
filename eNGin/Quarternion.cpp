#include <math.h>
#include <pch.h>

#include "Quarternion.h"

Quarternion::Quarternion() : w(0.0),
							 x(0.0),
							 y(0.0),
							 z(0.0)
{

}

Quarternion::Quarternion(double inputW, double inputX, double inputY, double inputZ) : w(inputW),
																							   x(inputX),
																							   y(inputY),
																							   z(inputZ)
{

}

void Quarternion::SetQuartX(double quartX)
{
	x = quartX;
}

void Quarternion::SetQuartY(double quartY)
{
	y = quartY;
}

void Quarternion::SetQuartZ(double quartZ)
{
	z = quartZ;
}

void Quarternion::SetQuartW(double quartW)
{
	w = quartW;
}

double Quarternion::GetQuartX()
{
	return x;
}

double Quarternion::GetQuartY()
{
	return y;
}

double Quarternion::GetQuartZ()
{
	return z;
}

double Quarternion::GetQuartW()
{
	return w;
}

double Quarternion::QuartSquared()
{
	return  x * x + y * y + z * z + w * w;
}

double Quarternion::QuartMagnitude()
{
	return sqrt(QuartSquared());
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

double Quarternion::DotProduct(Quarternion inputQuart)
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

Quarternion Quarternion::ScalarProduct(double theScalar)
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
	double theSquaredMagnitude;
	Quarternion resultQuart;

	theConjugate = Conjugate();
	theSquaredMagnitude = 1.0 / QuartSquared();
	resultQuart = theConjugate.ScalarProduct(theSquaredMagnitude);

	return resultQuart;
}

Quarternion Quarternion::QRotation(double theTheta, Vector3 theAxis)
{
	Quarternion rotationQuart, axisQuart, pqQuart, quartResult;
	Vector3 theUnitVector;
	double  sinTheta;

	// Normalise rotation axis to have unit length
	theUnitVector = theAxis.UnitVector();
	
	sinTheta = sin(theTheta / 2);

	// Convert to rotation quaternion
	rotationQuart.SetQuartX(theUnitVector.GetPointX() * sinTheta);  // theTheta should be in radians
	rotationQuart.SetQuartY(theUnitVector.GetPointY() * sinTheta);
	rotationQuart.SetQuartZ(theUnitVector.GetPointZ() * sinTheta);
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

Quarternion Quarternion::Slerp(Quarternion targetQuart, double t)
{
	Quarternion resultQuart;
	double cosineHalfTheta;
	double halfTheta;
	double sineHalfTheta;
	double ratioOne;
	double ratioTwo;

	cosineHalfTheta = DotProduct(targetQuart);

	if (abs(cosineHalfTheta) >= 1.0)
	{
		resultQuart.SetQuartW(w);
		resultQuart.SetQuartX(x);
		resultQuart.SetQuartY(y);
		resultQuart.SetQuartZ(z);

		return resultQuart;
	}

	halfTheta = acos(cosineHalfTheta);
	sineHalfTheta = sqrt(1.0 - cosineHalfTheta * cosineHalfTheta);

	if (abs(sineHalfTheta) < 0.001)
	{
		resultQuart.SetQuartW(w * 0.5 + targetQuart.GetQuartW() * 0.5);
		resultQuart.SetQuartX(x * 0.5 + targetQuart.GetQuartX() * 0.5);
		resultQuart.SetQuartY(y * 0.5 + targetQuart.GetQuartY() * 0.5);
		resultQuart.SetQuartZ(z * 0.5 + targetQuart.GetQuartZ() * 0.5);

		return resultQuart;
	}

	ratioOne = sin((1 - t) * halfTheta) / sineHalfTheta;
	ratioTwo = sin(t * halfTheta) / sineHalfTheta;

	resultQuart.SetQuartW(w * ratioOne + targetQuart.GetQuartW() * ratioTwo);
	resultQuart.SetQuartX(x * ratioOne + targetQuart.GetQuartX() * ratioTwo);
	resultQuart.SetQuartY(y * ratioOne + targetQuart.GetQuartY() * ratioTwo);
	resultQuart.SetQuartZ(z * ratioOne + targetQuart.GetQuartZ() * ratioTwo);

	return resultQuart;
}