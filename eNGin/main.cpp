#include <iostream>

#include <gl/glut.h>

#include "Game.h"

void Init();
void UpdateDisplay();
void Resize(int w, int h);
void KeyDown(unsigned char key, int x, int y);
void KeyUp(unsigned char key, int x, int y);
void MouseMove(int x, int y);

Game game;

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 500);
	glutCreateWindow("Oculus The Rift");

	Init();
	game.Initialise();

	glutDisplayFunc(UpdateDisplay);
	glutIdleFunc(UpdateDisplay);

	glutReshapeFunc(Resize);

	glutIgnoreKeyRepeat(1);
	//Normal key processing
	glutKeyboardFunc(KeyDown);
	glutKeyboardUpFunc(KeyUp);
	//Mouse func
	glutPassiveMotionFunc(MouseMove);

	glutMainLoop();

	return 0;
}

void Init() {
	glClearColor(97.0 / 255.0, 140.0 / 255, 185.0 / 255.0, 1.0);
	glLineWidth(5.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Create Camera
	GLdouble fov = 60;
	GLdouble aspect = 1;
	GLdouble nearVal = 0.5;
	GLdouble farVal = 100;

	gluPerspective(fov, aspect, nearVal, farVal);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
}

void UpdateDisplay() {
	game.Run();
}

void Resize(int w, int h) {
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0) h = 1;
	float ratio = 1.0f * w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45, ratio, 1, 250000);
	glMatrixMode(GL_MODELVIEW);
}

void KeyDown(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;
	}
	game.InputDown(key, x, y);
}

void KeyUp(unsigned char key, int x, int y) {
	game.InputUp(key, x, y);
}

void MouseMove(int x, int y) {
	glutWarpPointer(400, 250);
	//glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	game.MouseLook(x, y);
}
