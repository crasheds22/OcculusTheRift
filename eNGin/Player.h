#ifndef PLAYER_H
#define PLAYER_H

#include <gl\glut.h>

#include "Actor.h"
#include "Quarternion.h"

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
 */


class Player : public Actor {
public:
	static Player* GetInstance();

	void Update(float deltaTime) override {};

	//========================================
	/**
	 *	An overridden member taking no arguments
	 *	Updates the Player's location in the world
	 */

	void Initialise();
	//========================================

	//========================================
	/**
	 *	An overridden member taking no arguments
	 *	Updates the Player's location in the world
	 */
	void Update(float deltaTime, std::map<int, std::vector<Actor*>> entityMap);
	//========================================

	//========================================
	// Set functions

	/**
	 *	A normal member taking one argument
	 *	Used to determine if the player is moving backward (1) or not backward (0)
	 *	@param tempMove Which way the Player is moving
	 */
	void DirectionB(const GLdouble tempMove);

	/**
	*	A normal member taking one argument
	*	Used to determine if the player is moving forward (1) or not forward (0)
	*	@param tempMove Which way the Player is moving
	*/
	void DirectionF(const GLdouble tempMove);
	
	/**
	 *	A normal member taking one argument
	 *	Used to determine if the player is moving up (1), down (-1) or not at all (0)
	 *	@param tempMove Which way the Player is moving
	 */
	void DirectionUD(const GLdouble tempMove);
	
	/**
	*	A normal member taking one argument
	*	Used to determine if the player is moving left (1) or not left (0)
	*	@param tempMove Which way the Player is moving
	*/
	void DirectionL(const GLdouble tempMove);

	/**
	*	A normal member taking one argument
	*	Used to determine if the player is moving right (1) or not right (0)
	*	@param tempMove Which way the Player is moving
	*/
	void DirectionR(const GLdouble tempMove);

	/**
	 *	A normal member taking one argument
	 *	Used to determine if the player is rotating up (1), down (-1) or not at all (0)
	 *	@param tempMove Which way the Player is rotating the camera
	 */
	void DirectionLookUD(const GLdouble tempRot);

	/**
	 *	A normal member taking one argument
	 *	Used to determine if the player is rotating right (1), left (-1) or not at all (0)
	 *	@param tempMove Which way the Player is rotating the camera
	 */
	void DirectionLookLR(const GLdouble tempRot);
	//========================================

	//========================================
	// Get functions
	/**
	 *	A normal member returning a double value
	 *	Returns the Player's z point location
	 *	@return The Player's z point
	 */
	GLdouble GetFB();

	/**
	 *	A normal member returning a double value
	 *	Returns the Player's x point location
	 *	@return The Player's x point
	 */
	GLdouble GetLR();

	/**
	 *	A normal member returning a double value
	 *	Returns the Player's y point location
	 *	@return The Player's y point
	 */
	GLdouble GetUD();
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
	*	@brief sets the camera to th new quarternion position 
	*	@param theInputVector target vector
	*	@return void
	*	@pre 
	*	@post
	*/
	void SetCameraViewDelta(Quarternion inputVector);

	/**
	*	@brief sets the up position of the camera
	*	@param theInputVector target vector
	*	@return void
	*	@pre
	*	@post
	*/
	void SetCameraUp(Vector3 inputVector);

	/**
	*	@brief gets the new current view of the camera
	*	@param 
	*	@return quarternion of the new direction
	*	@pre
	*	@post
	*/
	Quarternion GetCameraViewDelta();

	/**
	*	@brief gets the new current view of the camera as a vector
	*	@param
	*	@return vector of the new direction
	*	@pre
	*	@post
	*/
	Vector3 GetCameraViewDeltaVector();

	/**
	*	@brief gets the new current view of the camera
	*	@param
	*	@return quarternion of the new direction
	*	@pre
	*	@post
	*/
	Vector3 GetCameraUp();

	/**
	*	@brief applies the quarternion rotation to the camera position 
	*	@param
	*	@return quarternion of the new direction
	*	@pre
	*	@post
	*/
	Quarternion RotateCamera(GLdouble mouseAngle, Vector3 qAxis, Quarternion pAxis,float deltaTime);

	double GetShotTimer();
	double GetShotTime();

	void SetShotTimer(double t);
	void SetShotTime(double t);

private:
	//========================================
	//Singleton design
	//static Player* instance;

	/**
	 *	Default constructor
	 *	Initialises all values
	 */
	Player();

	Player(Player const&) {};
	void operator=(Player const&) {};
	//========================================

	//========================================
	//Look
	Point lookFB,	/*<! The forward/backward look direction */
		  lookLR;	/*<! The left/right look direction */
	//========================================

	//========================================
	//Movement
	GLdouble deltaMoveFB,	/*<! The total change in direction forward/backward */
			 deltaMoveLR,	/*<! The total change in direction left/right */
			 deltaMoveUD;	/*<! The total change in direction up/down */

	GLdouble	deltaMoveF, /*<! The change in direction forward */
				deltaMoveB, /*<! The change in direction backward */
				deltaMoveL, /*<! The change in direction left */
				deltaMoveR; /*<! The change in direction right */
	//========================================

	//========================================
	//Rotation
	GLdouble rotLR,		/*<! The rotation angle left/right */
			 rotUD,		/*<! The rotation angle up/down */
			 deltaRotLR,/*<! The change in rotation angle left/right */
			 deltaRotUD;/*<! The change in rotation angle up/down */
	//========================================

	Quarternion cameraViewDelta; /*<! The quarternion camera */
	Vector3 cameraUp;  /*<! The up position of the camera */

	double damageTime = 1, damageTimer;
	double shotTime = 2, shotTimer;

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

	/**
	 *	A private member taking no arguments
	 *	Moves the player up/down
	 */
	void MoveUD(float deltaTime);

	/**
	 *	A private member taking no arguments
	 *	Rotates the camera up/down
	 */
	void LookUD(float deltaTime);

	/**
	 *	A private member taking no arguments
	 *	Rotates the camera left/right
	 */
	void LookLR(float deltaTime);
	//========================================
};

#endif
