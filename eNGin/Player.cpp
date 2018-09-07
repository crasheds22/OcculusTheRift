#include "Player.h"

Player::Player() : moveSpeed(0.0),
				   rotateSpeed(0.0),
				   lookFB{ 0.0, 0.0, -1.0 },
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

void Player::Update() {
	Move();

	glLoadIdentity();
	gluLookAt(position.GetPointX(), position.GetPointY() + 1.8, position.GetPointZ(),
		position.GetPointX() + lookFB.x, position.GetPointY() + lookFB.y + 1.8, position.GetPointZ() + lookFB.z,
		0.0, 1.0, 0.0);
}

void Player::Draw() {
	//model->DrawModel(position.GetPointX(), position.GetPointY(), position.GetPointZ(),
	//				 texture->GetTexture(), texture->GetWidth(), texture->GetHeight());
}

void Player::SetMoveSpeed(GLdouble spd) {
	moveSpeed = spd;
}

void Player::SetRotateSpeed(GLdouble spd) {
	rotateSpeed = spd;
}

void Player::DirectionFB(const GLdouble tempMove) {
	deltaMoveFB = tempMove;
}

void Player::DirectionUD(const GLdouble tempMove) {
	deltaMoveUD = tempMove;
}

void Player::DirectionLR(const GLdouble tempMove) {
	deltaMoveLR = tempMove;
}

void Player::DirectionLookUD(const GLdouble tempRot) {
	deltaRotUD = tempRot * rotateSpeed;
}

void Player::DirectionLookLR(const GLdouble tempRot) {
	deltaRotLR = tempRot * rotateSpeed;
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

void Player::Move() {
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

void Player::MoveFB() {
	GLdouble moveX = deltaMoveFB * lookFB.x * moveSpeed;
	GLdouble moveZ = deltaMoveFB * lookFB.z * moveSpeed;

	position.SetPointX(moveX + position.GetPointX());
	position.SetPointZ(moveZ + position.GetPointZ());
}

void Player::MoveLR() {
	GLdouble moveX = deltaMoveLR * lookLR.x * moveSpeed;
	GLdouble moveZ = deltaMoveLR * lookLR.z * moveSpeed;

	position.SetPointX(moveX + position.GetPointX());
	position.SetPointZ(moveZ + position.GetPointZ());
}

void Player::MoveUD() {

}

void Player::LookLR() {
	rotLR += deltaRotLR;



	lookFB.x = sin(rotLR);
	lookFB.z = -cos(rotLR);

	lookLR.x = sin(rotLR  + (float)PI / 2.0);
	lookLR.z = -cos(rotLR  + (float)PI / 2.0);
}

void Player::LookUD() {
	rotUD += deltaRotUD;

	
	lookFB.y = sin(rotUD);

	lookLR.y = sin(rotUD + (float)PI / 2.0);
}
