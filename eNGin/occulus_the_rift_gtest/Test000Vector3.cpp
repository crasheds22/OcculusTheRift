#include "pch.h"
#include <math.h>
#include <Vector3.h>

TEST(TestSuite000_Vector3Testing, VectorTest000_VectorMagnitude)
{
	Vector3 objectOne;

	SUCCEED();
}

TEST(TestSuite000_Vector3Testing, VectorTest001_VectorMagnitude)
{
	Vector3 objectOne;
	GLdouble resultTest;

	objectOne = Vector3(0.0, 0.0, 0.0);
	resultTest = objectOne.VectorMagnitude();

	std::cout << "Magnitude: " << resultTest << std::endl;

	EXPECT_EQ(0, resultTest);
}


TEST(TestSuite000_Vector3Testing, VectorTest002_VectorMagnitude)
{
	Vector3 objectOne;
	GLdouble resultTest;

	objectOne = Vector3(1.0, 1.0, 1.0);
	resultTest = objectOne.VectorMagnitude();

	std::cout << "Magnitude: " << resultTest << std::endl;
	resultTest *= 100000;
	resultTest = round(resultTest);
	resultTest /= 100000;


	EXPECT_EQ(1.73205, resultTest);
}
