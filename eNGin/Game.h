#ifndef GAME_H
#define GAME_H

#include <gl/glut.h>
#include <vector>
#include <map>
#include <string>

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
#include "GUI.h"
#include "Projectile.h"
#include "Coin.h"

#define SHAY_STATE 0
#define MENU_STATE 1
#define GAME_STATE 2
#define LOAD_STATE 3
#define MAIN_MENU 4
#define PAUSE_MENU 5
#define DEATH_MENU 6
#define STORY_MENU 7

#define tPlayer 0
#define tEnemy 1
#define tWALL 2
#define tPOWERUP 3
#define tEXIT 4
#define tProjectile 5

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
 *
 *	@author Rebecca Lim
 *	@version 2.0: Added collision detection
 *	@date 21-09-2018
 *
 *	@author Liam Kinsella
 *	@version 3.0: Added levels and dungeon generator
 *	@date 03-10-2018
 *
 *	@author Liam Kinsella
 *	@version 3.1: Added level exits
 *	@date 04-10-2018
 *	
 *	@author Vincent Tran
 *	@version 3.2: Added menu screens
 *	@date 05-10-2018
 *
 *	@author Aaron Thomson
 *	@version 3.3 Changed entity list to accept Actor*
 *	@date 10-10-2018
 *
 *	@author Liam Kinsella
 *	@version 3.4: Added sound player
 *	@date 10-10-2018
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

	/**
	 *	A normal member taking 4 arguments
	 *	Used to resolve mouse clicks
	 *	@param button The mouse button presed
	 *	@param state The state of that button
	 *	@param x The x location of the mouse on screen
	 *	@param y The y location of the mouse on screen
	 */
	void MouseClick(int button, int state, int x, int y);

	/**
	*	A normal member returning a pointer to a Shay object
	*	Returns a pointer to ShaysWorld
	*	@return Shay pointer
	*/
	Shay *GetShaysWorld() const;

	/**
	*	A normal member returning a pointer to a Menu object
	*	Returns a pointer to Menu
	*	@return Menu pointer
	*/
	Menu *GetMenu() const;

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

	/**
	 *	A normal member allowing the switching of states
	 */
	void SwitchState();

	/**
	 *	Draws the GUI on the screen (replace with GUI::DrawGUI)
	 */
	void DrawGUI();

	/**
	 *	A normal function returning an int
	 *	@return The stage number
	 */
	int GetStage();

	/**
	 *	A normal function returning an int
	 *	@return The level number
	 */
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
	 *	Returns the x value of the centre of the screen
	 *	@return The x value of the screen centre
	 */
	int GetCentreX();

	/**
	 *	Returns the y value of the centre of the screen
	 *	@return The y value of the screen centre
	 */
	int GetCentreY();

	/**
	*	A normal member taking no arguments
	*	Used to clear the entities from the level
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
	*	Used to add a coin to the list of game entities
	*	@param x The x position of the coin
	*	@param y The y position of the coin
	*	@param z The z position of the coin
	*/
	void AddCoin(float x, float y, float z);

	/**
	*	A normal member taking 3 arguments
	*	Used to add an exit to the list of game entities
	*	@param x The x position of the exit
	*	@param y The y position of the exit
	*	@param z The z position of the exit
	*/
	void AddExit(float x, float y, float z);

	/**
	*	Returns the playerCharacter in the scene
	*	@return A pointer to the Player character
	*/
	Player* GetPlayer() const;

	/**
	 *	A normal member taking 4 arguments
	 *	Used to add an enemy to the list of game entities
	 *	@param x The x position of the Enemy
	 *	@param y The y position of the Enemy
	 *	@param z The z position of the Enemy
	 */
	void AddEnemy(float x, float y, float z);

	/**
	 *	Returns the list of textures
	 *	@return All the textures currently loaded
	 */
	std::vector<Texture> GetTexture();
	
	/**
	 *	A normal member taking 4 arguments
	 *	Used to add a projectile to the list of entities
	 *	@param owner The entity that fired the projectile
	 *	@param start The start position of the projectile
	 *	@param dir The direction to move in
	 *	@param tex The texture value to retrieve
	 */
	void AddProjectile(Actor* owner, Vector3 start, Vector3 dir, int tex);

	/**
	*	Returns the gameScore
	*	@return Game Score
	*/
	int GetGameScore();

	/**
	*	A normal member taking no arguments
	*	Restarts game world
	*/
	void Restart();

	/**
	*	A normal member taking 1 arguments
	*	Used to play a sound from within an actor
	*	@param index of the sound to play
	*/
	void PlaySoundAt(int index);


	/**
	*	A normal member taking 3 arguments
	*	Draws text to screen
	*	@param x pos of text
	*	@param y pos of text
	*	@param text the text to draw
	*/
	void DrawText(int x, int y, std::string text);

private:
	int count;					/*<! Used to determine first run or not */
	int gameScore;				/*<! Used to track the player's score in game */
	float startTime;			/*<! start counting time variable> */
	float endTime;				/*<! end counting time variable> */
	float deltaTime;			/*<! A change in time variable> */
	float currentSpeed;
	int state;					/*<! an int representing current game state>*/

	int wallCount = 0;			/*<! used to place walls in the Entities map>*/

	Shay *shaysWorld;			/*<! shaysWorld black box>*/

	Player *playerCharacter;	/*<! The player in a scene */

	Menu *menuScreens;			/*<! The menu screens */

	MusicPlayer bgmControl;		/*<! Handles the BGM for the Game> */

	SoundPlayer soundControl;	/*<! Handles all the sounds for the game */

	Dungeon* dungeon;			/*<!The level generator>*/

	GUI* playerInterface;		/*<! The player interface */

	std::vector<Model*> models;		/*<! All possible models to be used in the running of the game */
	std::vector<Texture> textures;	/*<! All possible textures to be used in the running of the game */

	std::map<int, std::vector<Actor*>> Entities; /*<! All entities in the current level */

	int centreX,		/*<! The x value of the centre of the screen */
		centreY;		/*<! The y value of the centre of the screen */

	bool pauseScreen;	/*<! To determine if the pause screen is showing */
	
	bool deathScreen;	/*<! To determine if the death screen is showing */

	bool mainScreen;	/*<! To determine if the main menu screen is showing */

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

	/**
	 *	A normal member taking 2 arguments
	 *	Checks the distance between two points and whether they have intersected
	 *	@param actorPosition The position of the actor to check
	 *	@param inputObject The objec to check if colliding with the actor
	 *	@return If they have collided
	 */
	bool ProximityCull(Vector3 actorPosition, Vector3 &inputObject);

	/**
	*	A normal member taking no arguments
	*	Draws the HUD within the game world
	*/
	void DrawHUD();

	int currentLevel; /*<! The current level of the game */
	int currentStage;/*<! The current stage of the game */
};

#endif
