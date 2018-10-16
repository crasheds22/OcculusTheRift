#include "Projectile.h"

Projectile::Projectile(Actor* act, Model *mod, Texture *tex, double spd, Vector3 dir, Vector3 start) : Actor(mod, tex),
																									   timeAlive(0),
																									   direction(dir)
{
	owner = act;
	this->SetPos(start);
	this->SetMoveSpeed(spd);
}

void Projectile::Update(float deltaTime) {
	timeAlive += deltaTime;
	dT = deltaTime;

	Move();
}

void Projectile::Move() {
	this->SetPos(this->GetPos().AddVector(direction * moveSpeed * dT));
}
