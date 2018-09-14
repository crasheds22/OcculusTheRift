#include "pch.h"
#include <MusicPlayer.h>


TEST(TestSuite003_MusicTesting, MusicTest000_TestObjectCreation)
{
	MusicPlayer mp;

	SUCCEED();
}


TEST(TestSuite003_MusicTesting, MusicTest001_TestObjectDestruction)
{
	MusicPlayer* mp;

	mp = new MusicPlayer();

	delete mp;

	SUCCEED();
}

TEST(TestSuite003_MusicTesting, MusicTest002_TestSetSong)
{
	MusicPlayer mp;

	mp.SetSong(1);
	mp.PlaySong();

	SUCCEED();
}

TEST(TestSuite003_MusicTesting, MusicTest003_TestPlaySong)
{
	MusicPlayer mp;

	mp.PlaySong();

	SUCCEED();
}