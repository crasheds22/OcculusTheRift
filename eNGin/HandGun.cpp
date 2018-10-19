#include "HandGun.h"



HandGun::HandGun()
{
}

HandGun::HandGun(float x, float y, float z, Model* mod, Texture* tex)
{
	Vector3 temp;

	temp.SetPointX(x);

	temp.SetPointY(y);

	temp.SetPointZ(z);

	SetPos(temp);

	//SetScale(Vector3(size, size, size));

	model = mod;

	texture = tex;

}


HandGun::~HandGun()
{
}

void HandGun::Update(float deltaTime)
{
	glPushMatrix();

	glTranslatef(position.GetPointX(), position.GetPointY() + 0.5, position.GetPointZ());
	model->DrawModel(0, 0, 0, texture->GetTexture(), texture->GetWidth(), texture->GetHeight());

	glPopMatrix();
}
