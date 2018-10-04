#ifndef LEVELEXIT_H
#define LEVELEXIT_H

#include <gl\glut.h>

#include "Actor.h"
#include "Model.h"
#include "Texture.h"

class LevelExit : public Actor
{
public:
	LevelExit();

	LevelExit(float x, float y, float z, Model* mod, Texture* tex);


protected:
	float size = 1;
};

#endif
