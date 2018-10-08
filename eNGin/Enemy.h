#ifndef ENEMY_H
#define ENEMY_H

#include <vector>

#include "Actor.h"
#include "State.h"
#include "EnemyOwnedStates.h"

class Enemy : public Actor {
public:
	Enemy(Model* mod, Texture* tex, std::vector<Vector3> f);

	void Update(float deltaTime);

	void ChangeState(State* newState);

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

	double decelVal = 2;

	float dT;

	//===============================================================

	Vector3 lookFB,
		    lookLR;

	double deltaMoveFB,
		   deltaMoveLR,
		   deltaMoveUD;

	double rotLR,
		   rotUD,
		   deltaRotLR,
		   deltaRotUD;

};

#endif
