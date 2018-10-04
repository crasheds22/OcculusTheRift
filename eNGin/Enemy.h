#ifndef ENEMY_H
#define ENEMY_H

#include "Actor.h"
#include "State.h"
#include "EnemyOwnedStates.h"

class Enemy : public Actor {
public:
	Enemy(Model* mod, Texture* tex);

	void Update(float deltaTime);

	void ChangeState(State* newState);

	void Wander();
	void Chase(Vector3 targetPos);
	void Attack();
	void Search(Vector3 targetPos);

	void FindTarget(Actor &target);

	//Movement functions
	void DirectionFB(const double tempMove);
	void DirectionUD(const double tempMove);
	void DirectionLR(const double tempMove);
	void DirectionLookUD(const double tempRot);
	void DirectionLookLR(const double tempRot);

	double GetFB();
	double GetLR();
	double GetUD();

	void Move();
private:
	State* currentState;

	Vector3 target;

	double decelVal = 2;

	Vector3 lookFB,
		    lookLR;

	double deltaMoveFB,
		   deltaMoveLR,
		   deltaMoveUD;

	double rotLR,
		   rotUD,
		   deltaRotLR,
		   deltaRotUD;

	bool firstWanderEntry = true;

	void MoveFB();
	void MoveLR();
	void MoveUD();
	void LookUD();
	void LookLR();
};

#endif
