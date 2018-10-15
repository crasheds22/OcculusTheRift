#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Actor.h"
#include "Vector3.h"

class Projectile : public Actor {
public:
	Projectile(Actor* act, Model *mod, Texture *tex);

	void Update(float deltaTime) override;

	void Move();

	void SetSpeed(double spd);
	void SetDirection(Vector3 &dir);
	void SetStartPosition(Vector3 &start);

private:
	Actor* owner;

	double speed;
	double timeAlive;

	Vector3 startPos;
	Vector3 direction;

};

#endif
