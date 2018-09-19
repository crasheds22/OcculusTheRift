#pragma once

#include <gl/glut.h>

class Projection
{
	public:
		Projection();
		Projection(GLdouble theMin, GLdouble theMax);
		virtual~Projection();
		GLdouble GetMinProjection();
		GLdouble GetMaxProjection();

	private:
		GLdouble minProjection;
		GLdouble maxProjection;
};