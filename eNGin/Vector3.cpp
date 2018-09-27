
#include <pch.h>
#include <math.h>

#include "Vector3.h"

Vector3::Vector3() : x(0),
					 y(0),
					 z(0)
{

}

Vector3::Vector3(GLdouble posX, GLdouble posY, GLdouble posZ) : x(posX),
																y(posY),
																z(posZ)
{
	x = posX;
	y = posY;
	z = posZ;
}

void Vector3::SetPointX(GLdouble posX) {
	x = posX;
}

void Vector3::SetPointY(GLdouble posY) {
	y = posY;
}

void Vector3::SetPointZ(GLdouble posZ) {
	z = posZ;
}

GLdouble Vector3::GetPointX() const {
	return x;
}

GLdouble Vector3::GetPointY() const {
	return y;
}

GLdouble Vector3::GetPointZ() const {
	return z;
}

GLdouble Vector3::VectorMagnitude() 
{
	return sqrt((x * x + y * y + z * z));
}

GLdouble Vector3::DotProduct(Vector3 &in) {
	return x * in.x + y * in.y + z * in.z;
}

Vector3 Vector3::CrossProduct(Vector3 &in) {
	Vector3 tempVec(y * in.GetPointZ() - z * in.GetPointY(),
					z * in.GetPointX() - x * in.GetPointZ(),
					x * in.GetPointY() - y * in.GetPointX());

	return tempVec;
}

Vector3 Vector3::MultiplyByScalar(GLdouble scalar) {
	Vector3 tempVec(x * scalar,
					y * scalar,
					z * scalar);

	return tempVec;
}

Vector3 Vector3::UnitNormal(Vector3 &inputVector) {
	GLdouble mag = VectorMagnitude();
	Vector3 normalVector;
	Vector3 resultVector;

	normalVector = CrossProduct(inputVector);
	resultVector.SetPointX(normalVector.GetPointX() / mag);
	resultVector.SetPointY(normalVector.GetPointY() / mag);
	resultVector.SetPointZ(normalVector.GetPointZ() / mag);

	return resultVector;
}

GLdouble Vector3::VectorAngle(Vector3 targetVector)
{
	GLdouble tempDotResult;
	GLdouble magnitudeOne;
	GLdouble magnitudeTwo;
	GLdouble magnitudeProduct;
	GLdouble resultAngle;

	tempDotResult = DotProduct(targetVector);
	magnitudeOne = VectorMagnitude();
	magnitudeTwo = targetVector.VectorMagnitude();
	magnitudeProduct = magnitudeOne * magnitudeTwo;
	resultAngle = acos(tempDotResult / magnitudeProduct);

	return resultAngle;
}

Vector3 Vector3::SubtractVector(Vector3 theInputVector)
{
	Vector3 resultVector;

	resultVector.x = x - theInputVector.x;
	resultVector.y = y - theInputVector.y;
	resultVector.z = z - theInputVector.z;

	return resultVector;
}

Vector3 Vector3::AddVector(Vector3 theInputVector)
{
	Vector3 resultVector;

	resultVector.x = x + theInputVector.x;
	resultVector.y = y + theInputVector.y;
	resultVector.z = z + theInputVector.z;

	return resultVector;
}