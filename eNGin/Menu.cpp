#include <pch.h>

#include <algorithm>
#include <math.h>

#include "Menu.h"
#include "Game.h"


Menu::Menu(Game* ownerIn) 
{
	owner = ownerIn;
}

void Menu::Draw(Texture displayingTexture)
{
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

	//Requires this for some reason
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

	gluPerspective(60.0, 1 * glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT), 0.5, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Menu::Init() 
{
	SetState(MENU_STATE);
}

void Menu::Update()
{
}

void Menu::MouseClick(int button, int state, int x, int y) 
{
	centreX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	centreY = glutGet(GLUT_WINDOW_HEIGHT) / 2;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		float xLeft = 254;
		float xRight = 542;
		float yUp = 173;
		float yDown = 239;

		if (centreX != 400)
		{
			xLeft = glutGet(GLUT_WINDOW_WIDTH) / 3.25;
			xRight = glutGet(GLUT_WINDOW_WIDTH) / 1.5;
		}

		if (centreY != 250)
		{
			yUp = glutGet(GLUT_WINDOW_HEIGHT) / 2.88;
			yDown = glutGet(GLUT_WINDOW_HEIGHT) / 2.08;
		}

		if ((x >= xLeft && x <= xRight) && (y >= yUp && y <= yDown))
		{

			owner->SetState(SHAY_STATE);
		}
		else if ((x >= xLeft && x <= xRight) && (y >= yUp + 90 && y <= yDown + 90))
		{
			owner->SetState(LOAD_STATE);
		}
		else if ((x >= xLeft && x <= xRight) && (y >= yUp + 180 && y <= yDown + 180))
		{
			exit(0);
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