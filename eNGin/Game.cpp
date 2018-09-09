#include "Game.h"

Game::Game() {
	shaysWorld = new Shay(this);
	state = SHAY_STATE;
	textures.resize(10);

	
}

Game::~Game()
{
	if (shaysWorld != NULL)
	{
		delete shaysWorld;
	}
}


void Game::Run() {
	Update();
	Draw();
}

void Game::Initialise() {
	shaysWorld->Init();
	centreX = 400;
	centreY = 250;
	//centreX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	//centreY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	deltaTime = clock();

	playerCharacter.SetMoveSpeed(0.05);
	playerCharacter.SetRotateSpeed(0.01);
	StartSong();
	textures[0].LoadTexture("data/spr_healthbar.png", 128, 128);
	textures[1].LoadTexture("data/spr_health_pellet.png", 32, 32);

	
}

void Game::Update() {

	if (state != SHAY_STATE)
	{
		DrawGUI();
	}

	switch (state)
	{
		case GAME_STATE:
			playerCharacter.Update();
			break;

		case MENU_STATE:
			break;
	}
	
}

void Game::Draw() {
	
	switch (state)
	{
		case MENU_STATE:
			break;

		case SHAY_STATE:
			if (shaysWorld != NULL)
			{
				shaysWorld->Draw();
			}
			break;

		case GAME_STATE:
			
			playerCharacter.Draw();

			glPushMatrix();
			glTranslatef(5.0, 0.0, 0.0);
			glScalef(1.0, 2.0, 1.0);
			alpha.Draw();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-5.0, 0.0, 0.0);
			glScalef(2.0, 1.0, 1.0);
			beta.Draw();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0.0, 0.0, 5.0);
			glScalef(1.0, 1.0, 2.0);
			gamma.Draw();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0.0, 0.0, -5.0);
			delta.Draw();
			glPopMatrix();

			glFlush();


			break;
	}
}

void Game::InputDown(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
	case 'A':
		playerCharacter.DirectionLR(-1);
		break;
	case 's':
	case 'S':
		playerCharacter.DirectionFB(-1);
		break;
	case 'd':
	case 'D':
		playerCharacter.DirectionLR(1);
		break;
	case 'w':
	case 'W':
		playerCharacter.DirectionFB(1);
		break;
	}
}

void Game::InputUp(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
	case 'A':
	case 'd':
	case 'D':
		playerCharacter.DirectionLR(0);
		break;
	case 'w':
	case 'W':
	case 's':
	case 'S':
		playerCharacter.DirectionFB(0);
		break;
	}
}

void Game::MouseLook(int x, int y) {
	int deadzone = 100;

	//If the mouse pointer has moved far enough, rotate camera
	if ((abs((long double)x) > deadzone) || (abs((long double)y) > deadzone)) {
		int deltaX = ((centreX - x) < 0) - (0 < (centreX - x));
		int deltaY = -(((centreY - y) < 0) - (0 < (centreY - y)));

		playerCharacter.DirectionLookLR(deltaX);
		playerCharacter.DirectionLookUD(deltaY);
	}
}

Shay * Game::GetShaysWorld() const
{
	return shaysWorld;
}

int Game::GetState() const
{
	return state;
}

void Game::SetState(int stateIn)
{
	state = stateIn;
}

void Game::StartSong()
{
	const char * filePath = "data/test_song.mp3";
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
	int result = 0;
	int flags = MIX_INIT_MP3;

	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		std::cout << "Failed to init SDL" << std::endl;
		exit(1);
	}

	if (flags != (result = Mix_Init(flags))) {
		std::cout << "Could not initialize mixer, result: " << std::endl;
		std::cout << "Mix_Init: " << Mix_GetError() << std::endl;
		exit(1);
	}

	Mix_Music * song = Mix_LoadMUS(filePath);
	Mix_PlayMusic(song, -1);
}

void Game::SwitchState()
{
	if (state == SHAY_STATE)
	{
		state = GAME_STATE;
		delete shaysWorld;
		shaysWorld = NULL;

	}

}

void Game::DrawGUI()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Set View mode to orthographic
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-8.0, 8.0, -8.0, 8.0, 1.0, 30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Draw Content
	std::vector<unsigned char> temp = textures[0].GetTexture();
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textures[0].GetWidth(), textures[0].GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, &temp[0]);

	glPushMatrix();
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, -1);
		glVertex3f(-8, 8, -1);
		glTexCoord2f(1.0, -1);
		glVertex3f(0, 8, -1);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(0, 0, -1);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-8, 0, -1);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	/*

	int l, i;
	char* st = (char*)"Test";
	l = strlen(st);
	glRasterPos3i(-3, -4, -1);
	for (i = 0; i < l; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[i]);
	}*/
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, 1, 1.0, 30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


}