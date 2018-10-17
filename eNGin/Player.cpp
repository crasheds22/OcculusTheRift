#include <pch.h>

#include "Player.h"

#include "Quarternion.h"

Player::Player() : lookFB{ 0.0, 0.0, -1.0 },
				   lookLR{ 1.0, 1.0, 0.0 },
  				   deltaMoveFB(0.0),
				   deltaMoveLR(0.0),
				   deltaMoveUD(0.0),
				   rotLR(0.0),
				   rotUD(0.0),
				   deltaRotLR(0.0),
				   deltaRotUD(0.0)
{
	
}

Player* Player::GetInstance() 
{
	static Player instance;
	
	return &instance;
}

void Player::Initialise()
{
	cameraViewDelta.SetQuartW(0);
	cameraViewDelta.SetQuartX(position.GetPointX());
	cameraViewDelta.SetQuartY(position.GetPointY() + 1.8);
	cameraViewDelta.SetQuartZ(position.GetPointZ());

	cameraUp.SetPointX(0);
	cameraUp.SetPointY(1);
	cameraUp.SetPointZ(0);
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
	for (int ii = 0; ii < entityMap[2].size(); ii++)
	{
		if (collisionBox.AABBtoAABB(entityMap[2][ii]->GetCollider()))
		{
			collisionBox.CollideWith(this, *entityMap[2][ii]);

		}
	}
	//Check for projectile collisions
}

void Player::DirectionB(const GLdouble tempMove) {
	deltaMoveB = tempMove;
}

void Player::DirectionR(const GLdouble tempMove) {
	deltaMoveR = tempMove;
}

void Player::DirectionF(const GLdouble tempMove) {
	deltaMoveF = tempMove;
}

void Player::DirectionL(const GLdouble tempMove) {
	deltaMoveL = tempMove;
}

void Player::DirectionUD(const GLdouble tempMove) {
	deltaMoveUD = tempMove;
}

void Player::DirectionLookLR(const GLdouble tempRot) {
	deltaRotLR = tempRot * rotateSpeed;
}

void Player::DirectionLookUD(const GLdouble tempRot) {
	deltaRotUD = tempRot * rotateSpeed;
}

GLdouble Player::GetFB() {
	return position.GetPointZ();
}

GLdouble Player::GetLR() {
	return position.GetPointX();
}

GLdouble Player::GetUD() {
	return position.GetPointY();
}

void Player::Move(float deltaTime) {
	deltaMoveFB = deltaMoveF - deltaMoveB;
	deltaMoveLR = deltaMoveR - deltaMoveL;

	if (deltaMoveFB != 0)
		MoveFB(deltaTime);

	if (deltaMoveLR != 0)
		MoveLR(deltaTime);

	//if (deltaMoveUD != 0)
		//MoveUD(deltaTime);

	//if (deltaRotLR / rotateSpeed != 0)
		//LookLR(deltaTime);

	//if (deltaRotUD / rotateSpeed != 0)
		//LookUD(deltaTime);
}

void Player::MoveFB(float deltaTime) {

	Quarternion view = cameraViewDelta.Normalize();

	GLdouble moveX = deltaMoveFB * view.GetQuartX() * moveSpeed * deltaTime;
	GLdouble moveZ = deltaMoveFB * view.GetQuartZ() * moveSpeed * deltaTime;

	position.SetPointX(moveX + position.GetPointX());
	position.SetPointZ(moveZ + position.GetPointZ());
}

void Player::MoveLR(float deltaTime) {

	Vector3 view(cameraViewDelta.GetQuartX(), cameraViewDelta.GetQuartY(), cameraViewDelta.GetQuartZ());

	view = view.CrossProduct(GetCameraUp());
	view = view.UnitVector();

	GLdouble moveX = deltaMoveLR * view.GetPointX() * moveSpeed * deltaTime;
	GLdouble moveZ = deltaMoveLR * view.GetPointZ() * moveSpeed * deltaTime;

	position.SetPointX(moveX + position.GetPointX());
	position.SetPointZ(moveZ + position.GetPointZ());
}

void Player::MoveUD(float deltaTime) {

}


void Player::LookLR(float deltaTime) {
	rotLR += deltaRotLR * deltaTime;

	float PI = 3.141592654;

	lookFB.x = sin(rotLR);
	lookFB.z = -cos(rotLR);

	lookLR.x = sin(rotLR  + (float)PI / 2.0);
	lookLR.z = -cos(rotLR  + (float)PI / 2.0);
}

void Player::LookUD(float deltaTime) {
	rotUD += deltaRotUD * deltaTime;

	float PI = 3.141592654;
	lookFB.y = sin(rotUD);

	lookLR.y = sin(rotUD + (float)PI / 2.0);
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
Quarternion Player::RotateCamera(GLdouble mouseAngle, Vector3 qAxis, Quarternion pAxis, float deltaTime)
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


Point Player::GetLookFB()
{
	return lookFB;
}


