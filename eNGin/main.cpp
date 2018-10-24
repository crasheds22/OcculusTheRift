#include <gl/glut.h>

#include "Game.h"

#define SHAY_STATE 0
#define MENU_STATE 1
#define GAME_STATE 2
#define PAUSE_MENU 5
#define DEATH_MENU 6

Game game;

// ratio of screen
float ratio;

// initializes setting
void myinit();

// display functions
void Display();
void reshape(int w, int h);

// keyboard and mouse functions
void keys(unsigned char key, int x, int y);
void releaseKeys(unsigned char key, int x, int y);

void Mouse(int button, int state, int x, int y);
void MouseMove(int x, int y);

//--------------------------------------------------------------------------------------
//  Main function 
//--------------------------------------------------------------------------------------
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 500);
	glutCreateWindow("Occulus The Rift");

	myinit();
	game.Initialise();
	game.GetMenu()->Init();

	glutIgnoreKeyRepeat(1);
	glutKeyboardUpFunc(releaseKeys);
	glutKeyboardFunc(keys);

	glutFullScreen();

	glutDisplayFunc(Display);
	glutIdleFunc(Display);

	glutMouseFunc(Mouse);

	glutMotionFunc(MouseMove);
	glutPassiveMotionFunc(MouseMove);

	glutReshapeFunc(reshape);
	glutMainLoop();

	return(0);
}

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

//--------------------------------------------------------------------------------------
//  Main Display Function
//--------------------------------------------------------------------------------------
void Display()
{
	game.Run();

	glFlush();
	glutSwapBuffers();
}

//--------------------------------------------------------------------------------------
void reshape(int w, int h)
{
	if((game.GetShaysWorld() != NULL) && (game.GetState()== SHAY_STATE))
	{
		game.GetShaysWorld()->SetWidthHeight(w, h);
	}
	
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0) 
		h = 1;

	game.SetCentreX(w / 2);
	game.SetCentreY(h / 2);
	
	ratio = 1.0f * w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(60, ratio, 0.5, 250000);
	glMatrixMode(GL_MODELVIEW);
}

//--------------------------------------------------------------------------------------
// Keyboard Functions
//--------------------------------------------------------------------------------------
void keys(unsigned char key, int x, int y)
{
	if (game.GetState() == SHAY_STATE)
	{
		game.GetShaysWorld()->DownKey(key, x,y);
	}
	else
	{
		switch (key)
		{
		case 27:
			exit(0);
			break;
		}
		game.InputDown(key, x, y);
	}
}

//--------------------------------------------------------------------------------------
void releaseKeys(unsigned char key, int x, int y)
{
	if (game.GetState() == SHAY_STATE)
	{
		game.GetShaysWorld()->UpKey(key,x,y);
	}
	else
	{
		game.InputUp(key, x, y);
	}
}

//--------------------------------------------------------------------------------------
//  Mouse Buttons
//--------------------------------------------------------------------------------------
void Mouse(int button, int state, int x, int y)
{
	if (game.GetState() == SHAY_STATE) {
		game.GetShaysWorld()->MouseClick(button, state, x, y);
	}

	if (game.GetState() == GAME_STATE) {
		if (game.GetMenu()->GetMenuState() == MAIN_MENU || game.GetMenu()->GetMenuState() == PAUSE_MENU || game.GetMenu()->GetMenuState() == DEATH_MENU)
		{
			game.GetMenu()->MouseClick(button, state, x, y);
		}
		else
		{
			game.MouseClick(button, state, x, y);
		}
	}

	if (game.GetState() == MENU_STATE) {
		game.GetMenu()->MouseClick(button, state, x, y);
	}
}

void MouseMove(int x, int y)
{
	bool showCursor = false;

	if (game.GetMenu()->GetMenuState() == MAIN_MENU || game.GetMenu()->GetMenuState() == PAUSE_MENU || game.GetMenu()->GetMenuState() == DEATH_MENU)
	{
		showCursor = true;
	}
	if (game.GetState() == GAME_STATE)
	{
		if (!showCursor)
		{
			glutWarpPointer(game.GetCentreX(), game.GetCentreY());
			game.MouseLook(x, y);
		}
	}
}
