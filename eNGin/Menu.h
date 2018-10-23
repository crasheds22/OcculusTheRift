#ifndef MENU_H
#define MENU_H

/**
 *	@class Menu
 *	@brief Base class for all menus : Main Menu, Pause Menu
 *	@details Holds mouse click information and game states
 *
 *	@author Vincent Tan
 *	@version 1.0 Base functions and drawing of Main Menu
 *	@date 02-10-2018
 *
 *	@author Vincent Tan
 *	@version 2.0 Mouse click on menu "buttons" produces output
 *	@date 03-10-2018
 *
 *	@author Vincent Tan
 *	@version 2.5 Mouse click on "buttons" change state of game
 *	@date 05-10-2018
 */

#include <gl/glut.h>
#include "Texture.h"

#define SHAY_STATE 0
#define MENU_STATE 1
#define GAME_STATE 2
#define PAUSE_MENU 5
#define DEATH_MENU 6

class Game;

class Menu
{
	public:
		Menu();
		 
		Menu(Game * ownerIn);

		void Draw(Texture displayingTexture);

		void Init();

		void MouseClick(int button, int state, int x, int y);

		int GetState();

		void SetState(int settingState);

		void Clear();

		void SetMenuState(int settingState);

		int GetMenuState();

		Game* owner;

	private:

		float windowWidth;
		float windowHeight;
		float centreX;
		float centreY;
		int gameState;
		int menuState;
};

#endif