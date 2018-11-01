#include "pch.h"

#include "Texture.h"


TEST(TestSuite004_TextureTesting, TextureTest000_TestObjectCreation)
{
	Texture tex;

	SUCCEED();
}


TEST(TestSuite004_TextureTesting, TextureTest001_TestObjectDestruction)
{
	Texture* tex;

	tex = new Texture();

	delete tex;

	SUCCEED();
}

TEST(TestSuite004_TextureTesting, TextureTest002_TestLoadTexture)
{
	Texture tex;

	tex.LoadTexture("data/hb_full_left.png", 32, 32);

	SUCCEED();
}

TEST(TestSuite004_TextureTesting, TextureTest003_TestGetData)
{
	Texture tex;
	std::vector<unsigned char> test;

	tex.LoadTexture("data/hb_full_left.png", 32, 32);

	test = tex.GetTexture();

	SUCCEED();
}

TEST(TestSuite004_TextureTesting, TextureTest004_TestGetWidth)
{
	Texture tex;
	unsigned int test;

	tex.LoadTexture("data/hb_full_left.png", 32, 32);

	test = tex.GetWidth();

	SUCCEED();
}

TEST(TestSuite004_TextureTesting, TextureTest005_TestGetHeight)
{
	Texture tex;
	unsigned int test;

	tex.LoadTexture("data/hb_full_left.png", 32, 32);

	test = tex.GetHeight();

	SUCCEED();
}
