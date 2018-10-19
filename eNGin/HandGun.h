#pragma once
#include "Actor.h"
class HandGun :
	public Actor
{
public:
	HandGun();
	HandGun(float x, float y, float z, Model* mod, Texture* tex);
	~HandGun();

	void Update(float deltaTime) override;
};

