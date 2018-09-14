#include "pch.h"

#include <Game.h>

TEST(TestSuite003_Vector3Testing, GameTest001_GameCreation)
{
	Game theGame;

	SUCCEED();
}

TEST(TestSuite003_Vector3Testing, DISABLED_GameTest002_GameInitialisation)
{
	Game theGame;

	theGame.Initialise();

	SUCCEED();
}

