#ifndef COIN_H
#define COIN_H

#include <gl\glut.h>

#include "Actor.h"
#include "Model.h"
#include "Texture.h"

class Coin : public Actor
{
public:
	Coin();

	Coin(float x, float y, float z, Model* mod, Texture* tex);

	int GetValue();

	void Update(float deltaTime) override;
protected:
	float size = 2; /*<! size of the wall's hit box>*/
	int value = 20;
	float rotate = 0;
	float rotSpeed = 90;
};



#endif