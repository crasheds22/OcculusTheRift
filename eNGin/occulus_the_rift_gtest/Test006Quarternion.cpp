#include "pch.h"
#include <Quarternion.h>
#include <Vector3.h>

TEST(TestSuite006_QuarternionTesting, QuartTest001_QuartCreation)
{
	Quarternion theQuart;

	SUCCEED();
}

TEST(TestSuite006_QuarternionTesting, QuartTest002_QuartMultiplication)
{
	Quarternion quartOne;
	Quarternion quartTwo;
	Quarternion quartResult;

	quartOne = Quarternion(1, 0, 1, 0);
	quartTwo = Quarternion(1, 0.5, 0.5, 0.75);

	quartResult = quartOne.CrossProduct(quartTwo);
	
	EXPECT_FLOAT_EQ(0.5, quartResult.GetQuartW());
	EXPECT_FLOAT_EQ(1.25, quartResult.GetQuartX());
	EXPECT_FLOAT_EQ(1.5, quartResult.GetQuartY());
	EXPECT_FLOAT_EQ(0.25, quartResult.GetQuartZ());
}

TEST(TestSuite006_QuarternionTesting, QuartTest003_QuartMultiplication)
{
	Quarternion quartOne;
	Quarternion quartTwo;
	Quarternion quartResult;

	quartOne = Quarternion(1, 0, 1, 0);
	//quartTwo = Quarternion(1, 0.5, 0.5, 0.75);
	quartResult = quartOne.CrossProduct(quartOne);

	EXPECT_FLOAT_EQ(0, quartResult.GetQuartW());
	EXPECT_FLOAT_EQ(0, quartResult.GetQuartX());
	EXPECT_FLOAT_EQ(2, quartResult.GetQuartY());
	EXPECT_FLOAT_EQ(0, quartResult.GetQuartZ());
}

TEST(TestSuite006_QuarternionTesting, QuartTest004_QuartMultiplication)
{
	Quarternion quartOne;
	Quarternion quartTwo;
	Quarternion quartResult;

	quartOne = Quarternion(1, 2, 3, 4).Normal();
	quartTwo = Quarternion(5, 6, 7, 8).Normal();

	quartResult = quartOne.CrossProduct(quartTwo);

	EXPECT_FLOAT_EQ(0.182574, quartOne.GetQuartW());
	EXPECT_FLOAT_EQ(0.365148, quartOne.GetQuartX());
	EXPECT_FLOAT_EQ(0.547723, quartOne.GetQuartY());
	EXPECT_FLOAT_EQ(0.730297, quartOne.GetQuartZ());

	EXPECT_FLOAT_EQ(0.379049, quartTwo.GetQuartW());
	EXPECT_FLOAT_EQ(0.454859, quartTwo.GetQuartX());
	EXPECT_FLOAT_EQ(0.530669, quartTwo.GetQuartY());
	EXPECT_FLOAT_EQ(0.606478, quartTwo.GetQuartZ());

	EXPECT_FLOAT_EQ(0.830455, quartResult.GetQuartW());
	EXPECT_FLOAT_EQ(0.166091, quartResult.GetQuartX());
	EXPECT_FLOAT_EQ(0.415227, quartResult.GetQuartY());
	EXPECT_FLOAT_EQ(0.332182, quartResult.GetQuartZ());
}


TEST(TestSuite006_QuarternionTesting, QuartTest005_QuartMultiplication)
{
	Quarternion quartOne;
	Quarternion quartTwo;
	Quarternion quartResult;

	quartOne = Quarternion(1, 2, 3, 4).Normal();
	quartTwo = Quarternion(5, 6, 7, 8).Normal();
	

	quartResult = quartOne.CrossProduct(quartTwo);

	EXPECT_FLOAT_EQ(0.182574, quartOne.GetQuartW());
	EXPECT_FLOAT_EQ(0.365148, quartOne.GetQuartX());
	EXPECT_FLOAT_EQ(0.547723, quartOne.GetQuartY());
	EXPECT_FLOAT_EQ(0.730297, quartOne.GetQuartZ());

	EXPECT_FLOAT_EQ(0.379049, quartTwo.GetQuartW());
	EXPECT_FLOAT_EQ(0.454859, quartTwo.GetQuartX());
	EXPECT_FLOAT_EQ(0.530669, quartTwo.GetQuartY());
	EXPECT_FLOAT_EQ(0.606478, quartTwo.GetQuartZ());

	EXPECT_FLOAT_EQ(0.830455, quartResult.GetQuartW());
	EXPECT_FLOAT_EQ(0.166091, quartResult.GetQuartX());
	EXPECT_FLOAT_EQ(0.415227, quartResult.GetQuartY());
	EXPECT_FLOAT_EQ(0.332182, quartResult.GetQuartZ());
}

TEST(TestSuite006_QuarternionTesting, QuartTest006_QuartRotation)
{
	Quarternion theQuart;
	double theRadian;
	Vector3 theAxis, theAxis2;
	Quarternion qQuart, pQuart, qpQuart,theResult;

	theRadian = 60 * (3.14159265359 / 180);

	theAxis = Vector3(0, cos(theRadian), sin(theRadian));
	theAxis2 = Vector3(0, 0.5, sqrt(3) / 2);
	qQuart = theQuart.QRotation(theRadian, theAxis);

	pQuart.SetQuartW(0);
	pQuart.SetQuartX(1);
	pQuart.SetQuartY(-1);
	pQuart.SetQuartZ(2);

	qpQuart = qQuart.CrossProduct(pQuart);

	theResult = qpQuart.CrossProduct(qQuart.Inverse());

	Vector3 theComparison;
	theComparison.SetPointX((10 + (4 * sqrt(3))) / 8);
	theComparison.SetPointY((1 + (2 * sqrt(3))) / 8);
	theComparison.SetPointZ((14 - (3 * sqrt(3))) / 8);

	EXPECT_EQ(0, theResult.GetQuartW());
	EXPECT_EQ(theComparison.GetPointX(), theResult.GetQuartX());
	EXPECT_EQ(theComparison.GetPointY(), theResult.GetQuartY());
	EXPECT_EQ(theComparison.GetPointZ(), theResult.GetQuartZ());

	SUCCEED();
}





