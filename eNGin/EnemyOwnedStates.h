#ifndef ENEMYOWNEDSTATES_H
#define ENEMYOWNEDSTATES_H

#include "State.h"

/**
 *	@class WanderState
 */
class WanderState : public State {
public:
	static WanderState* Instance();

	virtual void Enter(Enemy* entity);

	virtual void Execute(Enemy* entity);

	virtual void Exit(Enemy* entity);

private:
	WanderState() {};

	WanderState(const WanderState&) {};
	WanderState& operator= (const WanderState&) {};
};

/**
 *	@class ChaseState
 */
class ChaseState : public State {
public:
	static ChaseState* Instance();

	virtual void Enter(Enemy* entity);

	virtual void Execute(Enemy* entity);

	virtual void Exit(Enemy* entity);

private:
	ChaseState() {};

	ChaseState(const ChaseState&) {};
	ChaseState& operator= (const ChaseState&) {};
};

class AttackState : public State {
public:
	static AttackState* Instance();

	virtual void Enter(Enemy* entity);

	virtual void Execute(Enemy* entity);

	virtual void Exit(Enemy* entity);

private:
	AttackState() {};

	AttackState(const AttackState&) {};
	AttackState& operator= (const AttackState&) {};
};

class SearchState : public State {
public:
	static SearchState* Instance();

	virtual void Enter(Enemy* entity);

	virtual void Execute(Enemy* entity);

	virtual void Exit(Enemy* entity);

private:
	SearchState() {};

	SearchState(const SearchState&) {};
	SearchState& operator= (const SearchState&) {};
};

#endif
