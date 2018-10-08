#include "Enemy.h"

Enemy::Enemy(Model* mod, Texture* tex, std::vector<Vector3> f) : Actor(mod, tex),
															   lookFB( 0.0, 0.0, -1.0 ),
															   lookLR( 1.0, 1.0, 0.0 ),
															   deltaMoveFB(0.0),
															   deltaMoveLR(0.0),
															   deltaMoveUD(0.0),
															   rotLR(0.0),
														 	   rotUD(0.0),
															   deltaRotLR(0.0),
															   deltaRotUD(0.0),
															   currentState(WanderState::Instance())
{
	SetMoveSpeed(4);
	SetRotateSpeed(5);
	
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
