#include <pch.h>

#include "Menu.h"
#include "Game.h"

Menu::Menu(Game* ownerIn) 
{
	owner = ownerIn;
}

void Menu::DrawText(const char *text, int length, int x, int y)
{
	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(x, y, 0);
	glScalef(0.25, 0.25, 1);
	for (int i = 0; i < length; i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, (int)text[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
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

	if (menuState == DEATH_MENU && !exitScreen)
	{
		string text = "Score: " + to_string(owner->GetGameScore());
		DrawText(text.data(), text.size(), centreX / 2.05, centreY);
	}

	gluPerspective(60.0, 1.0 * glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT), 1.0, 400.0);
	glMatrixMode(GL_MODELVIEW);

	glFlush();
}

void Menu::Init() 
{
	SetState(MENU_STATE);
	exitScreen = false; 
	windowWidth = glutGet(GLUT_WINDOW_WIDTH);
	windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
	centreX = windowWidth / 2;
	centreY = windowHeight / 2;
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
	float yDistance = windowHeight / 5.5652173913;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (exitScreen)
		{
			xLeft = windowWidth / 4.01764705882;
			xRight = windowWidth / 1.333984375;
			yUp = windowHeight / 10.1052631579;
			yDown = windowHeight / 1.11304347826;

			if ((x >= xLeft && x <= xRight) && (y >= yUp && y <= yDown))
			{
				exit(0);
			}
		}
		else if (menuState == PAUSE_MENU)
		{
			if ((x >= xLeft && x <= xRight) && (y >= yUp && y <= yDown))
			{ 
				owner->SwitchState();
			}
			else if ((x >= xLeft && x <= xRight) && (y >= yUp + yDistance && y <= yDown + yDistance))
			{
				exitScreen = true;
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
				exitScreen = true;
			}
		}
		else if (menuState == STORY_MENU)
		{
			yUp = windowHeight / 1.41697416974;
			yDown = windowHeight / 1.19254658385;

			if ((x >= xLeft && x <= xRight) && (y >= yUp && y <= yDown))
			{
				owner->SwitchState();
			}
		}
		else
		{
			yUp = windowHeight / 2.88721804511;
			yDown = windowHeight / 2.08695652174;

			if ((x >= xLeft && x <= xRight) && (y >= yUp && y <= yDown))
			{
				menuState = STORY_MENU;
			}
			else if ((x >= xLeft && x <= xRight) && (y >= yUp + yDistance && y <= yDown + yDistance))
			{
				owner->Restart();
			}
			else if ((x >= xLeft && x <= xRight) && (y >= yUp + yDistance * 2 && y <= yDown + yDistance * 2))
			{
				exitScreen = true;
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

bool Menu::GetExit()
{
	return exitScreen;
}