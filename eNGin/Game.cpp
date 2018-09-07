#include "Game.h"

Game::Game() {
	
}

void Game::Run() {
	Update();

	Draw();
}

void Game::Initialise() {
	centreX = 400;
	centreY = 250;
	//centreX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	//centreY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	deltaTime = clock();

	playerCharacter.SetMoveSpeed(0.005);
	playerCharacter.SetRotateSpeed(0.0001);
}

void Game::Update() {
	playerCharacter.Update();
}

void Game::Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
