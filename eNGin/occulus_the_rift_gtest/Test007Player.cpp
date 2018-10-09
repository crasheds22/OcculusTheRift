
#include <math.h>

#include "pch.h"
#include <Player.h>
#include <Vector3.h>
#include <Quarternion.h>



TEST(TestSuite007_PlayerTesting, PlayerTest001_QuartCreation)
{
	Player* thePlayer;

	SUCCEED();
}

TEST(TestSuite007_PlayerTesting, PlayerTest002_QuartCreation)
{
	Player* thePlayer;
	double theRadian;
	Vector3 theAxis;
	Quarternion theResult;

	theAxis = Vector3(1, -1, 2);
	theRadian = 60 * (3.14159265359/ 180);


	theResult = thePlayer->RotateCamera(theRadian, theAxis);

	Vector3 theComparison;
	theComparison.SetPointX((10 + (4 * sqrt(3))) / 8);
	theComparison.SetPointY((1 + (2 * sqrt(3))) / 8);
	theComparison.SetPointZ((14 + (8 * sqrt(3))) / 8);

	EXPECT_EQ(theComparison.GetPointX(), theResult.GetQuartX());
	EXPECT_EQ(theComparison.GetPointY(), theResult.GetQuartY());
	EXPECT_EQ(theComparison.GetPointZ(), theResult.GetQuartZ());

	SUCCEED();
}