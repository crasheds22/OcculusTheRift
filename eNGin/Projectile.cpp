#include "Projectile.h"

Projectile::Projectile(Actor* act, Model *mod, Texture *tex) : Actor(mod, tex),
															   timeAlive(0)
{
	owner = act;
}

void Projectile::Update(float deltaTime) {
	timeAlive += glutGet(GLUT_ELAPSED_TIME);

	if (timeAlive > 5000)
		delete this;
	else
		Move();
}

void Projectile::Move() {
	this->SetPos(this->GetPos() + direction * speed);
}

void Projectile::SetSpeed(double spd) {
	speed = spd;
}

void Projectile::SetDirection(Vector3 &dir) {
	direction = dir;
}

void Projectile::SetStartPosition(Vector3 &start) {
	startPos = start;
}
