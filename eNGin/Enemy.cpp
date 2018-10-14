#include "Enemy.h"

#include <iostream>

Enemy::Enemy(Model* mod, Texture* tex, float xPos, float yPos, float zPos, std::vector<Vector3> &f) : Actor(mod, tex),
																									  tempFlags(f)
{
	SetPos(xPos, yPos, zPos);
	SetMoveSpeed(4);
	SetRotateSpeed(5);

	wander = new WanderState(this);
	chase = new ChaseState();
	attack = new AttackState();

	currentState = wander;
}

void Enemy::Update(float deltaTime) {
	std::cout << "Enemy update" << std::endl;
	dT = deltaTime;

	if (currentState) {
		currentState->Execute(this);
	}
}

void Enemy::ChangeState(State* newState) {
	currentState->Exit(this);

	currentState = newState;

	currentState->Enter(this);
}

State* Enemy::GetWander() {
	return wander;
}

State* Enemy::GetChase() {
	return chase;
}

State* Enemy::GetAttack() {
	return attack;
}

std::vector<Vector3> Enemy::GetFlags() {
	return tempFlags;
}

//=============================================================================

double Enemy::GetFB() {
	return position.GetPointZ();
}

double Enemy::GetLR() {
	return position.GetPointX();
}

double Enemy::GetUD() {
	return position.GetPointY();
}

//========================================
// Private functions that mvoe the Actor
//========================================

void Enemy::MoveX(double moveX) {
	double newX = 0.0;

	newX = position.GetPointX() + moveX * moveSpeed * dT;

	position.SetPointX(newX);
}

void Enemy::MoveY(double moveY) {
	double newY = 0.0;

	newY = position.GetPointY() + moveY * moveSpeed * dT;

	position.SetPointY(newY);
}

void Enemy::MoveZ(double moveZ) {
	double newZ = 0.0;

	newZ = position.GetPointZ() + moveZ * moveSpeed * dT;

	position.SetPointZ(newZ);
}

void Enemy::RotateXZ() {

}

void Enemy::RotateXY() {

}
