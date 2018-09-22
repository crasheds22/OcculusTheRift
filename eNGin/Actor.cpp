#include <pch.h>

#include "Actor.h"

Actor::Actor() : position{ 0.0, 0.0, 0.0 },
				 rotations{ 0.0, 0.0, 0.0 },
				 scale{ 1.0, 1.0, 1.0 }
{

}

Actor::Actor(Model* mod, Texture* tex) : position{ 0.0, 0.0, 0.0 },
										 rotations{ 0.0, 0.0, 0.0 },
										 scale{ 1.0, 1.0, 1.0 },
										 model(mod),
										 texture(tex)
{

}

void Actor::Update() {

}

void Actor::Draw() {
	if ((model != NULL) && (texture != NULL))
	{
		glPushMatrix();
			glRotatef(rotations.GetPointX(), 1.0, 0.0, 0.0);
			glRotatef(rotations.GetPointY(), 0.0, 1.0, 0.0);
			glRotatef(rotations.GetPointZ(), 0.0, 0.0, 1.0);

			glScalef(scale.GetPointX(), scale.GetPointY(), scale.GetPointZ());

			model->DrawModel(position.GetPointX(), position.GetPointY(), position.GetPointZ(),
				texture->GetTexture(), texture->GetWidth(), texture->GetHeight());
		glPopMatrix();
	}
}

void Actor::SetPos(Vector3 pos) {
	position = Vector3(pos.GetPointX(), pos.GetPointY(), pos.GetPointZ());
}

void Actor::SetPos(GLdouble tempX, GLdouble tempY, GLdouble tempZ) {
	position = Vector3(tempX, tempY, tempZ);
}

void Actor::SetRot(Vector3 rot) {
	rotations = { rot.GetPointX(), rot.GetPointY(), rot.GetPointZ() };
}

void Actor::SetRot(GLdouble rotX, GLdouble rotY, GLdouble rotZ) {
	rotations = { rotX, rotY, rotZ };
}

void Actor::SetScale(Vector3 sca) {
	scale = { sca.GetPointX(), sca.GetPointY(), sca.GetPointZ() };
}

void Actor::SetScale(GLdouble scaX, GLdouble scaY, GLdouble scaZ) {
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

const Collider Actor::GetCollider()
{
	return collisionBox;
}
