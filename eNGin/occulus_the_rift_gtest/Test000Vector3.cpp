#include "pch.h"
#include <Vector3.h>

TEST(TestSuite000_Vector3Testing, VectorTest000_VectorMagnitude)
{
	Vector3 objectOne;
	GLdouble resultTest;

	objectOne = Vector3(0.0, 0.0, 0.0);
	resultTest = objectOne.VectorMagnitude();

	std::cout << "Magnitude: " << resultTest << std::endl;

	SUCCEED();
}

TEST(TestSuite000_Vector3Testing, VectorTest001_VectorMagnitude)
{
	Vector3 objectOne;
	GLdouble resultTest;

	objectOne = Vector3(1.0, 1.0, 1.0);
	resultTest = objectOne.VectorMagnitude();

	std::cout << "Magnitude: " << resultTest << std::endl;

	SUCCEED();
}
