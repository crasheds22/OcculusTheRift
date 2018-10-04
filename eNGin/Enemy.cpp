#include "Enemy.h"

Enemy::Enemy(Model* mod, Texture* tex) : Actor(mod, tex),
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

}

void Enemy::Update(float deltaTime) {
	if (currentState) {
		currentState->Execute(this);
	}
}

void Enemy::ChangeState(State* newState) {
	currentState->Exit(this);

	currentState = newState;

	currentState->Enter(this);
}

void Enemy::Wander() {
	//Randomly explore the scene
}

void Enemy::Chase(Vector3 targetPos) {
	//Arrive behaviour: Seeks to location, upon arrival, applies brakes

	//Vector to target: targetPos - enemyPos
	//Vector3 toTarget = targetPos - position;
	//Get distance: target.Magnitude
	//double distance = toTarget.VectorMagnitude();

	//if distance > 0
	//if (distance > 0) {

		//fine tweak decel
		//double tweak = 0.3;

		//calc speed required to reach target: speed = distance / decel * tweak
		//double speed = distance / decelVal * tweak;

		//Vector3 desired = target * speed / dist
		//Vector3 desired = toTarget * speed / distance;

		//return desired - enemySpeed

	//}//ENDIF

	//return Vector3(0.0, 0.0, 0.0)
	
}

void Enemy::Attack() {
	//When in range, attacks
}

void Enemy::Search(Vector3 targetPos) {
	//Arrive to player last known location, rotate
}

void Enemy::FindTarget(Actor &target) {

}

//=============================================================================

void Enemy::DirectionFB(const double tempMove) {
	deltaMoveFB = tempMove;
}

void Enemy::DirectionUD(const double tempMove) {
	deltaMoveUD = tempMove;
}

void Enemy::DirectionLR(const double tempMove) {
	deltaMoveLR = tempMove;
}

void Enemy::DirectionLookUD(const double tempRot) {
	deltaRotUD = tempRot * rotateSpeed;
}

void Enemy::DirectionLookLR(const double tempRot) {
	deltaRotLR = tempRot * rotateSpeed;
}

double Enemy::GetFB() {
	return position.GetPointZ();
}

double Enemy::GetLR() {
	return position.GetPointX();
}

double Enemy::GetUD() {
	return position.GetPointY();
}

void Enemy::Move() {
	if (deltaMoveFB != 0)
		MoveFB();

	if (deltaMoveLR != 0)
		MoveLR();

	if (deltaMoveUD != 0)
		MoveUD();

	if (deltaRotLR / rotateSpeed != 0)
		LookLR();

	if (deltaRotUD / rotateSpeed != 0)
		LookUD();
}

//========================================
// Private functions that mvoe the Actor
//========================================

void Enemy::MoveFB() {
	GLdouble moveX = deltaMoveFB * lookFB.GetPointX() * moveSpeed;
	GLdouble moveZ = deltaMoveFB * lookFB.GetPointZ() * moveSpeed;

	position.SetPointX(moveX + position.GetPointX());
	position.SetPointZ(moveZ + position.GetPointZ());
}

void Enemy::MoveLR() {
	GLdouble moveX = deltaMoveLR * lookLR.GetPointX() * moveSpeed;
	GLdouble moveZ = deltaMoveLR * lookLR.GetPointZ() * moveSpeed;

	position.SetPointX(moveX + position.GetPointX());
	position.SetPointZ(moveZ + position.GetPointZ());
}

void Enemy::MoveUD() {

}

void Enemy::LookLR() {
	rotLR += deltaRotLR;

	float PI = 3.141592654;

	lookFB.SetPointX(sin(rotLR));
	lookFB.SetPointZ(-cos(rotLR));

	lookLR.SetPointX(sin(rotLR + (float)PI / 2.0));
	lookLR.SetPointZ(-cos(rotLR + (float)PI / 2.0));
}

void Enemy::LookUD() {
	rotUD += deltaRotUD;

	float PI = 3.141592654;
	lookFB.SetPointY(sin(rotUD));

	lookLR.SetPointY(sin(rotUD + (float)PI / 2.0));
}
