#ifndef Game_h
#define Game_h

#include <ctime>
#include <cmath>
#include <gl/glut.h>
#include <vector>
#include <cstdlib>

#include "Player.h"
#include "Cube.h"
#include "Model.h"
#include "Texture.h"

/**
 *	@class Game
 *	@brief The 'task manager'
 *	@details Loads and manages all aspects of the Game
 *
 *	@author Aaron Thomson
 *	@version 1.0
 *	@date 14-08-2018
 *
 *	@author Liam Kinsella
 *	@version 1.1 Added mouse motion
 *	@date 06-09-2018
 */
class Game {
public:
	/**
	 *	Default constructor
	 */
	Game();

	/**
	 *	A normal member taking no arguments
	 *	Begins execution of game logic
	 */
	void Run();

	/**
	 *	A normal member taking no arguments
	 *	Initialises the game state and loads assets necessary
	 */
	void Initialise();

	/**
	 *	A normal member taking no arguments
	 *	Updates and reolves interactions between game entities
	 */
	void Update();

	/**
	 *	A normal member taking no arguments
	 *	Draws the world, actors and the player in a scene
	 */
	void Draw();

	/**
	 *	A normal member taking 3 arguments
	 *	Used to resolve keyboard presses
	 *	@param key The key pressed
	 *	@param x The mouse's x location on screen
	 *	@param y The mouse's y location on screen
	 */
	void InputDown(unsigned char key, int x, int y);

	/**
	 *	A normal member taking 3 arguments
	 *	Used to resolve key releases
	 *	@param key The key released
	 *	@param x The mouse's x location on screen
	 *	@param y The mouse's y location on screen
	 */
	void InputUp(unsigned char key, int x, int y);

	/**
	 *	A normal member taking 2 arguments
	 *	Used to resolve mouse motion on screen
	 *	@param x The mouse's x position on screen
	 *	@param y The mouse's y position on screen
	 */
	void MouseLook(int x, int y);

private:
	float deltaTime;			/*<! A change in time variable */

	Player playerCharacter;		/*<! The player in a scene */
	Cube alpha, beta, gamma, delta;

	std::vector<Model> models;		/*<! All possible models to be used in the running of the game */
	std::vector<Texture> textures;	/*<! All possible textures to be used in the running of the game */

	int centreX,		/*<! The x value of the centre of the screen */
		centreY;		/*<! The y value of the centre of the screen */

};

#endif
