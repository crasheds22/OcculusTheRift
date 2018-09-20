#include <pch.h>
#include "Cube.h"

Cube::Cube() {
	vertices[0] = Vector3( -1, -1, -1 );
	vertices[1] = Vector3( 1, -1, -1 );
	vertices[2] = Vector3( 1, 1, -1 );
	vertices[3] = Vector3( -1, 1, -1 );
	vertices[4] = Vector3( -1, -1, 1 );
	vertices[5] = Vector3( 1, -1, 1 );
	vertices[6] = Vector3( 1, 1, 1 );
	vertices[7] = Vector3( -1, 1, 1 );

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
		std::cout << "cube a vertex X: " <<vertices[a].GetPointX() << std::endl;
		glVertex3f(vertices[a].GetPointX(), vertices[a].GetPointY(), vertices[a].GetPointZ());

		glColor3f(colours[b].r, colours[b].g, colours[b].b);
		glVertex3f(vertices[b].GetPointX(), vertices[b].GetPointY(), vertices[b].GetPointZ());

		glColor3f(colours[c].r, colours[c].g, colours[c].b);
		glVertex3f(vertices[c].GetPointX(), vertices[c].GetPointY(), vertices[c].GetPointZ());

		glColor3f(colours[d].r, colours[d].g, colours[d].b);
		glVertex3f(vertices[d].GetPointX(), vertices[d].GetPointY(), vertices[d].GetPointZ());
	glEnd();
}

void Cube::SetAABB()
{
	collisionBox.SetMaxPoint(1, 1, 1);
	collisionBox.SetMinPoint(-1, -1, -1);
}