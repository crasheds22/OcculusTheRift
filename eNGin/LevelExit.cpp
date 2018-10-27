#include <pch.h>
#include "LevelExit.h"

LevelExit::LevelExit(float x, float y, float z, Model * mod, Texture * tex) : Actor(mod, tex)
{
	this->SetPos(x, y, z);

	collisionBox.SetMinPoint(x - size, y, z - size);
	collisionBox.SetMaxPoint(x + size, y + size, z + size);
}