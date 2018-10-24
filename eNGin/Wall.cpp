#include <pch.h>
#include "Wall.h"

Wall::Wall(float x, float y, float z, Model * mod, Texture * tex) : Actor(mod, tex)
{
	this->SetPos(x, y, z);
	
	collisionBox.SetMinPoint(x - size, y, z - size);
	collisionBox.SetMaxPoint(x + size, y + size, z + size);
}
