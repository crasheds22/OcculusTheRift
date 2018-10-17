#include "Projectile.h"

Projectile::Projectile(Actor* act, Model *mod, Texture *tex, double spd, Vector3 dir, Vector3 start) : Actor(mod, tex),
																									   timeAlive(0),
																									   direction(dir)
{
	owner = act;
	this->SetPos(start);
	this->SetMoveSpeed(spd);

	collisionBox.SetMaxPoint(position.GetPointX() + 0.5, position.GetPointY() + 0.5, position.GetPointZ() + 0.5);
	collisionBox.SetMinPoint(position.GetPointX() - 0.5, position.GetPointY() - 0.5, position.GetPointZ() - 0.5);
}

Projectile::~Projectile() {
	delete this;
}

void Projectile::Update(float deltaTime) {
	timeAlive += deltaTime;
	dT = deltaTime;

	Move();
}

void Projectile::Move() {
	this->SetPos(this->GetPos().AddVector(direction * moveSpeed * dT));
}

double Projectile::GetTime() {
	return timeAlive;
}
