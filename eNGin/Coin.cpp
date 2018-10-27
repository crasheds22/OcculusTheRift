#include <pch.h>
#include "Coin.h"

Coin::Coin(float x, float y, float z, Model * mod, Texture * tex) : Actor(mod, tex)
{
	this->SetPos(x, y, z);

	collisionBox.SetMinPoint(x - size, y, z - size);
	collisionBox.SetMaxPoint(x + size, y + size, z + size);
}

int Coin::GetValue()
{
	return value;
}

void Coin::Update(float deltaTime)
{
	if (rotations.GetPointY() < 360) {
		rotations.SetPointY(rotations.GetPointY() + rotSpeed * deltaTime);
	}
	else {
		rotations.SetPointY(rotations.GetPointY() - 360);
	}
}
