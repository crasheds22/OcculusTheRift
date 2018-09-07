#ifndef PLAYER_H
#define PLAYER_H

#include <gl\glut.h>

#include "Actor.h"

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
 */
class Player : public Actor{
public:
	/**
	 *	Default constructor
	 *	Initialises all values
	 */
	Player();

	//========================================
	/**
	 *	An overridden member taking no arguments
	 *	Updates the Player's location in the world
	 */
	void Update();

	/**
	 *	An overridden member taking no arguments
	 *	Draws the Player model and applies the Player texture
	 */
	void Draw();
	//========================================

	//========================================
	// Set functions
	/**
	 *	A normal member taking one argument
	 *	Sets the move speed for the Player
	 *	@param spd The desired speed of the Player
	 */
	void SetMoveSpeed(GLdouble spd);
	
	/**
	 *	A normal member taking one argument
	 *	Sets the rotate speed of the Player
	 *	@param spd The desired rotation speed of the Player
	 */
	void SetRotateSpeed(GLdouble spd);

	/**
	 *	A normal member taking one argument
	 *	Used to determine if the player is moving forward (1), backward (-1) or not at all (0)
	 *	@param tempMove Which way the Player is moving
	 */
	void DirectionFB(const GLdouble tempMove);
	
	/**
	 *	A normal member taking one argument
	 *	Used to determine if the player is moving up (1), down (-1) or not at all (0)
	 *	@param tempMove Which way the Player is moving
	 */
	void DirectionUD(const GLdouble tempMove);
	
	/**
	 *	A normal member taking one argument
	 *	Used to determine if the player is moving right (1), left (-1) or not at all (0)
	 *	@param tempMove Which way the Player is moving
	 */
	void DirectionLR(const GLdouble tempMove);

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
	void Move();
	//========================================

private:
	//========================================
	//Speeds
	GLdouble moveSpeed,		/*<! The Player's movement speed */
			 rotateSpeed;	/*<! The Player's rotation speed */
	//========================================

	//========================================
	//Look
	Point lookFB,	/*<! The forward/backward look direction */
		  lookLR;	/*<! The left/right look direction */
	//========================================

	//========================================
	//Movement
	GLdouble deltaMoveFB,	/*<! The change in direction forward/backward */
			 deltaMoveLR,	/*<! The change in direction left/right */
			 deltaMoveUD;	/*<! The change in direction up/down */
	//========================================

	//========================================
	//Rotation
	GLdouble rotLR,		/*<! The rotation angle left/right */
			 rotUD,		/*<! The rotation angle up/down */
			 deltaRotLR,/*<! The change in rotation angle left/right */
			 deltaRotUD;/*<! The change in rotation angle up/down */
	//========================================

	//========================================
	// Move functions
	/**
	 *	A private member taking no arguments
	 *	Moves the player forward/backward
	 */
	void MoveFB();
	
	/**
	 *	A private member taking no arguments
	 *	Moves the player left/right
	 */
	void MoveLR();

	/**
	 *	A private member taking no arguments
	 *	Moves the player up/down
	 */
	void MoveUD();

	/**
	 *	A private member taking no arguments
	 *	Rotates the camera up/down
	 */
	void LookUD();

	/**
	 *	A private member taking no arguments
	 *	Rotates the camera left/right
	 */
	void LookLR();
	//========================================
};

#endif
