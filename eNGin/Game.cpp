#include "Game.h"

Game::Game() {
	shaysWorld = new Shay(this);
	state = SHAY_STATE;
	
}

Game::~Game()
{
	delete shaysWorld;
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

	
}

void Game::Update() {

	if (state == GAME_STATE)
	{
		playerCharacter.Update();
	}

	
	
}

void Game::Draw() {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (state == GAME_STATE)
	{
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
	}
	else
	{
		if (shaysWorld != NULL)
		{
			shaysWorld->Draw();
		}
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
	int deadzone = 10;

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
	}

}
