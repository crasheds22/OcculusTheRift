#include "pch.h"


#include <Vector3.h>
#include <Collider.h>
#include "Projection.h"

TEST(TestSuite001_AABBTesting, CollisionTest000_TestObjectCreation)
{
	Collider objectOne;
	Collider objectTwo;
	
	
	objectOne.SetMinPoint(0.0, 0.0, 0.00);
	objectOne.SetMaxPoint(1.0, 1.0, 1.0);

	objectTwo.SetMinPoint(2.0, 2.0, 2.0);
	objectTwo.SetMaxPoint(3.0, 3.0, 3.0);


	std::cout << "Test: " << objectOne.AABBtoAABB(objectTwo) << std::endl;

	SUCCEED();
}

TEST(TestSuite001_AABBTesting, CollisionTest001_TestCollisionObjectApart)
{
	Collider objectOne;
	Collider objectTwo;
	Vector3 inputMin;
	Vector3 inputMax;

	objectOne.SetMinPoint(0.0, 0.0, 0.00);
	objectOne.SetMaxPoint(1.0, 1.0, 1.0);

	objectTwo.SetMinPoint(2.0, 2.0, 2.0);
	objectTwo.SetMaxPoint(3.0, 3.0, 3.0);


	std::cout << "Test: " << objectOne.AABBtoAABB(objectTwo) << std::endl;

	EXPECT_FALSE(objectOne.AABBtoAABB(objectTwo));
}

TEST(TestSuite001_AABBTesting, CollisionTest002_TestCollisionObjectsCollided)
{
	Collider objectOne;
	Collider objectTwo;
	Vector3 inputMin;
	Vector3 inputMax;

	objectOne.SetMinPoint(0.0, 0.0, 0.00);
	objectOne.SetMaxPoint(1.0, 1.0, 1.0);

	objectTwo.SetMinPoint(0.5, 0.5, 0.5);
	objectTwo.SetMaxPoint(1.5, 1.5, 1.5);

	std::cout << "Test: " << objectOne.AABBtoAABB(objectTwo) << std::endl;

	EXPECT_TRUE(objectOne.AABBtoAABB(objectTwo));
}

TEST(TestSuite001_AABBTesting, CollisionTest003_TestObjectJustTouching)
{
	Collider objectOne;
	Collider objectTwo;
	Vector3 inputMin;
	Vector3 inputMax;

	objectOne.SetMinPoint(0.0, 0.0, 0.00);
	objectOne.SetMaxPoint(1.0, 1.0, 1.0);

	objectTwo.SetMinPoint(1.0, 1.0, 1.0);
	objectTwo.SetMaxPoint(2.0, 2.0, 2.0);


	std::cout << "Test: " << objectOne.AABBtoAABB(objectTwo) << std::endl;

	EXPECT_FALSE(objectOne.AABBtoAABB(objectTwo));
}

TEST(TestSuite001_AABBTesting, CollisionTest004_TestProjectionUnitNormal)
{

	Collider objectOne;
	Vector3 testNormal;

	objectOne.SetMinPoint(1.0, 1.0, 1.0);
	objectOne.SetMaxPoint(1.0, 2.0, 1.0);

	testNormal = objectOne.ProjectionNormal();

	std::cout << "Normal X: " << testNormal.GetPointX()  << std::endl;
	std::cout << "Normal Y: " << testNormal.GetPointY() << std::endl;
	std::cout << "Normal Z: " << testNormal.GetPointZ() << std::endl;

	SUCCEED();
}


TEST(TestSuite001_AABBTesting, CollisionTest005TestObjectOverlap)
{
	
	Collider objectOne;
	Collider objectTwo;
	GLdouble testOverlap;

	objectOne.SetMinPoint(1.0, 1.0, 1.00);
	objectOne.SetMaxPoint(2.0, 2.0, 1.0);

	objectTwo.SetMinPoint(1.5, 1.5, 1.5);
	objectTwo.SetMaxPoint(2.5, 2.5, 1.5);

	GLdouble targetTest;

	targetTest = objectTwo.VectorProjection001();

	testOverlap = objectOne.ProjectionOverlap001(targetTest);

	std::cout << "Overlap test: " << testOverlap << std::endl;

	SUCCEED();
}

TEST(TestSuite001_AABBTesting, DISABLED_CollisionTest005_TestObjectNotOverlap)
{
	Collider objectOne;
	Collider objectTwo;
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

TEST(TestSuite001_AABBTesting, CollisionTest006_TestObjectTouching)
{
	Collider objectOne;
	Collider objectTwo;
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

TEST(TestSuite001_AABBTesting, CollisionTest007_TestProjectionNormal)
{
	Collider objectOne;
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

TEST(TestSuite001_AABBTesting, CollisionTest008_TestVectorProjection)
{
	Collider objectOne;
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

TEST(TestSuite001_AABBTesting, CollisionTest009_TestVectorProjection)
{
	Collider objectOne;
	Vector3 inputMin;
	Vector3 inputMax;
	Projection resultProjection;


	objectOne.SetMinPoint(1.0, 1.0, 1.0);
	objectOne.SetMaxPoint(2.0, 2.0, 2.0);

	objectOne.ProjectionNormal();

	resultProjection = objectOne.VectorProjection();

	std::cout << "Projection Minima: " << resultProjection.GetMinProjection() << std::endl;
	std::cout << "Projection Maxima: " << resultProjection.GetMaxProjection() << std::endl;

	SUCCEED();
}

TEST(TestSuite001_AABBTesting, CollisionTest010_TestVectorProjection)
{
	Collider objectOne;
	Vector3 inputMin;
	Vector3 inputMax;
	Projection resultProjection;


	objectOne.SetMinPoint(2.0, 2.0, 2.0);
	objectOne.SetMaxPoint(3.0, 3.0, 3.0);

	objectOne.ProjectionNormal();

	resultProjection = objectOne.VectorProjection();

	std::cout << "Projection Minima: " << resultProjection.GetMinProjection() << std::endl;
	std::cout << "Projection Maxima: " << resultProjection.GetMaxProjection() << std::endl;

	SUCCEED();
}

TEST(TestSuite2_Vector3Testing, VectorTest001_VectorMagnitude)
{
	Vector3 objectOne;
	GLdouble resultTest;

	objectOne = Vector3(1.0, 1.0, 1.0);
	resultTest = objectOne.VectorMagnitude();

	std::cout << "Magnitude: " << resultTest << std::endl;

	SUCCEED();
}

TEST(TestSuite001_AABBTesting, CollisionTest011_TestMTV)
{
	Collider objectOne;
	Collider objectTwo;
	Vector3 resultMTV;


	objectOne.SetMinPoint(1.0, 1.0, 1.0);
	objectOne.SetMaxPoint(3.0, 4.0, 0.0);
	objectTwo.SetMinPoint(1.0, 1.0, 1.0);
	objectTwo.SetMaxPoint(5.0, -12.0, 0.0);

	

	resultMTV = objectOne.MinimumTranslationVector(objectTwo);

	std::cout << "Projection Minima: " << resultMTV.GetPointX() << std::endl;
	std::cout << "Projection Maxima: " << resultMTV.GetPointY() << std::endl;
	std::cout << "Projection Maxima: " << resultMTV.GetPointZ() << std::endl;

	SUCCEED();
}



