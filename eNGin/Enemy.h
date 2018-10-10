#ifndef ENEMY_H
#define ENEMY_H

#include <vector>

#include "Actor.h"
#include "State.h"
#include "EnemyOwnedStates.h"

class Enemy : public Actor {
public:
	Enemy(Model* mod, Texture* tex, float xPos, float yPos, float zPos, std::vector<Vector3> &f);

	void Update(float deltaTime) override;

	void ChangeState(State* newState);

	State* GetWander();
	State* GetChase();
	State* GetAttack();

	std::vector<Vector3> GetFlags();

	double GetFB();
	double GetLR();
	double GetUD();

	void MoveX(double moveX);
	void MoveY(double moveY);
	void MoveZ(double moveZ);
	void RotateXZ();
	void RotateXY();

private:
	State* currentState;

	WanderState* wander;
	ChaseState* chase;
	AttackState* attack;

	std::vector<Vector3> tempFlags;

	float dT;
};

#endif
