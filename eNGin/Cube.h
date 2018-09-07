#ifndef CUBE_H
#define CUBE_H

#include <gl/glut.h>

class Cube{
public:
	Cube();

	void Update();

	void Draw();
private:
	struct Point {
		float x, y, z;
	};

	Point vertices[8];

	struct RGB {
		float r, g, b;
	};

	RGB colours[8];

	//-----------------------------------------------------

	void Polygons(int a, int b, int c, int d);
};

#endif