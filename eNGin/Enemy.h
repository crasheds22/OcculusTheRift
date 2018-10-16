#ifndef ENEMY_H
#define ENEMY_H
class Game;

#include <vector>

#include "Actor.h"
#include "State.h"
#include "EnemyOwnedStates.h"
#include "Projectile.h"

class Enemy : public Actor {
public:
	Enemy(Game* own, Model* mod, Texture* tex, float xPos, float yPos, float zPos, std::vector<Vector3> &f);

	void Update(float deltaTime) override;

	void ChangeState(State* newState);

	State* GetWander();
	State* GetChase();
	State* GetAttack();

	void Shoot();

	std::vector<Vector3> GetFlags();

	double GetFB();
	double GetLR();
	double GetUD();

	void MoveX(double moveX);
	void MoveY(double moveY);
	void MoveZ(double moveZ);

private:
	State* currentState;

	WanderState* wander;
	ChaseState* chase;
	AttackState* attack;

	Game* owner;

	std::vector<Vector3> tempFlags;

	float dT;
};

#endif
