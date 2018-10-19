#include "Coin.h"

Coin::Coin()
{

}

Coin::Coin(float x, float y, float z, Model * mod, Texture * tex)
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

int Coin::GetValue()
{
	return value;
}


void Coin::Update(float deltaTime)
{
	/*(if (rotate < 360)
	{
		rotate += rotSpeed * deltaTime;
	}
	else
	{
		rotate -= 360;
	}

	
	glPushMatrix();

	glTranslatef(position.GetPointX(), position.GetPointY() + 0.5, position.GetPointZ());
	glRotatef(rotate, 0, 1, 0);
	model->DrawModel(0, 0,0, texture->GetTexture(), texture->GetWidth(), texture->GetHeight());

	glPopMatrix();*/

	if (rotations.GetPointY() < 360) {
		rotations.SetPointY(rotations.GetPointY() + rotSpeed * deltaTime);
	}
	else {
		rotations.SetPointY(rotations.GetPointY() - 360);
	}
}
