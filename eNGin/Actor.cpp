#include <pch.h>

#include "Actor.h"

Actor::Actor() : moveSpeed(0.0),
			 	 rotateSpeed(0.0),
				 maxHealth(0.0),
				 health(maxHealth),
				 position{ 0.0, 0.0, 0.0 },
				 rotations{ 0.0, 0.0, 0.0 },
				 scale{ 1.0, 1.0, 1.0 }
{

}

Actor::Actor(Model* mod, Texture* tex) : moveSpeed(0.0),
										 rotateSpeed(0.0),
										 maxHealth(0.0),
										 health(maxHealth),
										 position{ 0.0, 0.0, 0.0 },
										 rotations{ 0.0, 0.0, 0.0 },
										 scale{ 1.0, 1.0, 1.0 },
										 model(mod),
										 texture(tex)
{

}

void Actor::Draw() {
	if ((model != NULL) && (texture != NULL))
	{
		glPushMatrix();
			glTranslatef(position.GetPointX(), position.GetPointY(), position.GetPointZ());

			glRotatef(rotations.GetPointX(), 1.0, 0.0, 0.0);
			glRotatef(rotations.GetPointY(), 0.0, 1.0, 0.0);
			glRotatef(rotations.GetPointZ(), 0.0, 0.0, 1.0);

			model->DrawModel(0, 0, 0, texture->GetTexture(), texture->GetWidth(), texture->GetHeight());
		glPopMatrix();
	}
}

void Actor::SetPos(Vector3 pos) {
	position = Vector3(pos.GetPointX(), pos.GetPointY(), pos.GetPointZ());
}

void Actor::SetPos(double tempX, double tempY, double tempZ) {
	position = Vector3(tempX, tempY, tempZ);
}

void Actor::SetRot(Vector3 rot) {
	rotations = { rot.GetPointX(), rot.GetPointY(), rot.GetPointZ() };
}

void Actor::SetRot(double rotX, double rotY, double rotZ) {
	rotations = { rotX, rotY, rotZ };
}

void Actor::SetScale(Vector3 sca) {
	scale = { sca.GetPointX(), sca.GetPointY(), sca.GetPointZ() };
}

void Actor::SetScale(double scaX, double scaY, double scaZ) {
	scale = { scaX, scaY, scaZ };
}

Vector3 Actor::GetPos() {
	return position;
}

Vector3 Actor::GetRot() {
	return rotations;
}

Vector3 Actor::GetScale() {
	return scale;
}

Collider Actor::GetCollider()
{
	return collisionBox;
}

void Actor::SetMoveSpeed(double spd) {
	moveSpeed = spd;
}

void Actor::SetRotateSpeed(double spd) {
	rotateSpeed = spd;
}

double Actor::GetRotateSpeed() {
	return rotateSpeed;
}

double Actor::GetMoveSpeed() {
	return moveSpeed;
}

void Actor::SetMaxHealth(int max)
{
	maxHealth = max;
}

int Actor::GetMaxHealth()
{
	return maxHealth;
}

void Actor::SetCurrentHealth(int cur)
{
	health = cur;
}

int Actor::GetCurrentHealth()
{
	return health;
}
