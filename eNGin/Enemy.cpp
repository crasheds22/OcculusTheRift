#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(Game* own, Model* mod, Texture* tex, float xPos, float yPos, float zPos) : Actor(mod, tex),
																												 owner(own),
																												 shootTime(2),
																												 shootTimer(shootTime)
{
	SetPos(xPos, yPos, zPos);
	SetMoveSpeed(4);
	SetRotateSpeed(5);

	wander = new WanderState();
	chase = new ChaseState();
	attack = new AttackState();

	currentState = wander;

	SetMaxHealth(2);
	SetCurrentHealth(2);
}

Enemy::~Enemy() {
	delete wander;
	wander = NULL;

	delete chase;
	chase = NULL;

	delete attack;
	attack = NULL;

	delete currentState;
	currentState = NULL;

	delete owner;
	owner = NULL;
}

void Enemy::Update(float deltaTime) {
	dT = deltaTime;

	if (currentState) {
		currentState->Execute(this);
	}

	shootTimer -= dT;
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

void Enemy::Shoot() {
	if (shootTimer <= 0) {
		owner->AddProjectile(this, this->GetPos(), owner->GetPlayer()->GetPos() - this->GetPos(), 18);
		shootTimer = shootTime;
	}
}

float Enemy::GetdT() {
	return dT;
}

//=============================================================================

//========================================
// Functions that move the Actor
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
