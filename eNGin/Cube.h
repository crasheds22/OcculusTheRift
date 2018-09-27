#ifndef CUBE_H
#define CUBE_H

#include <gl/glut.h>

#include "Actor.h"

class Cube : public Actor
{
	public:
		Cube();

		void Update();

		void Draw() override;

		void SetRot(Vector3 rot) override;
		
		void SetRot(GLdouble rotX, GLdouble rotY, GLdouble rotZ) override;

		void CalculateFaceNormal(Vector3 *AABBVertices);

		void SetAABB();



	private:
		struct Point {
			float x, y, z;
		};

		Vector3 vertices[8];

		struct RGB {
			float r, g, b;
		};

		RGB colours[8];

		Vector3 normals[6];

		//-----------------------------------------------------

		void Polygons(int a, int b, int c, int d);
		
};

#endif