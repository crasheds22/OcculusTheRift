#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(Game* own, Model* mod, Texture* tex, float xPos, float yPos, float zPos, std::vector<Vector3> &f) : Actor(mod, tex),
																												 tempFlags(f),
																												 owner(own)
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

State* Enemy::GetChase(Vector3 last) {
	chase->SetLastTarget(last);

	return chase;
}

State* Enemy::GetAttack() {
	return attack;
}

std::vector<Vector3> Enemy::GetFlags() {
	return tempFlags;
}

void Enemy::Shoot() {
	owner->AddProjectile(this, this->GetPos(), (owner->GetPlayer()->GetPos() - this->GetPos()));
}

float Enemy::GetdT() {
	return dT;
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

	newX = position.GetPointX() + (moveX * moveSpeed * dT);

	position.SetPointX(newX);
}

void Enemy::MoveY(double moveY) {
	double newY = 0.0;

	newY = position.GetPointY() + (moveY * moveSpeed * dT);

	position.SetPointY(newY);
}

void Enemy::MoveZ(double moveZ) {
	double newZ = 0.0;

	newZ = position.GetPointZ() + (moveZ * moveSpeed * dT);

	position.SetPointZ(newZ);
}
