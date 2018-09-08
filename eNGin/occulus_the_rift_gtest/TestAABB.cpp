#include "pch.h"

#include <AABB.h>
#include <Vector3.h>
#include "Projection.h"

TEST(TestSuite1_AABBTesting, CollisionTest000_TestObjectCreation)
{
	AABB objectOne;
	AABB objectTwo;
	

	objectOne.SetMinPoint(0.0, 0.0, 0.00);
	objectOne.SetMaxPoint(1.0, 1.0, 1.0);

	objectTwo.SetMinPoint(2.0, 2.0, 2.0);
	objectTwo.SetMaxPoint(3.0, 3.0, 3.0);


	std::cout << "Test: " << objectOne.AABBtoAABB(objectTwo) << std::endl;

	SUCCEED();
}

TEST(TestSuite1_AABBTesting, CollisionTest001_TestCollisionObjectApart)
{
	AABB objectOne;
	AABB objectTwo;
	Vector3 inputMin;
	Vector3 inputMax;

	objectOne.SetMinPoint(0.0, 0.0, 0.00);
	objectOne.SetMaxPoint(1.0, 1.0, 1.0);

	objectTwo.SetMinPoint(2.0, 2.0, 2.0);
	objectTwo.SetMaxPoint(3.0, 3.0, 3.0);


	std::cout << "Test: " << objectOne.AABBtoAABB(objectTwo) << std::endl;

	EXPECT_FALSE(objectOne.AABBtoAABB(objectTwo));
}

TEST(TestSuite1_AABBTesting, CollisionTest002_TestCollisionObjectsCollided)
{
	AABB objectOne;
	AABB objectTwo;
	Vector3 inputMin;
	Vector3 inputMax;

	objectOne.SetMinPoint(0.0, 0.0, 0.00);
	objectOne.SetMaxPoint(1.0, 1.0, 1.0);

	objectTwo.SetMinPoint(0.5, 0.5, 0.5);
	objectTwo.SetMaxPoint(1.5, 1.5, 1.5);

	std::cout << "Test: " << objectOne.AABBtoAABB(objectTwo) << std::endl;

	EXPECT_TRUE(objectOne.AABBtoAABB(objectTwo));
}

TEST(TestSuite1_AABBTesting, CollisionTest003_TestObjectJustTouching)
{
	AABB objectOne;
	AABB objectTwo;
	Vector3 inputMin;
	Vector3 inputMax;

	objectOne.SetMinPoint(0.0, 0.0, 0.00);
	objectOne.SetMaxPoint(1.0, 1.0, 1.0);

	objectTwo.SetMinPoint(1.0, 1.0, 1.0);
	objectTwo.SetMaxPoint(2.0, 2.0, 2.0);


	std::cout << "Test: " << objectOne.AABBtoAABB(objectTwo) << std::endl;

	EXPECT_FALSE(objectOne.AABBtoAABB(objectTwo));
}

TEST(TestSuite_AABBTesting, CollisionTest004_TestObjectOverlap)
{
	AABB objectOne;
	AABB objectTwo;
	Vector3 inputMin;
	Vector3 inputMax;
	GLdouble testOverlap;

	objectOne.SetMinPoint(0.0, 0.0, 0.00);
	objectOne.SetMaxPoint(1.0, 1.0, 1.0);

	objectTwo.SetMinPoint(0.5, 0.5, 0.5);
	objectTwo.SetMaxPoint(1.5, 1.5, 1.5);

	Projection targetTest;

	targetTest = objectTwo.VectorProjection();

	testOverlap = objectOne.ProjectionOverlap(targetTest);

	std::cout << "Overlap test: " << testOverlap << std::endl;

	SUCCEED();
}

TEST(TestSuite_AABBTesting, CollisionTest005_TestObjectNotOverlap)
{
	AABB objectOne;
	AABB objectTwo;
	Vector3 inputMin;
	Vector3 inputMax;
	GLdouble testOverlap;

	objectOne.SetMinPoint(0.0, 0.0, 0.00);
	objectOne.SetMaxPoint(1.0, 1.0, 1.0);

	objectTwo.SetMinPoint(2.0, 2.0, 2.0);
	objectTwo.SetMaxPoint(3.0, 3.0, 3.0);


	Projection targetTest;

	targetTest = objectTwo.VectorProjection();

	testOverlap = objectOne.ProjectionOverlap(targetTest);

	std::cout << "Overlap test: " << testOverlap << std::endl;
	
	SUCCEED();
}

TEST(TestSuite_AABBTesting, CollisionTest006_TestObjectTouching)
{
	AABB objectOne;
	AABB objectTwo;
	Vector3 inputMin;
	Vector3 inputMax;
	GLdouble testOverlap;
	objectOne.SetMinPoint(0.0, 0.0, 0.00);
	objectOne.SetMaxPoint(1.0, 1.0, 1.0);

	objectTwo.SetMinPoint(1.0, 1.0, 1.0);
	objectTwo.SetMaxPoint(2.0, 2.0, 2.0);

	Projection targetTest;

	targetTest = objectTwo.VectorProjection();

	testOverlap = objectOne.ProjectionOverlap(targetTest);

	std::cout << "Overlap test: " << testOverlap << std::endl;
	EXPECT_FLOAT_EQ(0, testOverlap);
	SUCCEED();
}

TEST(TestSuite_AABBTesting, CollisionTest007_TestProjectionNormal)
{
	AABB objectOne;
	Vector3 inputMin;
	Vector3 inputMax;
	Vector3 resultVector;
	

	objectOne.SetMinPoint(0.0, 0.0, 0.00);
	objectOne.SetMaxPoint(1.0, 1.0, 1.0);

	objectOne.ProjectionNormal();

	resultVector = objectOne.ProjectionNormal();

	std::cout << "Projection Normal testX: " << resultVector.GetPointX() << std::endl;
	std::cout << "Projection Normal testY: " << resultVector.GetPointY() << std::endl;
	std::cout << "Projection Normal testZ: " << resultVector.GetPointZ() << std::endl;

	SUCCEED();
}

TEST(TestSuite_AABBTesting, CollisionTest008_TestVectorProjection)
{
	AABB objectOne;
	Vector3 inputMin;
	Vector3 inputMax;
	Projection resultProjection;


	objectOne.SetMinPoint(0.0, 0.0, 0.00);
	objectOne.SetMaxPoint(1.0, 1.0, 1.0);

	objectOne.ProjectionNormal();

	resultProjection = objectOne.VectorProjection();

	std::cout << "Projection Minima: " << resultProjection.GetMinProjection() << std::endl;
	std::cout << "Projection Maxima: " << resultProjection.GetMaxProjection() << std::endl;
	

	SUCCEED();
}

