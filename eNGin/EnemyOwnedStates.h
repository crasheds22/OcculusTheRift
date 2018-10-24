#ifndef ENEMYOWNEDSTATES_H
#define ENEMYOWNEDSTATES_H

#include <vector>

#include "State.h"

/**
 *	@class WanderState
 *	@brief Defines the behaviour an enemy can have while wandering the scene
 *
 *	@author Aaron Thomson
 *	@version 1.0
 *	@date 04-10-2018
 */
class WanderState : public State {
public:
	/**
	 *	A normal function taking one parameter
	 *	Defines the action to take when entering the wander state
	 *	@param entity A reference to he enemy that owns this state
	 */
	void Enter(Enemy* entity);

	/**
	 *	A normal function taking one parameter
	 *	Defines the action to take while executing in the wander state
	 *	@param entity A reference to he enemy that owns this state
 	 */
	void Execute(Enemy* entity);

	/**
	 *	A normal function taking one parameter
	 *	Defines the action to take when exiting the wander state
	 *	@param entity A reference to he enemy that owns this state
	 */
	void Exit(Enemy* entity);

private:
};

/**
 *	@class ChaseState
 *	@brief Defines the behaviour an enemy can take while chasing the player
 *
 *	@author Aaron Thomson
 *	@version 1.0
 *	@date 04-10-2018
 */
class ChaseState : public State {
public:
	/**
	*	A normal function taking one parameter
	*	Defines the action to take when entering the chase state
	*	@param entity A reference to he enemy that owns this state
	*/
	void Enter(Enemy* entity);

	/**
	*	A normal function taking one parameter
	*	Defines the action to take while executing in the chase state
	*	@param entity A reference to he enemy that owns this state
	*/
	void Execute(Enemy* entity);

	/**
	*	A normal function taking one parameter
	*	Defines the action to take when exiting the chase state
	*	@param entity A reference to he enemy that owns this state
	*/
	void Exit(Enemy* entity);
};

/**
 *	@class AttackState
 *	@brief Defines the behaviour an enemy can take while attacking
 *
 *	@author Aaron Thomson
 *	@version 1.0
 *	@date 04-10-2018
 */
class AttackState : public State {
public:
	/**
	*	A normal function taking one parameter
	*	Defines the action to take when entering the attack state
	*	@param entity A reference to he enemy that owns this state
	*/
	void Enter(Enemy* entity);

	/**
	*	A normal function taking one parameter
	*	Defines the action to take while executing in the attack state
	*	@param entity A reference to he enemy that owns this state
	*/
	void Execute(Enemy* entity);

	/**
	*	A normal function taking one parameter
	*	Defines the action to take when exiting the attack state
	*	@param entity A reference to he enemy that owns this state
	*/
	void Exit(Enemy* entity);
};

#endif
