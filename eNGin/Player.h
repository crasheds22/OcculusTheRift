#ifndef PLAYER_H
#define PLAYER_H

#include "Actor.h"
#include "Quarternion.h"
#include "SoundPlayer.h"

/**
 *	@class Player
 *	@brief Defines the player character a user can play as
 *
 *	@author Aaron Thomson
 *	@version 1.0
 *	@date 14-08-2018
 *
 *	@author Aaron Thomson
 *	@version 1.1 Modified functions to integrate with Vector3
 *	@date 05-09-2018
 *
 *	@author Aaron Thomson
 *	@version 2.0 Change class to singleton design
 *	@date 10-09-2018
 *
 *	@author Rebecca Lim
 *	@version 2.1 Added collision detection
 *	@date 21-09-2018
 *
 *	@author Liam Kinsella
 *	@version 3.0 Changed player movement
 *	@date 04-10-2018
 *
 *	@author Rebecca Lim
 *	@version 3.1 Added Quaternion functionality
 *	@date 09-10-2018
 *
 *	@author Aaron Thomson
 *	@version 3.2 Changed update input map to accept Actor*
 *	@date 10-10-2018
 *
 *	@author Aaron Thomson
 *	@version 3.3 Player now shoots
 *	@date 23-10-2018
 */
class Player : public Actor {
public:
	/**
	 *	Returns the static instance of the Player class
	 *	Singleton design, only one player exists, this function returns the address of it
	 */
	static Player* GetInstance();

	/**
	 *	An overridden function taking one argument
	 *	The player is a special case class that has its own update function
	 *	@param deltaTime The time between successive calls
	 */
	void Update(float deltaTime) override {};

	/**
	 *	A normal function taking no arguments and returning nothing
	 *	Initialises the players health and current camera view
	 */
	void Initialise();

	/**
	 *	A normal function taking two argumments
	 *	Performs all the player's update function in movement and looking
	 *	@param deltaTime The time between successive calls
	 *	@param entityMap All possible entities within proximity the player may collide with
	 */
	void Update(float deltaTime, std::map<int, std::vector<Actor*>> entityMap);

	//========================================
	// Set functions
	/**
	 *	A normal member taking one argument
	 *	Used to determine if the player is moving backward (1) or not backward (0)
	 *	@param tempMove Which way the Player is moving
	 */
	void DirectionB(const double tempMove);

	/**
	*	A normal member taking one argument
	*	Used to determine if the player is moving forward (1) or not forward (0)
	*	@param tempMove Which way the Player is moving
	*/
	void DirectionF(const double tempMove);
	
	/**
	*	A normal member taking one argument
	*	Used to determine if the player is moving left (1) or not left (0)
	*	@param tempMove Which way the Player is moving
	*/
	void DirectionL(const double tempMove);

	/**
	*	A normal member taking one argument
	*	Used to determine if the player is moving right (1) or not right (0)
	*	@param tempMove Which way the Player is moving
	*/
	void DirectionR(const double tempMove);
	//========================================

	//========================================
	// Get functions
	/**
	 *	A normal member returning a double value
	 *	Returns the Player's z point location
	 *	@return The Player's z point
	 */
	double GetFB();

	/**
	 *	A normal member returning a double value
	 *	Returns the Player's x point location
	 *	@return The Player's x point
	 */
	double GetLR();

	/**
	 *	A normal member returning a double value
	 *	Returns the Player's y point location
	 *	@return The Player's y point
	 */
	double GetUD();
	//========================================

	//========================================
	// Movement
	/**
	 *	A normal member taking no arguments
	 *	Used to check if the player has moved, and then update the location
	 */
	void Move(float deltaTime);
	//========================================

	/**
	 *	Sets the camera to the new quarternion position 
	 *	@param theInputVector target vector
	 */
	void SetCameraViewDelta(Quarternion inputVector);

	/**
	 *	Sets the up position of the camera
	 *	@param theInputVector target vector
	 */
	void SetCameraUp(Vector3 inputVector);

	/**
	 *	Gets the new current view of the camera
	 *	@return The new current view of the camera
	 */
	Quarternion GetCameraViewDelta();

	/**
	 *	Gets the new current view of the camera as a vector
	 *	@return The new current camera view as a vector
	 */
	Vector3 GetCameraViewDeltaVector();

	/**
	*	Returns the up direction of the camera
	*	@return The up vector of the camera
	*/
	Vector3 GetCameraUp();

	/**
	*	Applies the quarternion rotation to the camera position
	*	
	*	@param mouseAngle The amount to rotate by
	*	@param qAxis The axis to rotate about
	*	@param pAxis The current camera view
	*	@param deltaTime The change in time since the last call
	*	@return The result of rotating the camera view
	*/
	Quarternion RotateCamera(double mouseAngle, Vector3 qAxis, Quarternion pAxis, float deltaTime);

	/**
	 *	Returns the amount of time left on the timer before another shot may be made
	 *	@return The amount of time remaining
	 */
	double GetShotTimer();

	/**
	 *	Returns the amount of time permitted between shots
	 *	@double The max time between shots
	 */
	double GetShotTime();

	/**
	 *	Sets the amount of time on the timer
	 *	@param t The amount of time to set
	 */
	void SetShotTimer(double t);

	/**
	 *	Sets the max amount of time between shots
	 *	@param t The amount of time to set to
	 */
	void SetShotTime(double t);

private:
	//========================================
	//Singleton design
	/**
	 *	Default constructor
	 *	Initialises all values
	 */
	Player();

	/**
	 *	Privatised copy constructor
	 *	Ensures only one copy of player exists
	 */
	Player(Player const&) {};
	
	/**
	 *	Privatised assignment operator
	 *	Ensures only one player exists
	 */
	void operator=(Player const&) {};

	//========================================

	//========================================
	//Movement
	double deltaMoveFB,		/*<! The total change in direction forward/backward */
		   deltaMoveLR;		/*<! The total change in direction left/right */

	double	deltaMoveF,		/*<! The change in direction forward */
			deltaMoveB,		/*<! The change in direction backward */
			deltaMoveL,		/*<! The change in direction left */
			deltaMoveR;		/*<! The change in direction right */
	//========================================

	Quarternion cameraViewDelta; /*<! The quarternion camera */
	Vector3 cameraUp;			 /*<! The up position of the camera */

	SoundPlayer soundPlay; /*<! SFX control for player character*/

	double damageTime,		/*<! The amount of time between taking damage */
		   damageTimer;		/*<! Timer to determine when to take damage*/
	double shotTime,		/*<! The amount of time between shots */
		   shotTimer;		/*<! Timer to determine when to shoot */

	//========================================
	// Move functions
	/**
	 *	A private member taking no arguments
	 *	Moves the player forward/backward
	 */
	void MoveFB(float deltaTime);
	
	/**
	 *	A private member taking no arguments
	 *	Moves the player left/right
	 */
	void MoveLR(float deltaTime);
	//========================================
};

#endif
