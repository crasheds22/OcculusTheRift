#include "Projectile.h"
#include <math.h>

Projectile::Projectile(Actor* act, Model *mod, Texture *tex, double spd, Vector3 dir, Vector3 start) : Actor(mod, tex),
timeAlive(0),
direction(dir)
{
	owner = act;
	this->SetPos(start);
	this->SetMoveSpeed(spd);

	Vector3 Vn(0, 1, 0);
	Vector3 Va(start), Vb(dir);
	Vector3 cross = Vb.CrossProduct(Va);
	double dot = Va.DotProduct(Vb);

	double angle = atan2(cross.DotProduct(Vn), dot);
	angle *= 180 / 3.141592653;

	this->SetRot(0.0, angle, 0.0);
}

Projectile::~Projectile() {
	delete this;
}

void Projectile::Update(float deltaTime) {
	timeAlive += deltaTime;
	dT = deltaTime;

	collisionBox.SetMaxPoint(position.GetPointX() + 0.5, position.GetPointY() + 0.5, position.GetPointZ() + 0.5);
	collisionBox.SetMinPoint(position.GetPointX() - 0.5, position.GetPointY() - 0.5, position.GetPointZ() - 0.5);

	Move();
}

void Projectile::Move() {
	this->SetPos(this->GetPos().AddVector(direction * moveSpeed * dT));
}

double Projectile::GetTime() {
	return timeAlive;
}
