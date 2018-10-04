#ifndef STATE_H
#define STATE_H
class Enemy;

/**
 *	@class State
 *	@brief Base class for states
 *	@details The base class for all states to be used in the AI state machine controlling enemies.
 *			 Adapted from M. Buckland: Programming Game AI by Example
 *	
 *	@author Aaron Thomson
 *	@version 1.0
 *	@date 01-10-2018
 */
class State {
public:
	/**
	 *	Virtual destructor
	 */
	virtual ~State() {};

	/**
	 *	A pure virtual function to be implemented by every State derived
	 *	Defines a behaviour when entering the state
	 *	@param entity The Enemy type the behaviour will apply to
	 */
	virtual void Enter(Enemy* enitity) = 0;

	/**
	 *	A pure virtual function to be implemented by every State derived
	 *	Defines a behaviour when in the state
	 *	@param entity The Enemy type the behaviour will apply to
	 */
	virtual void Execute(Enemy* entity) = 0;

	/**
	 *	A pure virtual function to be implemented by every State derived
	 *	Defines a behaviour when exiting the state
	 *	@param entity The Enemy type the behaviour will apply to
	 */
	virtual void Exit(Enemy* entity) = 0;
};

#endif
