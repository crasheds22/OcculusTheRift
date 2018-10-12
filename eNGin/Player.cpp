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
	// cameraViewDelta needs to be initialised to the position and cannot be 0,0,0
	cameraViewDelta.SetQuartX(40);
	cameraViewDelta.SetQuartY(0);
	cameraViewDelta.SetQuartZ(40);
	
	cameraUp.SetPointX(0);
	cameraUp.SetPointY(1);
	cameraUp.SetPointZ(0);
}

Player* Player::GetInstance() {
	static Player instance;

	return &instance;
}

void Player::Update(float deltaTime, std::vector<Actor> resultObjectList) {

	//cameraUp = Vector3(0.0, 1.0, 0.0);

	//std::cout << "Player Spawning point X" << position.GetPointX() << std::endl;
	//std::cout << "Player Spawning point Y" << position.GetPointY() << std::endl;
	//std::cout << "Player Spawning point Z" << position.GetPointZ() << std::endl;

	Move(deltaTime);
	glLoadIdentity();
	gluLookAt(	position.GetPointX(), position.GetPointY() + 1.8, position.GetPointZ(),
				cameraViewDelta.GetQuartX(), 
				cameraViewDelta.GetQuartY(),
				cameraViewDelta.GetQuartZ(),
				0.0, 1.0, 0.0);

	collisionBox.SetMaxPoint(position.GetPointX() + 0.5, position.GetPointY() + 0.5, position.GetPointZ() + 0.5);
	collisionBox.SetMinPoint(position.GetPointX() - 0.5, position.GetPointY() - 0.5, position.GetPointZ() - 0.5);


	for (int ii = 0; ii < resultObjectList.size(); ii++)
	{
		
		std::cout << "Object List position X: " << resultObjectList[ii].GetPos().GetPointX() << std::endl;
		std::cout << "Object List position Y: " << resultObjectList[ii].GetPos().GetPointY() << std::endl;
		std::cout << "Object List position Z: " << resultObjectList[ii].GetPos().GetPointZ() << std::endl;

		if (collisionBox.AABBtoAABB(resultObjectList[ii].GetCollider()))
		{
			std::cout << "Collided" << std::endl;
			collisionBox.CollideWith(this, resultObjectList[ii]);
		}
		else
		{
			std::cout << "No Collision" << std::endl;
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

GLdouble Player::GetFB() {
	return position.GetPointZ();
}

void Player::DirectionLookUD(const GLdouble tempRot) {
	deltaRotUD = tempRot * rotateSpeed;
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

void Player::SetCameraViewLR(Quarternion inputVector)
{
	cameraViewLR = inputVector;
}

void Player::SetCameraViewUD(Quarternion inputVector)
{
	cameraViewUD = inputVector;
}

void Player::SetCameraViewDelta(Quarternion inputVector)
{
	cameraViewDelta = inputVector;
}



void Player::SetCameraUp(Vector3 inputVector)
{
	cameraUp = inputVector;
}

Quarternion Player::GetCameraViewLR()
{
	return cameraViewLR;
}

Quarternion Player::GetCameraViewUD()
{
	return cameraViewUD;
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
Quarternion Player::RotateCamera(GLdouble mouseAngle, Vector3 qAxis, Quarternion pAxis,float deltaTime)
{
	Quarternion tempQuart, qQuart, pQuart, qpQuart, quartResult;

	qQuart = tempQuart.QRotation(mouseAngle, qAxis);
	
	pQuart.SetQuartW(0);
	pQuart.SetQuartX(pAxis.GetQuartX());
	pQuart.SetQuartY(pAxis.GetQuartY());
	pQuart.SetQuartZ(pAxis.GetQuartZ());

	std::cout << "qQuarternion W:" << qQuart.GetQuartW() << std::endl;
	std::cout << "qQuarternion X:" << qQuart.GetQuartX() << std::endl;
	std::cout << "qQuarternion Y:" << qQuart.GetQuartY() << std::endl;
	std::cout << "qQuarternion Z:" << qQuart.GetQuartZ() << std::endl;
	
	qpQuart = qQuart.CrossProduct(pQuart);

	quartResult = qpQuart.CrossProduct(qQuart.Inverse());
	
	quartResult = quartResult.ScalarProduct(1);

	cameraViewDelta = quartResult; 

	std::cout << "Delta W:" << cameraViewDelta.GetQuartW() << std::endl;
	std::cout << "Delta X:" << cameraViewDelta.GetQuartX() << std::endl;
	std::cout << "Delta Y:" << cameraViewDelta.GetQuartY() << std::endl;
	std::cout << "Delta Z:" << cameraViewDelta.GetQuartZ() << std::endl;

	return quartResult;
}

Vector3 Player::RotateCameraDelta(Vector3 axisOne, Vector3 axisTwo)
{
	Vector3 theResult;

	theResult = axisOne.CrossProduct(axisTwo);

	return theResult;
}




