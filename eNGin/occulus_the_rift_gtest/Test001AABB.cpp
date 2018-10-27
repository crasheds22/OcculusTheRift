#include "pch.h"

#include <Vector3.h>
#include <Collider.h>


TEST(TestSuite001_AABBTesting, CollisionTest000_TestObjectCreation)
{
	Collider objectOne;
	Collider objectTwo;
	
	
	objectOne.SetMinPoint(0.0, 0.0, 0.0);
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

TEST(TestSuite001_AABBTesting, DISABLED_CollisionTest004_TestProjectionUnitNormal)
{

	Collider objectOne;
	Vector3 testNormal;

	objectOne.SetMinPoint(1.0, 1.0, 1.0);
	objectOne.SetMaxPoint(1.0, 2.0, 1.0);

	//testNormal = objectOne.ProjectionNormal();

	SUCCEED();
}

TEST(TestSuite001_AABBTesting, DISABLED_CollisionTest005_TestProjectionUnitNormal)
{
	Collider objectOne;
	Vector3 inputMin;
	Vector3 inputMax;
	Vector3 resultVector;


	objectOne.SetMinPoint(3.0, 1.0, 1.00);
	objectOne.SetMaxPoint(1.0, 3.0, 1.0);

	//resultVector = objectOne.ProjectionNormal();

	SUCCEED();
}

TEST(TestSuite001_AABBTesting, DISABLED_CollisionTest006_TestVectorProjection)
{
	Collider objectOne;
	Vector3 inputMin;
	Vector3 inputMax;
	//Projection resultProjection;
	Vector3 resultProjection;
	

	objectOne.SetMinPoint(1.0, 1.0, 1.0);
	objectOne.SetMaxPoint(1.0, 3.0, 1.0);

	//resultProjection = objectOne.VectorProjection();

	SUCCEED();
}

TEST(TestSuite001_AABBTesting, DISABLED_CollisionTest007_TestVectorProjection)
{
	Collider objectOne;
	Vector3 inputMin;
	Vector3 inputMax;
	//Projection resultProjection;
	Vector3 resultProjection;


	objectOne.SetMinPoint(1.0, 1.0, 1.0);
	objectOne.SetMaxPoint(2.0, 2.0, 2.0);

	//objectOne.ProjectionNormal();

	//resultProjection = objectOne.VectorProjection();

	//std::cout << "Projection Maxima: " << resultProjection.GetMaxProjection() << std::endl;
	//std::cout << "Projection Minima: " << resultProjection.GetMinProjection() << std::endl;
	//std::cout << "Projection: " << resultProjection.GetMinProjection() << std::endl;

	SUCCEED();
}

TEST(TestSuite001_AABBTesting, DISABLED_CollisionTest008_TestVectorProjection)
{
	Collider objectOne;
	Vector3 inputMin;
	Vector3 inputMax;
	//Projection resultProjection;
	Vector3 resultProjection;


	objectOne.SetMinPoint(1.0, 1.0, 1.0);
	objectOne.SetMaxPoint(1.0, 3.0, 1.0);

	//objectOne.ProjectionNormal();

	//resultProjection = objectOne.VectorProjection();

	//std::cout << "Projection Maxima: " << resultProjection.GetMaxProjection() << std::endl;
	//std::cout << "Projection Minima: " << resultProjection.GetMinProjection() << std::endl;
	//std::cout << "Projection: " << resultProjection.GetMinProjection() << std::endl;

	SUCCEED();
}




TEST(TestSuite001_AABBTesting, DISABLED_CollisionTest009TestObjectOverlap)
{
	
	Collider objectOne;
	Collider objectTwo;
	Vector3 testOverlap;

	objectOne.SetMinPoint(1.0, 1.0, 1.0);
	objectOne.SetMaxPoint(1.0, 2.0, 1.0);

	objectTwo.SetMinPoint(1.0, 1.5, 1.0);
	objectTwo.SetMaxPoint(1.0, 2.5, 1.0);

	//Projection targetTest;
	Vector3 targetTest;

	//targetTest = objectTwo.VectorProjection();

	//testOverlap = objectOne.ProjectionOverlap(targetTest);

	//std::cout << "Overlap test: " << testOverlap << std::endl;

	SUCCEED();
}

TEST(TestSuite001_AABBTesting, DISABLED_CollisionTest010_TestObjectNotOverlap)
{
	Collider objectOne;
	Collider objectTwo;
	Vector3 inputMin;
	Vector3 inputMax;
	Vector3 testOverlap;

	objectOne.SetMinPoint(0.0, 0.0, 0.00);
	objectOne.SetMaxPoint(1.0, 1.0, 1.0);

	objectTwo.SetMinPoint(2.0, 2.0, 2.0);
	objectTwo.SetMaxPoint(3.0, 3.0, 3.0);

	//Projection targetTest;
	Vector3 targetTest;

	//targetTest = objectTwo.VectorProjection();

	//testOverlap = objectOne.ProjectionOverlap(targetTest);

	//std::cout << "Overlap test: " << testOverlap << std::endl;
	
	SUCCEED();
}

TEST(TestSuite001_AABBTesting, DISABLED_CollisionTest011_TestObjectTouching)
{
	Collider objectOne;
	Collider objectTwo;
	Vector3 inputMin;
	Vector3 inputMax;
	Vector3 testOverlap;

	objectOne.SetMinPoint(0.0, 0.0, 0.00);
	objectOne.SetMaxPoint(1.0, 1.0, 1.0);

	objectTwo.SetMinPoint(1.0, 1.0, 1.0);
	objectTwo.SetMaxPoint(2.0, 2.0, 2.0);

	//Projection targetTest;
	Vector3 targetTest;

	//targetTest = objectTwo.VectorProjection();

	//testOverlap = objectOne.ProjectionOverlap(targetTest);

	//std::cout << "Overlap test: " << testOverlap << std::endl;
	//EXPECT_FLOAT_EQ(0, testOverlap);
	
	SUCCEED();
}






TEST(TestSuite001_AABBTesting, DISABLED_CollisionTest012_TestMTV)
{
	Collider objectOne;
	Collider objectTwo;
	Vector3 resultMTV;
	/*
	objectOne.SetMinPoint(0.0, 0.0, 0.00);
	objectOne.SetMaxPoint(1.0, 1.0, 1.0);

	objectTwo.SetMinPoint(0.5, 0.5, 0.5);
	objectTwo.SetMaxPoint(1.5, 1.5, 1.5);
	*/
	
	objectOne.SetMinPoint(1.0, 1.0, 1.0);
	objectOne.SetMaxPoint(3.0, 3.0, 3.0);

	objectTwo.SetMinPoint(1.0, 3.0, 1.0);
	objectTwo.SetMaxPoint(3.0, 1.0, 1.0);
	
	//resultMTV = objectOne.MinimumTranslationVector(objectTwo);

	std::cout << "MTV X: " << resultMTV.GetPointX() << std::endl;
	std::cout << "MTV Y: " << resultMTV.GetPointY() << std::endl;
	std::cout << "MTV Z: " << resultMTV.GetPointZ() << std::endl;

	SUCCEED();
}



