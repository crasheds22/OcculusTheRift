#include "pch.h"
#include <SoundPlayer.h>

TEST(TestSuite009_SoundPlayerTesting, SoundPlayerTest001_SoundPlayerCreation)
{
	SoundPlayer soundPlayer;

	SUCCEED();
}


TEST(TestSuite009_SoundPlayerTesting, SoundPlayerTest002_SoundPlayerSoundTest)
{
	SoundPlayer soundPlayer;

	soundPlayer.PlaySound(0);

	SUCCEED();
}

TEST(TestSuite009_SoundPlayerTesting, SoundPlayerTest003_SoundPlayerDestruction)
{
	SoundPlayer* soundPlayer;

	soundPlayer = new SoundPlayer();

	delete soundPlayer;

	SUCCEED();
}