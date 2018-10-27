#include "pch.h"
#include <math.h>
#include <gl/glut.h>
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

TEST(TestSuite000_Vector3Testing, VectorTest003_VectorScalar)
{
	Vector3 objectOne;
	Vector3 objectTwo;
	GLdouble resultTest;

	objectOne = Vector3(4, 8, 10);
	objectTwo = Vector3(9.0, 2.0, 7.0);

	resultTest = objectOne.DotProduct(objectTwo);

	std::cout << "Scalar: " << resultTest << std::endl;

	EXPECT_EQ(122, resultTest);
}

TEST(TestSuite000_Vector3Testing, VectorTest004_VectorCrossProduct)
{
	Vector3 objectOne;
	Vector3 objectTwo;
	Vector3 resultComp;
	Vector3 resultTest;

	resultComp = Vector3(-3, 6, -3);

	objectOne = Vector3(2,3,4);
	objectTwo = Vector3(5,6,7);

	resultTest = objectOne.CrossProduct(objectTwo);

	std::cout << "Cross X: " << resultTest.GetPointX() << std::endl;
	std::cout << "Cross Y: " << resultTest.GetPointY() << std::endl;
	std::cout << "Cross Z: " << resultTest.GetPointZ() << std::endl;

	

	EXPECT_EQ(resultComp.GetPointX(), resultTest.GetPointX());
}

TEST(TestSuite000_Vector3Testing, DISABLED_VectorTest005_VectorScalarProduct)
{
	Vector3 objectOne;
	Vector3 resultComp;
	Vector3 resultTest;


	resultComp = Vector3(2, 2, 2);

	objectOne = Vector3(1, 1, 1);
	

	//resultTest = objectOne.MultiplyByScalar(2);

	std::cout << "Cross X: " << resultTest.GetPointX() << std::endl;
	std::cout << "Cross Y: " << resultTest.GetPointY() << std::endl;
	std::cout << "Cross Z: " << resultTest.GetPointZ() << std::endl;

	EXPECT_EQ(resultComp.GetPointX(), resultTest.GetPointX());
}

TEST(TestSuite000_Vector3Testing, DISABLED_VectorTest006_VectorUnitNormal)
{
	Vector3 objectOne;
	Vector3 objectTwo;
	Vector3 resultComp;
	Vector3 resultTest;

	objectOne = Vector3(3, 3, 4);
	objectTwo = Vector3(1, 2, 3);

	//resultTest = objectOne.UnitNormal(objectTwo);

	std::cout << "Cross X: " << resultTest.GetPointX() << std::endl;
	std::cout << "Cross Y: " << resultTest.GetPointY() << std::endl;
	std::cout << "Cross Z: " << resultTest.GetPointZ() << std::endl;

	EXPECT_EQ(resultComp.GetPointX(), resultTest.GetPointX());
}



