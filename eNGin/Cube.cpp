#include <pch.h>
#include "Cube.h"

Cube::Cube() {
	vertices[0] = { -1, -1, -1 };
	vertices[1] = { 1, -1, -1 };
	vertices[2] = { 1, 1, -1 };
	vertices[3] = { -1, 1, -1 };
	vertices[4] = { -1, -1, 1 };
	vertices[5] = { 1, -1, 1 };
	vertices[6] = { 1, 1, 1 };
	vertices[7] = { -1, 1, 1 };

	colours[0] = { 0, 0, 0 };
	colours[1] = { 1, 0, 0 };
	colours[2] = { 1, 1, 0 };
	colours[3] = { 0, 1, 0 };
	colours[4] = { 0, 0, 1 };
	colours[5] = { 1, 0, 1 };
	colours[6] = { 1, 1, 1 };
	colours[7] = { 0, 1, 1 };
}

void Cube::Update() {
	/*for (int i = 0; i < 8; i++) {
		vertices[i].x += 0.0001;
		vertices[i].z += 0.0001;
	}*/
}

void Cube::Draw() {
	Polygons(0, 3, 2, 1);
	Polygons(2, 3, 7, 6);
	Polygons(0, 4, 7, 3);
	Polygons(1, 2, 6, 5);
	Polygons(4, 5, 6, 7);
	Polygons(0, 1, 5, 4);

}

void Cube::Polygons(int a, int b, int c, int d) {
	glBegin(GL_POLYGON);
		glColor3f(colours[a].r, colours[a].g, colours[a].b);
		glVertex3f(vertices[a].x, vertices[a].y, vertices[a].z);

		glColor3f(colours[b].r, colours[b].g, colours[b].b);
		glVertex3f(vertices[b].x, vertices[b].y, vertices[b].z);

		glColor3f(colours[c].r, colours[c].g, colours[c].b);
		glVertex3f(vertices[c].x, vertices[c].y, vertices[c].z);

		glColor3f(colours[d].r, colours[d].g, colours[d].b);
		glVertex3f(vertices[d].x, vertices[d].y, vertices[d].z);
	glEnd();
}