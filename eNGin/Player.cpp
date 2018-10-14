#include <pch.h>

#include "Player.h"

#include "Cube.h"
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
	cameraViewUD.SetPointX(0);
	cameraViewUD.SetPointY(1);
	cameraViewUD.SetPointZ(0);
	cameraViewLR.SetPointX(1);
	cameraViewLR.SetPointY(0);
	cameraViewLR.SetPointZ(0);
	cameraUp.SetPointX(0);
	cameraUp.SetPointY(1);
	cameraUp.SetPointZ(0);
}

Player* Player::GetInstance() {
	static Player instance;

	return &instance;
}

void Player::Update(float deltaTime, std::map<int, std::vector<Actor*>> entityMap) {
	std::cout << "Player update" << std::endl;

	Move(deltaTime);

	glLoadIdentity();
	gluLookAt(position.GetPointX(), position.GetPointY() + 1.8, position.GetPointZ(),
			  position.GetPointX() * cameraViewLR.GetPointX() * cameraViewUD.GetPointX(), 
			  position.GetPointY() * cameraViewLR.GetPointY() * cameraViewUD.GetPointY(), 
		      position.GetPointZ() * cameraViewLR.GetPointZ() * cameraViewUD.GetPointZ(),
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

	if (deltaMoveUD != 0)
		MoveUD(deltaTime);

	//if (deltaRotLR / rotateSpeed != 0)
		//LookLR(deltaTime);

	//if (deltaRotUD / rotateSpeed != 0)
		//LookUD(deltaTime);
}

void Player::MoveFB(float deltaTime) {
	GLdouble moveX = deltaMoveFB * lookFB.x * moveSpeed * deltaTime;
	GLdouble moveZ = deltaMoveFB * lookFB.z * moveSpeed * deltaTime;

	position.SetPointX(moveX + position.GetPointX());
	position.SetPointZ(moveZ + position.GetPointZ());
}

void Player::MoveLR(float deltaTime) {
	GLdouble moveX = deltaMoveLR * lookLR.x * moveSpeed * deltaTime;
	GLdouble moveZ = deltaMoveLR * lookLR.z * moveSpeed * deltaTime;

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

void Player::SetCameraViewLR(Vector3 inputVector)
{
	cameraViewLR = inputVector;
}

void Player::SetCameraViewUD(Vector3 inputVector)
{
	cameraViewUD = inputVector;
}

void Player::SetCameraViewDelta(Vector3 inputVector)
{
	cameraViewDelta = inputVector;
}



void Player::SetCameraUp(Vector3 inputVector)
{
	cameraUp = inputVector;
}

Vector3 Player::GetCameraViewLR()
{
	return cameraViewLR;
}

Vector3 Player::GetCameraViewUD()
{
	return cameraViewUD;
}

Vector3 Player::GetCameraViewDelta()
{
	return cameraViewDelta;
}

Vector3 Player::GetCameraUp()
{
	return cameraUp;
}

// qp'q
Quarternion Player::RotateCameraLR(GLdouble mouseAngle, Vector3 pAxis, Vector3 qAxis,float deltaTime)
{
	Quarternion tempQuart, qQuart, pQuart, qpQuart, quartResult;

	qQuart = tempQuart.QRotation(mouseAngle, pAxis);
	
	pQuart.SetQuartW(0);
	pQuart.SetQuartX(qAxis.GetPointX());
	pQuart.SetQuartY(qAxis.GetPointY());
	pQuart.SetQuartZ(qAxis.GetPointZ());

	std::cout << "qQuarternion W:" << qQuart.GetQuartW() << std::endl;
	std::cout << "qQuarternion X:" << qQuart.GetQuartX() << std::endl;
	std::cout << "qQuarternion Y:" << qQuart.GetQuartY() << std::endl;
	std::cout << "qQuarternion Z:" << qQuart.GetQuartZ() << std::endl;
	
	qpQuart = qQuart.CrossProduct(pQuart);

	quartResult = qpQuart.CrossProduct(qQuart.Inverse());

	quartResult = quartResult.ScalarProduct(deltaTime * 30);
	std::cout << "Quarternion W:" << quartResult.GetQuartW() << std::endl;
	std::cout << "Quarternion X:" << quartResult.GetQuartX() << std::endl;
	std::cout << "Quarternion Y:" << quartResult.GetQuartY() << std::endl;
	std::cout << "Quarternion Z:" << quartResult.GetQuartZ() << std::endl;

	cameraViewLR.SetPointX(cameraViewLR.GetPointX() + quartResult.GetQuartX());
	cameraViewLR.SetPointY(cameraViewLR.GetPointY() + quartResult.GetQuartY());
	cameraViewLR.SetPointZ(cameraViewLR.GetPointZ() + quartResult.GetQuartZ());

	return quartResult;
}

// qp'q
Quarternion Player::RotateCameraUD(GLdouble mouseAngle, Vector3 pAxis, Vector3 qAxis, float deltaTime)
{
	Quarternion tempQuart, qQuart, pQuart, qpQuart, quartResult;

	qQuart = tempQuart.QRotation(mouseAngle, pAxis);

	pQuart.SetQuartW(0);
	pQuart.SetQuartX(qAxis.GetPointX());
	pQuart.SetQuartY(qAxis.GetPointY());
	pQuart.SetQuartZ(qAxis.GetPointZ());

	std::cout << "qQuarternion W:" << qQuart.GetQuartW() << std::endl;
	std::cout << "qQuarternion X:" << qQuart.GetQuartX() << std::endl;
	std::cout << "qQuarternion Y:" << qQuart.GetQuartY() << std::endl;
	std::cout << "qQuarternion Z:" << qQuart.GetQuartZ() << std::endl;

	qpQuart = qQuart.CrossProduct(pQuart);

	quartResult = qpQuart.CrossProduct(qQuart.Inverse());

	quartResult = quartResult.ScalarProduct(deltaTime * 30);
	std::cout << "Quarternion W:" << quartResult.GetQuartW() << std::endl;
	std::cout << "Quarternion X:" << quartResult.GetQuartX() << std::endl;
	std::cout << "Quarternion Y:" << quartResult.GetQuartY() << std::endl;
	std::cout << "Quarternion Z:" << quartResult.GetQuartZ() << std::endl;

	cameraViewUD.SetPointX(cameraViewUD.GetPointX() + quartResult.GetQuartX());
	cameraViewUD.SetPointY(cameraViewUD.GetPointY() + quartResult.GetQuartY());
	cameraViewUD.SetPointZ(cameraViewUD.GetPointZ() + quartResult.GetQuartZ());

	return quartResult;
}

Vector3 Player::RotateCameraDelta(Vector3 axisOne, Vector3 axisTwo)
{
	Vector3 theResult;

	theResult = axisOne.CrossProduct(axisTwo);

	return theResult;
}




