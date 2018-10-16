#ifndef Game_h
#define Game_h


#include <ctime>
#include <cmath>
#include <gl/glut.h>
#include <vector>
#include <map>
#include <cstdlib>
#include <iostream>

#include "Player.h"
#include "Menu.h"
#include "Model.h"
#include "Texture.h"
#include "Shay.h"
#include "MusicPlayer.h"
#include "Wall.h"
#include "Dungeon.h"
#include "LevelExit.h"
#include "Enemy.h"
#include "SoundPlayer.h"

#define SHAY_STATE 0
#define MENU_STATE 1
#define GAME_STATE 2
#define LOAD_STATE 3


#define tPlayer 0
#define tEnemy 1
#define tWALL 2
#define tPOWERUP 3
#define tEXIT 4

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
 *
 *	@author Liam Kinsella
 *	@version 1.2 Added Shays world black box and Finite state machine
 *	@date 08/09/2018
 *
 *	@author Aaron Thomson
 *	@version 1.3 Moved Update and Draw funcs to private
 *	@date 10-09-2018
 */
class Game {
public:
	/**
	 *	Default constructor
	 */
	Game();

	/**
	*	Default destructor
	*/
	~Game();

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

	void MouseClick(int button, int state, int x, int y);

	/**
	*	A normal member returning a pointer to a Shay object
	*	Returns a pointer to ShaysWorld
	*	@return Shay pointer
	*/
	Shay * GetShaysWorld() const;

	/**
	*	A normal member returning a pointer to a Menu object
	*	Returns a pointer to Menu
	*	@return Menu pointer
	*/
	Menu * GetMenu() const;

	/**
	*	A normal member returning the state value
	*	Returns the value representing the current state of the game
	*	@return the game state
	*/
	int GetState() const;

	/**
	*	A normal member taking 1 argument
	*	Used to set the state of the game
	*	@param stateIn the new state of the game
	*/
	void SetState(int stateIn);

	void SwitchState();

	void DrawGUI();

	int GetStage();

	int GetLevel();

	/**
	 *	A normal member taking one argument
	 *	Sets the value for the centre of the screen on the x axis
	 *	@param x The x value for the centre of the screen
	 */
	void SetCentreX(int x);

	/**
	 *	A normal member taking one argument
	 *	Sets the value for the centre of the screen on the y axis
	 *	@param y The y valkue for the centre of the screen
	 */
	void SetCentreY(int y);

	/**
	*	@brief to get the centre of the screen
	*	@param
	*	@return integer representing the centre x value
	*	@pre
	*	@post
	*/
	int GetCentreX();


	/**
	*	@brief to get the centre of the screen
	*	@param
	*	@return integer representing the centre y value
	*	@pre
	*	@post
	*/
	int GetCentreY();

	/**
	*	A normal member taking no arguments
	*	Used to add clear the entities from the level
	*/
	void ClearLevel();

	/**
	*	A normal member taking 3 arguments
	*	Used to add a wall to the list of game entities
	*	@param x The x position of the wall
	*	@param y The y position of the wall
	*	@param z The z position of the wall
	*/
	void AddWall(float x, float y, float z);

	/**
	*	A normal member taking 3 arguments
	*	Used to add an exit to the list of game entities
	*	@param x The x position of the wall
	*	@param y The y position of the wall
	*	@param z The z position of the wall
	*/
	void AddExit(float x, float y, float z);

	/**
	*	@brief to get the pointer to the player object
	*	@return memory address of the player
	*/
	Player* GetPlayer() const;

	void AddEnemy(float x, float y, float z, std::vector<Vector3> &f);

private:
	int count;
	float startTime;			/*<! start counting time variable> */
	float endTime;				/*<! end counting time variable> */
	float deltaTime;			/*<! A change in time variable> */
	int state;					/*<! an int representing current game state>*/

	int wallCount = 0;			/*<! used to place walls in the Entities map>*/

	Shay * shaysWorld;			/*<! shaysWorld black box>*/

	Player *playerCharacter;		/*<! The player in a scene */

	Menu * menuScreens;			/*<! The menu screens */

	MusicPlayer bgmControl;		/*<! Handles the BGM for the Game> */

	SoundPlayer soundControl;

	Dungeon* dungeon;	/*<!The level generator>*/

	std::vector<Model*> models;		/*<! All possible models to be used in the running of the game */
	std::vector<Texture> textures;	/*<! All possible textures to be used in the running of the game */

	std::map<int, std::vector<Actor*>> Entities; /*<! All entities in the current level */

	int centreX,		/*<! The x value of the centre of the screen */
		centreY;		/*<! The y value of the centre of the screen */

	bool exitScreen;

	bool menuScreen;

	/**
	 *	A normal member taking no arguments
	 *	Updates and reolves interactions between game entities
	 */
	void Update(float deltaTime);

	/**
	 *	A normal member taking no arguments
	 *	Draws the world, actors and the player in a scene
	 */
	void Draw();

	bool ProximityCull(Vector3 actorPosition, Vector3 &inputObject);


	int currentLevel; /*<! The current level of the game */
	int currentStage;/*<! The current stage of the game */

};

#endif
