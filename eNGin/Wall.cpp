#include "Wall.h"

Wall::Wall()
{

}

Wall::Wall(float x, float y, float z, Model * mod, Texture * tex)
{
	Vector3 temp;

	temp.SetPointX(x);

	temp.SetPointY(y);

	temp.SetPointZ(z);

	position = temp;

	model = mod;

	texture = tex;

	collisionBox.SetMinPoint(x - size, y - (size*2), z - size);
	collisionBox.SetMaxPoint(x + size, y + (size * 2), z + size);

}
