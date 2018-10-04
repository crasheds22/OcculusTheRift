#include <pch.h>

#include "Player.h"
#include "Cube.h"

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

Player* Player::GetInstance() {
	static Player instance;

	return &instance;
}

void Player::Update(float deltaTime, std::map<int, std::vector<Actor>> entityMap) {
	Move(deltaTime);
	glLoadIdentity();
	gluLookAt(position.GetPointX(), position.GetPointY() + 1.8, position.GetPointZ(),
			  position.GetPointX() + lookFB.x, position.GetPointY() + lookFB.y + 1.8, position.GetPointZ() + lookFB.z,
			  0.0, 1.0, 0.0);

	collisionBox.SetMaxPoint(position.GetPointX() + 0.5, position.GetPointY() + 0.5, position.GetPointZ() + 0.5);
	collisionBox.SetMinPoint(position.GetPointX() - 0.5, position.GetPointY() - 0.5, position.GetPointZ() - 0.5);


		//Check for Wall Collisions
		for (int ii = 0; ii < entityMap[2].size(); ii++)
		{

			std::cout << "Object List position X: " << entityMap[2][ii].GetPos().GetPointX() << std::endl;
			std::cout << "Object List position Y: " << entityMap[2][ii].GetPos().GetPointY() << std::endl;
			std::cout << "Object List position Z: " << entityMap[2][ii].GetPos().GetPointZ() << std::endl;

			if (collisionBox.AABBtoAABB(entityMap[2][ii].GetCollider()))
			{
				std::cout << "Collided" << std::endl;
				collisionBox.CollideWith(this, entityMap[2][ii]);
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

	if (deltaRotLR / rotateSpeed != 0)
		LookLR(deltaTime);

	if (deltaRotUD / rotateSpeed != 0)
		LookUD(deltaTime);
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
