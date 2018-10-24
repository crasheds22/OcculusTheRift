#include <pch.h>

#include "Vector3.h"

Vector3::Vector3() : x(0),
					 y(0),
					 z(0)
{

}

Vector3::Vector3(double posX, double posY, double posZ) : x(posX),
														  y(posY),
														  z(posZ)
{

}

void Vector3::SetPointX(double posX) {
	x = posX;
}

void Vector3::SetPointY(double posY) {
	y = posY;
}

void Vector3::SetPointZ(double posZ) {
	z = posZ;
}

double Vector3::GetPointX() const {
	return x;
}

double Vector3::GetPointY() const {
	return y;
}

double Vector3::GetPointZ() const {
	return z;
}

double Vector3::VectorMagnitude() 
{
	return sqrt((x * x + y * y + z * z));
}

double Vector3::DotProduct(Vector3 &in) {
	return x * in.x + y * in.y + z * in.z;
}

Vector3 Vector3::CrossProduct(Vector3 in) {
	Vector3 tempVec(y * in.GetPointZ() - z * in.GetPointY(),
					z * in.GetPointX() - x * in.GetPointZ(),
					x * in.GetPointY() - y * in.GetPointX());

	return tempVec;
}

Vector3 Vector3::UnitVector() 
{
	double mag = VectorMagnitude();
	
	x /= mag;
	y /= mag;
	z /= mag;

	return *this;
}

Vector3& Vector3::operator-=(const Vector3 &rhs) {
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;

	return *this;
}

Vector3& Vector3::operator+=(const Vector3 &rhs) {
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;

	return *this;
}

Vector3& Vector3::operator*=(const double &rhs) {
	x *= rhs;
	y *= rhs;
	z *= rhs;

	return *this;
}

Vector3 operator-(const Vector3 &lhs, const Vector3 &rhs) {
	Vector3 result(lhs);

	result -= rhs;

	return result;
}

Vector3 operator+(const Vector3 &lhs, const Vector3 &rhs) {
	Vector3 result(lhs);

	result += rhs;

	return result;
}

Vector3 operator*(const Vector3 &lhs, double rhs) {
	Vector3 result(lhs);

	result *= rhs;

	return result;
}

Vector3 operator*(double lhs, const Vector3 &rhs) {
	Vector3 result(rhs);

	result *= lhs;

	return result;
}
