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

	quartOne = Quarternion(1, 2, 3, 4).Normalize();
	quartTwo = Quarternion(5, 6, 7, 8).Normalize();

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

	quartOne = Quarternion(1, 2, 3, 4).Normalize();
	quartTwo = Quarternion(5, 6, 7, 8).Normalize();
	

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

/*
0.0		0 + 0.6i + 0.8j + 0k
0.1     0 + 0.46714i + 0.872923j - 0.140664k
0.2     0 + 0.314307i + 0.908523j - 0.275314k
0.3     0 + 0.148035i + 0.905278j - 0.398192k
0.4     0 - 0.0245656i + 0.863327j - 0.504046k
0.5     0 - 0.196116i + 0.784465j - 0.588348k
0.6     0 - 0.359282i + 0.672061j - 0.647496k
0.7     0 - 0.507086i + 0.530923j - 0.678959k
0.8     0 - 0.633209i + 0.367085j - 0.681392k
0.9     0 - 0.732259i + 0.187552j - 0.654692k
1       0 - 0.8i + 5.55112e-17j - 0.6k
*/

TEST(TestSuite006_QuarternionTesting, QuartTest007_QuartSlerp)
{
	Quarternion quartOne, quartTwo;
	Quarternion theResult;

	quartOne = Quarternion(0, 0.6, 0.8, 0);
	quartTwo = Quarternion(0, -0.8, 0, -0.6);

	/*
	for (int ii = 0; ii < 10; ii++)
	{
		theResult[ii] = quartOne.Slerp(quartTwo, 0.1*ii);

		std::cout	<< " W: " << theResult[ii].GetQuartW()
					<< " X: " << theResult[ii].GetQuartX()
					<< " Y: " << theResult[ii].GetQuartY()
					<< " Z: " << theResult[ii].GetQuartZ();
	}
	*/

	theResult = quartOne.Slerp(quartTwo, 0.1);


	EXPECT_EQ(0, theResult.GetQuartW());
	EXPECT_EQ(0.467140, theResult.GetQuartX());
	EXPECT_EQ(0.872923, theResult.GetQuartY());
	EXPECT_EQ(-0.140664, theResult.GetQuartZ());

	SUCCEED();
}





