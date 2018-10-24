#include <pch.h>

#include "Menu.h"
#include "Game.h"

Menu::Menu(Game* ownerIn) 
{
	owner = ownerIn;
}

void Menu::Draw(Texture displayingTexture)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	
	//Set View mode to orthographic
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-8.0, 8.0, -5.0, 5.0, 1.0, 30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Assign Texture
	std::vector<unsigned char> temp = displayingTexture.GetTexture();
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, displayingTexture.GetWidth(), displayingTexture.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, &temp[0]);

	glPushMatrix();
	glBegin(GL_QUADS);
	glTexCoord2f(-1.0, 1.0);
	glVertex3f(-4, -4, -1);
	glTexCoord2f(-1.0, 0.0);
	glVertex3f(-4, 4, -1);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(4, 4, -1);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(4, -4, -1);
	glEnd(); 
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, 1.0 * glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT), 1.0, 400.0);
	glMatrixMode(GL_MODELVIEW);

	glFlush();
}

void Menu::Init() 
{
	SetState(MENU_STATE);
}

void Menu::MouseClick(int button, int state, int x, int y) 
{
	windowWidth = glutGet(GLUT_WINDOW_WIDTH);
	windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
	centreX = windowWidth / 2;
	centreY = windowHeight / 2;

	float xLeft = windowWidth / 3.12585812357;
	float xRight = windowWidth / 1.47357065804;
	float yUp = windowHeight / 2.52631578947;
	float yDown = windowHeight / 1.8962962963;
	float yDistance = 138;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (menuState == PAUSE_MENU)
		{
			if ((x >= xLeft && x <= xRight) && (y >= yUp && y <= yDown))
			{
				owner->SwitchState();
			}
			else if ((x >= xLeft && x <= xRight) && (y >= yUp + yDistance && y <= yDown + yDistance))
			{
				exit(0);
			}
		}
		else if (menuState == DEATH_MENU)
		{
			if ((x >= xLeft && x <= xRight) && (y >= yUp && y <= yDown))
			{
				owner->Restart();
			}
			else if ((x >= xLeft && x <= xRight) && (y >= yUp + yDistance && y <= yDown + yDistance))
			{
				exit(0);
			}
		}
		else
		{
			yUp = windowHeight / 2.88721804511;
			yDown = windowHeight / 2.08695652174;

			if ((x >= xLeft && x <= xRight) && (y >= yUp && y <= yDown))
			{
				owner->SwitchState();
			}
			else if ((x >= xLeft && x <= xRight) && (y >= yUp + yDistance && y <= yDown + yDistance))
			{
				owner->SwitchState();
			}
			else if ((x >= xLeft && x <= xRight) && (y >= yUp + yDistance * 2 && y <= yDown + yDistance * 2))
			{
				exit(0);
			}
		}
		
	}
}

int Menu::GetState()
{
	return gameState;
}

void Menu::SetState(int settingState)
{
	gameState = settingState;
}

void Menu::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Menu::SetMenuState(int settingState)
{
	menuState = settingState;
}

int Menu::GetMenuState()
{
	return menuState;
}