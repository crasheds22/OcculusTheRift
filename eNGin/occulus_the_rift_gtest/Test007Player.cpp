
#include <math.h>

#include "pch.h"
#include <Player.h>
#include <Vector3.h>
#include <Quarternion.h>



TEST(TestSuite007_PlayerTesting, PlayerTest001_PlayerCreation)
{
	Player* thePlayer;

	SUCCEED();
}

TEST(TestSuite007_PlayerTesting, PlayerTest002_CameraRotation)
{
	Player* thePlayer;
	thePlayer = Player::GetInstance();

	double theRadian;
	Vector3 theAxis;
	Quarternion theResult, tempQuart;
	
	theRadian = 60 * (3.14159265359/ 180);
	theAxis = Vector3(0, cos(theRadian), sin(theRadian));
	tempQuart = Quarternion(0, 1, -1, 2);

	theResult = thePlayer->RotateCamera(theRadian, theAxis, tempQuart, 1.0);

	Vector3 theComparison;
	theComparison.SetPointX((10 + (4 * sqrt(3))) / 8);
	theComparison.SetPointY((1 + (2 * sqrt(3))) / 8);
	theComparison.SetPointZ((14 - (3 * sqrt(3))) / 8);

	EXPECT_EQ(theComparison.GetPointX(), theResult.GetQuartX());
	EXPECT_EQ(theComparison.GetPointY(), theResult.GetQuartY());
	EXPECT_EQ(theComparison.GetPointZ(), theResult.GetQuartZ());

	SUCCEED();
}