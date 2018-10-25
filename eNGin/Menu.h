#ifndef MENU_H
#define MENU_H

class Game;

#include <gl/glut.h>
#include "Texture.h"

#define SHAY_STATE 0
#define MENU_STATE 1
#define GAME_STATE 2
#define PAUSE_MENU 5
#define DEATH_MENU 6
#define STORY_MENU 7

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

class Game;

class Menu
{
public:
	/**
	 *	Constructor with a parameter
	 *	Accepts a Game owner and initialises accordingly
	 */
	Menu(Game * ownerIn);

	/**
	 *	Function to draw a texture to the screen
	 *	@param displayingTexture The texture to draw on the screen
	 */
	void Draw(Texture displayingTexture);

	/**
	 *	Function to initialise the Menu class
	 */
	void Init();

	/**
	 *	A mouse callback function
	 *	Active only when in the menu state, allows selection of menu buttons
	 *	@param button The mouse button being clicked
	 *	@param state The state that button is in
	 *	@param x The x location on screen
	 *	@param y The y location on screen
	 */
	void MouseClick(int button, int state, int x, int y);

	/**
	 *	A normal function returning an int
	 *	@return The current game state
	 */
	int GetState();

	/**
	 *	A normal function accepting one parameter
	 *	@param settingState The state of the game to be set to
	 */
	void SetState(int settingState);

	/**
	 *	A normal function clearing the bit channels
	 */
	void Clear();

	/**
	 *	A normal function setting the menu state
	 *	@param settingState The state ot set the menu to
	 */
	void SetMenuState(int settingState);

	/**
	 *	A normal function returning an int
	 *	@return The current menu state
	 */
	int GetMenuState();

	/**
	 *	A normal function returning a boolean
	 *	@return exitScreen boolean
	 */
	bool GetExit();

	bool exitScreen; /*<! To determine fi the exit screen is showing */

private:
	Game* owner;		/*<!  The owner of the menu instance */
	
	float windowWidth;	/*<! The width of the current window */
	float windowHeight;	/*<! The height of the current window */
	
	float centreX;	/*<! The centre of the window width */
	float centreY;	/*<! The centre of the window height */
	
	int gameState;	/*<! The current gamme state value */
	int menuState;	/*<! The currennt menu state value */
};

#endif