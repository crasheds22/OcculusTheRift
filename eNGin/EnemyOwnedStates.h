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
	static WanderState* Instance();

	virtual void Enter(Enemy* entity);

	virtual void Execute(Enemy* entity);

	virtual void Exit(Enemy* entity);

	void SetFlags(std::vector<Vector3> tempFlags);

private:
	WanderState() {};

	WanderState(const WanderState&) {};
	WanderState& operator= (const WanderState&) {};

	std::vector<Vector3> flags;
	std::vector<Vector3>::iterator fIter;
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

#endif
