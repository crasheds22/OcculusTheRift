#ifndef ENEMY_H
#define ENEMY_H
class Game;

#include <gl/glut.h>

#include "Actor.h"
#include "State.h"
#include "EnemyOwnedStates.h"

/**
 *	@class Enemy
 *	@brief Defines how an Enemy AI in a scene exists
 *
 *	@author Aaron Thomson
 *	@version 1.0
 *	@date 04-10-2018
 *
 *	@author Aaron Thomson
 *	@version 2.0: Moved movement functions to EnemyOwnedStates
 *	@date 09-10-2018
 *
 *	@author Aaron Thomson
 *	@version 2.1: Enemies now shoot at player
 *	@date 15-10-2018
 *
 *	@author Aaron Thomson
 *	@version 2.2: Enemy rotate to (nearly) face the player
 *	@date 22-10-2018
 */
class Enemy : public Actor {
public:
	/**
	 *	A constructor with parameters
	 *	Initialises values with those passed in
	 *	@param own The game that owns the enemy
	 *	@param mod The model to use for the enemy
	 *	@param tex The texture to use for the enemy
	 *	@param xPos The x position to place the enemy
	 *	@param yPos The y position to place the enemy at
	 *	@param zPos The z position to place the enemy at
	 */
	Enemy(Game* own, Model* mod, Texture* tex, float xPos, float yPos, float zPos);

	/**
	 *	Default destructor
	 *	Cleans up and deletes all pointers this class holds when it goes out of scope
	 */
	~Enemy();

	/**
	 *	A function taking one value
	 *	Updates the enemy state in the game
	 *	@param deltaTime The time between successive calls
	 *	@param entityMap The list of closest entities
	 */
	void Update(float deltaTime, std::map<int, std::vector<Actor*>> entityMap) override;
	
	/**
	 *	An overridden function taking on value
	 *	Would be used to update the Enemy but has been replaced
	 *	@param deltaTime The time between successive calls
	 */
	void Update(float deltaTime) override {};

	/**
	 *	A normal function taking one argument
	 *	Changes the state of the AI to the one passed in
	 *	@param newState The state to change too
	 */
	void ChangeState(State* newState);

	/**
	 *	A normal function returning a state pointer
	 *	@return The wander state
	 */
	State* GetWander();

	/**
	*	A normal function returning a state pointer
	*	@return The chase state
	*/
	State* GetChase();

	/**
	*	A normal function returning a state pointer
	*	@return The attack state
	*/
	State* GetAttack();

	/**
	 *	Defines the ability and behaviour of shooting a projectile
	 */
	void Shoot();

	/**
	 *	A function taking one argument
	 *	Moves the Enemy along the x axis
	 *	@param moveX The amount to move along the x axis
	 */
	void MoveX(double moveX);

	/**
	*	A function taking one argument
	*	Moves the Enemy along the y axis
	*	@param moveY The amount to move along the y axis
	*/
	void MoveY(double moveY);

	/**
	*	A function taking one argument
	*	Moves the Enemy along the z axis
	*	@param moveZ The amount to move along the z axis
	*/
	void MoveZ(double moveZ);

	/**
	 *	A normal function returning a float value
	 *	Returns the change in time value
	 *	@return The change in time 
	 */
	float GetdT();

	/**
	*	A function taking one argument
	*	Plays a sound from Game object
	*	@param index the sound file to play
	*/
	void PlaySound(int index);

private:
	State* currentState;	/*<! The state the AI is currently in */

	WanderState* wander;	/*<! A reference to the wander state */
	ChaseState* chase;		/*<! A reference to the chase state */
	AttackState* attack;	/*<! A reference to the attack state */

	Game* owner;	/*<! A reference to the Game objec tthat owns the Enemy */

	float dT;	/*!< the change in time value */

	float shootTime;	/*<! How frequently an Enemy is allowed to shoot */
	float shootTimer;	/*<! A countdown timer that decides when the Enemy may shoot */

	double damageTime,		/*<! The amount of time between taking damage */
		damageTimer;		/*<! Timer to determine when to take damage*/
};

#endif
