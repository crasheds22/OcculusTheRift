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
			glRotatef(rotations.x, 1.0, 0.0, 0.0);
			glRotatef(rotations.y, 0.0, 1.0, 0.0);
			glRotatef(rotations.z, 0.0, 0.0, 1.0);

			glScalef(scale.x, scale.y, scale.z);

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

void Actor::SetRot(Point rot) {
	rotations = { rot.x, rot.y, rot.z };
}

void Actor::SetRot(GLdouble rotX, GLdouble rotY, GLdouble rotZ) {
	rotations = { rotX, rotY, rotZ };
}

void Actor::SetScale(Point sca) {
	scale = { sca.x, sca.y, sca.z };
}

void Actor::SetScale(GLdouble scaX, GLdouble scaY, GLdouble scaZ) {
	scale = { scaX, scaY, scaZ };
}

Vector3 Actor::GetPos() {
	return position;
}

Point Actor::GetRot() {
	return rotations;
}

Point Actor::GetScale() {
	return scale;
}

const Collider Actor::GetCollider()
{
	return collisionBox;
}
