
#include <SDL.h>

#include "pch.h"
#include <gl/glut.h>
#include <iostream>

#define SHAY_STATE 0
#define MENU_STATE 1
#define GAME_STATE 2
#define PAUSE_MENU 5
#define DEATH_MENU 6
#define STORY_MENU 7

// ratio of screen
float ratio;

// initializes setting
void myinit();




//--------------------------------------------------------------------------------------
//  Initialize Settings
//--------------------------------------------------------------------------------------
void myinit()
{
	glClearColor(97.0 / 255.0, 140.0 / 255.0, 185.0 / 255.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Create Camera
	GLdouble fov = 60;
	GLdouble aspect = 1 * glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT);
	GLdouble nearVal = 1;
	GLdouble farVal = 100;

	gluPerspective(fov, aspect, nearVal, farVal);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0, 1.75, 0.0,
		0.0, 1.75, -1,
		0.0f, 1.0f, 0.0f);
}

int main(int argc, char **argv) {
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 500);
	glutCreateWindow("Oculus The Rift");

	myinit();
	
	
	::testing::InitGoogleTest(&argc, argv);	
	
	return RUN_ALL_TESTS();
}