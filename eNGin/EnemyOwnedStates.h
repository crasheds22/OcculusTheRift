#ifndef ENEMYOWNEDSTATES_H
#define ENEMYOWNEDSTATES_H

#include <vector>
#include "Vector3.h"

#include "State.h"

/**
 *	@class WanderState
 */
class WanderState : public State {
public:
	WanderState(Enemy* entity);

	virtual void Enter(Enemy* entity);

	virtual void Execute(Enemy* entity);

	virtual void Exit(Enemy* entity);

private:
	std::vector<Vector3> flags;
	std::vector<Vector3>::iterator fIter;
};

/**
 *	@class ChaseState
 */
class ChaseState : public State {
public:
	virtual void Enter(Enemy* entity);

	virtual void Execute(Enemy* entity);

	virtual void Exit(Enemy* entity);

private:

};

class AttackState : public State {
public:
	virtual void Enter(Enemy* entity);

	virtual void Execute(Enemy* entity);

	virtual void Exit(Enemy* entity);

private:

};

#endif
