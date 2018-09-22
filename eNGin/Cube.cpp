#include <pch.h>

#include <algorithm>
#include <math.h>

#include "Cube.h"

Cube::Cube() {
	vertices[0] = Vector3( -1.0, -1.0, -1.0 );
	vertices[1] = Vector3( 1.0, -1.0, -1.0 );
	vertices[2] = Vector3( 1.0, 1.0, -1.0 );
	vertices[3] = Vector3( -1.0, 1.0, -1.0 );
	vertices[4] = Vector3( -1.0, -1.0, 1.0 );
	vertices[5] = Vector3( 1.0, -1.0, 1.0 );
	vertices[6] = Vector3( 1.0, 1.0, 1.0 );
	vertices[7] = Vector3( -1.0, 1.0, 1.0 );

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
	x = GetPos().GetPointX();
	y = GetPos().GetPointY();
	z = GetPos().GetPointZ();
	x += 0.0001;
	SetPos(x, y, z);
}

void Cube::Draw()  
{
	Update();
	Polygons(0, 3, 2, 1);
	Polygons(2, 3, 7, 6);
	Polygons(0, 4, 7, 3);
	Polygons(1, 2, 6, 5);
	Polygons(4, 5, 6, 7);
	Polygons(0, 1, 5, 4);



	SetAABB();

}

void Cube::Polygons(int a, int b, int c, int d) {
	glBegin(GL_POLYGON);
		glColor3f(colours[a].r, colours[a].g, colours[a].b);
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
	Vector3 theMin;
	Vector3 theMax;
	Vector3 * AABBVertices;

	AABBVertices = new Vector3[8];

	theMin = vertices[0];
	theMax = vertices[0];

	for (int ii = 0; ii < 8; ii++)
	{
		AABBVertices[ii].SetPointX(vertices[ii].GetPointX() + GetPos().GetPointX());
		AABBVertices[ii].SetPointY(vertices[ii].GetPointY() + GetPos().GetPointY());
		AABBVertices[ii].SetPointZ(vertices[ii].GetPointZ() + GetPos().GetPointZ());
	}
	
	for (int ii = 0; ii < 8; ii++)
	{
		if (vertices[ii].GetPointX() < theMin.GetPointX())
		{
			theMin.SetPointX(vertices[ii].GetPointX());
		}

		if (vertices[ii].GetPointY() < theMin.GetPointY())
		{
			theMin.SetPointY(vertices[ii].GetPointY());
		}

		if (vertices[ii].GetPointZ() < theMin.GetPointZ())
		{
			theMin.SetPointZ(vertices[ii].GetPointZ());
		}

		if (vertices[ii].GetPointX() > theMax.GetPointX())
		{
			theMax.SetPointX(vertices[ii].GetPointX());
		}

		if (vertices[ii].GetPointY() > theMax.GetPointY())
		{
			theMax.SetPointY(vertices[ii].GetPointY());
		}

		if (vertices[ii].GetPointZ() > theMax.GetPointZ())
		{
			theMax.SetPointZ(vertices[ii].GetPointZ());
		}

	}

	collisionBox.SetMaxPoint(x + GetScale().x, y + GetScale().y, z + GetScale().z);
	collisionBox.SetMinPoint(x + -GetScale().x, y + -GetScale().y, z + -GetScale().z);
}


