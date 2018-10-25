#include <pch.h>

#include "Player.h"

Player::Player() : deltaMoveFB(0.0),
				   deltaMoveLR(0.0),
				   deltaMoveF(0),
				   deltaMoveB(0),
				   deltaMoveL(0),
				   deltaMoveR(0),
				   damageTime(1),
				   damageTimer(damageTime),
				   shotTime(0.3),
				   shotTimer(shotTime)
{

}

Player* Player::GetInstance() 
{
	static Player instance;
	
	return &instance;
}

void Player::Initialise()
{
	Quarternion qd(0, position.GetPointX(), position.GetPointY(), position.GetPointZ());
	SetCameraViewDelta(qd);

	Vector3 up(0, 1, 0);
	SetCameraUp(up);

	health = 5;
	maxHealth = 5;
}

void Player::Update(float deltaTime, std::map<int, std::vector<Actor*>> entityMap)
{
	Move(deltaTime);

	glLoadIdentity();
	gluLookAt(	position.GetPointX(), position.GetPointY() + 1.8, position.GetPointZ(),
				position.GetPointX() + cameraViewDelta.GetQuartX(), 
				position.GetPointY() + cameraViewDelta.GetQuartY(),
				position.GetPointZ() + cameraViewDelta.GetQuartZ(),
				0.0, 1.0, 0.0);

	collisionBox.SetMaxPoint(position.GetPointX() + 0.5, position.GetPointY() + 0.5, position.GetPointZ() + 0.5);
	collisionBox.SetMinPoint(position.GetPointX() - 0.5, position.GetPointY() - 0.5, position.GetPointZ() - 0.5);

	//Check for Wall Collisions
	for (std::size_t ii = 0; ii < entityMap[2].size(); ii++)
	{
		if (collisionBox.AABBtoAABB(entityMap[2][ii]->GetCollider()))
		{
			collisionBox.CollideWith(this, *entityMap[2][ii]);

		}
	}
	//Check for projectile collisions
	for (std::size_t ii = 0; ii < entityMap[5].size(); ii++)
	{
		if (entityMap[5][ii] != NULL) {
			if (collisionBox.AABBtoAABB(entityMap[5][ii]->GetCollider()))
			{
				if (damageTimer <= 0) {
					SetCurrentHealth(GetCurrentHealth() - 1);
					damageTimer = damageTime;
					soundPlay.PlaySound(5);
				}
			}
		}
	}

	damageTimer -= deltaTime;

	shotTimer -= deltaTime;
}

void Player::DirectionB(const double tempMove) {
	deltaMoveB = tempMove;
}

void Player::DirectionR(const double tempMove) {
	deltaMoveR = tempMove;
}

void Player::DirectionF(const double tempMove) {
	deltaMoveF = tempMove;
}

void Player::DirectionL(const double tempMove) {
	deltaMoveL = tempMove;
}

double Player::GetFB() {
	return position.GetPointZ();
}

double Player::GetLR() {
	return position.GetPointX();
}

double Player::GetUD() {
	return position.GetPointY();
}

void Player::Move(float deltaTime) {
	deltaMoveFB = deltaMoveF - deltaMoveB;
	deltaMoveLR = deltaMoveR - deltaMoveL;

	if (deltaMoveFB != 0)
		MoveFB(deltaTime);

	if (deltaMoveLR != 0)
		MoveLR(deltaTime);
}

void Player::MoveFB(float deltaTime) {

	Quarternion view = cameraViewDelta.Normalize();

	double moveX = deltaMoveFB * view.GetQuartX() * moveSpeed * deltaTime;
	double moveZ = deltaMoveFB * view.GetQuartZ() * moveSpeed * deltaTime;

	position.SetPointX(moveX + position.GetPointX());
	position.SetPointZ(moveZ + position.GetPointZ());
}

void Player::MoveLR(float deltaTime) {

	Vector3 view(cameraViewDelta.GetQuartX(), cameraViewDelta.GetQuartY(), cameraViewDelta.GetQuartZ());

	view = view.CrossProduct(GetCameraUp());
	view = view.UnitVector();

	double moveX = deltaMoveLR * view.GetPointX() * moveSpeed * deltaTime;
	double moveZ = deltaMoveLR * view.GetPointZ() * moveSpeed * deltaTime;

	position.SetPointX(moveX + position.GetPointX());
	position.SetPointZ(moveZ + position.GetPointZ());
}

void Player::SetCameraViewDelta(Quarternion inputVector)
{
	cameraViewDelta = inputVector;
}

void Player::SetCameraUp(Vector3 inputVector)
{
	cameraUp = inputVector;
}

Quarternion Player::GetCameraViewDelta()
{
	return cameraViewDelta;
}

Vector3 Player::GetCameraViewDeltaVector()
{
	return Vector3(cameraViewDelta.GetQuartX(), cameraViewDelta.GetQuartY(), cameraViewDelta.GetQuartZ());
}

Vector3 Player::GetCameraUp()
{
	return cameraUp;
}

// qpq'
Quarternion Player::RotateCamera(double mouseAngle, Vector3 qAxis, Quarternion pAxis, float deltaTime)
{
	Quarternion tempQuart, qQuart, pQuart, qpQuart, quartResult;

	qQuart = tempQuart.QRotation(mouseAngle, qAxis);
	
	pQuart.SetQuartW(0);
	pQuart.SetQuartX(pAxis.GetQuartX());
	pQuart.SetQuartY(pAxis.GetQuartY());
	pQuart.SetQuartZ(pAxis.GetQuartZ());
	
	qpQuart = qQuart.CrossProduct(pQuart);

	quartResult = qpQuart.CrossProduct(qQuart.Inverse());

	cameraViewDelta = quartResult;
	
	return quartResult;
}

double Player::GetShotTimer() {
	return shotTimer;
}

double Player::GetShotTime() {
	return shotTime;
}

void Player::SetShotTimer(double t) {
	shotTimer = t;
}

void Player::SetShotTime(double t) {
	shotTime = t;
}
