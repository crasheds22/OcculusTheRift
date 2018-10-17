#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Actor.h"
#include "Vector3.h"

class Projectile : public Actor {
public:
	Projectile(Actor* act, Model *mod, Texture *tex, double spd, Vector3 dir, Vector3 start);
	~Projectile();

	void Update(float deltaTime) override;

	void Move();

	double GetTime();

private:
	Actor* owner;

	double timeAlive;
	double dT;

	Vector3 direction;

};

#endif
