#include "LevelExit.h"

LevelExit::LevelExit()
{

}

LevelExit::LevelExit(float x, float y, float z, Model * mod, Texture * tex)
{
	Vector3 temp;

	temp.SetPointX(x);

	temp.SetPointY(y);

	temp.SetPointZ(z);

	SetPos(temp);

	//SetScale(Vector3(size, size, size));

	model = mod;

	texture = tex;


	collisionBox.SetMinPoint(x - size, y, z - size);
	collisionBox.SetMaxPoint(x + size, y + size, z + size);

}