#include "pch.h"
#include<Game.h>
#include <Dungeon.h>

TEST(TestSuite008_DungeonTesting, DungeonTest001_DungeonCreation)
{
	Game theGame;
	Dungeon * dungeon;

	dungeon = new Dungeon(&theGame);

	delete dungeon;

	SUCCEED();
}


TEST(TestSuite008_DungeonTesting, DungeonTest002_DungeonDestruction)
{
	Game theGame;
	Dungeon * dungeon;

	dungeon = new Dungeon(&theGame);

	delete dungeon;

	SUCCEED();
}