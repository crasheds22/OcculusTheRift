#ifndef WALL_H
#define WALL_H

#include <gl\glut.h>

#include "Actor.h"
#include "Model.h"
#include "Texture.h"

class Wall : public Actor
{
public:
	Wall();

	Wall(float x, float y, float z, Model* mod, Texture* tex);


protected:
	float size = 4;
};



#endif

