#include "Actor.h"

Actor::Actor() : position(0.0, 0.0, 0.0),
				 rotations{ 0.0, 0.0, 0.0 },
				 scale{ 1.0, 1.0, 1.0 }
{

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
