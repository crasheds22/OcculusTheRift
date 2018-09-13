#include "Game.h"

Game::Game() 
{
	playerCharacter = Player::GetInstance();

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

void Game::Run() 
{
	Draw();

	Update();
}

void Game::Initialise() 
{
	shaysWorld->Init();
	
	//centreX = 400;
	//centreY = 250;
	centreX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	centreY = glutGet(GLUT_WINDOW_HEIGHT) / 2;

	deltaTime = clock();

	playerCharacter->SetMoveSpeed(0.05);
	playerCharacter->SetRotateSpeed(0.009);
	
	textures[0].LoadTexture("data/hb_empty_left.png", 32, 32);
	textures[1].LoadTexture("data/hb_empty_middle.png", 32, 32);
	textures[2].LoadTexture("data/hb_empty_right.png", 32, 32);

	textures[3].LoadTexture("data/hb_full_left.png", 32, 32);
	textures[4].LoadTexture("data/hb_full_middle.png", 32, 32);
	textures[5].LoadTexture("data/hb_full_right.png", 32, 32);
}

void Game::Update()
{
	bgmControl.PlaySong();

	if (state != SHAY_STATE)
	{
		DrawGUI();
	}

	switch (state)
	{
		case GAME_STATE:
			playerCharacter->Update();
			break;

		case MENU_STATE:
			break;
	}	
}

void Game::Draw()
{
	switch (state)
	{
		case MENU_STATE:
			DrawGUI();
			break;

		case SHAY_STATE:
			if (shaysWorld != NULL)
			{
				shaysWorld->Draw();
			}
			break;

		case GAME_STATE:
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			playerCharacter->Draw();
			
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
			DrawGUI();

			glFlush();

			break;
	}
}

void Game::InputDown(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a':
	case 'A':
		playerCharacter->DirectionLR(-1);
		break;
	case 's':
	case 'S':
		playerCharacter->DirectionFB(-1);
		break;
	case 'd':
	case 'D':
		playerCharacter->DirectionLR(1);
		break;
	case 'w':
	case 'W':
		playerCharacter->DirectionFB(1);
		break;
	case 't':
	case 'T':

		break;
	}
}

void Game::InputUp(unsigned char key, int x, int y) 
{
	switch (key) {
	case 'a':
	case 'A':
	case 'd':
	case 'D':
		playerCharacter->DirectionLR(0);
		break;
	case 'w':
	case 'W':
	case 's':
	case 'S':
		playerCharacter->DirectionFB(0);
		break;
	}
}

void Game::MouseLook(int x, int y)
{
	int deadzone = 100;

	//If the mouse pointer has moved far enough, rotate camera
	if ((abs((long double)x) > deadzone) || (abs((long double)y) > deadzone)) {
		int deltaX = ((centreX - x) < 0) - (0 < (centreX - x));
		int deltaY = -(((centreY - y) < 0) - (0 < (centreY - y)));

		playerCharacter->DirectionLookLR(deltaX);
		playerCharacter->DirectionLookUD(deltaY);
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

void Game::SwitchState()
{
	if (state == SHAY_STATE)
	{
		state = GAME_STATE;
		delete shaysWorld;
		shaysWorld = NULL;
		bgmControl.SetSong(1);
	}

}

void Game::DrawGUI()
{
	//Set View mode to orthographic
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-8.0, 8.0, -5.0, 5.0, 1.0, 30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float x1 = -7.5;
	float x2 = -6.5;

	float y1 = 4.5;
	float y2 = 3.5;
	int maxHealth = 5;
	int currentHealth = 3;
	int hbSlot = 0;

	for (int i = 0; i < maxHealth; i++)
	{

		//Choose Texture
		if (i == 0)
		{
			hbSlot = 3;
		}
		else
		{
			if (i == maxHealth - 1)
			{
				hbSlot = 5;
			}
			else
			{
				hbSlot = 4;
			}
		}

		if (i + 1 > currentHealth)
		{
			hbSlot -= 3;
		}

		//Assign Texture
		std::vector<unsigned char> temp = textures[hbSlot].GetTexture();
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textures[hbSlot].GetWidth(), textures[hbSlot].GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, &temp[0]);

		//Draw Healthbar
		glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, -1);
			glVertex3f(x1 + i, y1, -1);
			glTexCoord2f(1.0, -1);
			glVertex3f(x2 + i, y1, -1);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(x2 + i, y2, -1);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(x1 + i, y2, -1);
		glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}

	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, 1, 1.0, 30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void Game::SetCentreX(int x) {
	centreX = x;
}

void Game::SetCentreY(int y) {
	centreY = y;
}