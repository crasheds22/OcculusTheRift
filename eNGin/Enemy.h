#ifndef ENEMY_H
#define ENEMY_H

#include <vector>

#include "Actor.h"
#include "State.h"
#include "EnemyOwnedStates.h"

/**
 *	@class Enemy
 *	@brief Defines a controller for an AI
 *
 *	@author Aaron Thomson
 *	@date 12-10-2018
 *	@version 1.0
 */
class Enemy : public Actor {
public:
	/**
	 *	A constructor with parameters
	 *	Builds an Enemy froma model, texture, position in space and a set of flags to move towards
	 */
	Enemy(Model* mod, Texture* tex, float xPos, float yPos, float zPos, std::vector<Vector3> &f);

	/**
	 *	An overridden function that takes one argument
	 *	@param deltaTime The time between successive calls
	 */
	void Update(float deltaTime) override;

	/**
	 *	A normal function taking one argument
	 *	Changes the state the AI is currently in to the state passed in
	 *	@param newState The state to change towards
	 */
	void ChangeState(State* newState);

	/**
	 *	A normal function returning a state pointer
	 *	Returns a state pointer to the Wander state
	 *	@return A state pointer to the wander state
	 */
	State* GetWander();

	/**
	 *	A normal function returning a state pointer
	 *	Returns a state pointer to the Chase state
	 *	@return A state pointer to the Chase state
	 */
	State* GetChase();

	/**
	 *	A normal function returning a state pointer
	 *	Returns a state pointer to the Attack state
	 *	@return A state pointer to the attack state
	 */
	State* GetAttack();

	/**
	 *	A normal function returning a list of flags
	 *	Returns the set of flags that the AI will move between
	 *	@return The vector of flags
	 */
	std::vector<Vector3> GetFlags();

	/**
	 *	A normal function returning a double
	 *	Returns the z value of the enemy
	 *	@return The z value of the enemy
	 */
	double GetFB();

	/**
	 *	A normal function returning a double
	 *	Returns the x value of the enemy
	 *	@return the x value
	 */
	double GetLR();

	/**
	 *	A normal function returning a double
	 *	Returns the y value of the enemy
	 *	@return The y value
	 */
	double GetUD();

	/**
	 *	A normal function taking one argument
	 *	Moves the enemy left and right along the x axis
	 *	@param moveX The amount to move along the x axis
	 */
	void MoveX(double moveX);

	/**
	 *	A normal function taking one argument
	 *	Moves the enemy up and down along the y axis
	 *	@param moveY The amount to move along the y axis
	 */
	void MoveY(double moveY);

	/**
	 *	A normal function taking one argument
	 *	Moves the enemy forward and backward along the z axis
	 *	@param moveZ The amount to move along the z axis
	 */
	void MoveZ(double moveZ);

private:
	State* currentState;	/*<! The state the Enemy is currently in */
	
	WanderState* wander;	/*<! The wander state owned by the enemy */
	ChaseState* chase;		/*<! The chase state owned by the enemy */
	AttackState* attack;	/*<! The attack state owned by the enemy */

	std::vector<Vector3> tempFlags;	/*<! A list of flags to move between in the wander state */

	float dT;	/*<! A variable to store delta time for use */
};

#endif
