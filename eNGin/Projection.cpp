#include <pch.h>

#include "Projection.h"

Projection::Projection()
{

}

Projection::Projection(GLdouble theMin, GLdouble theMax)
{
	minProjection = theMin;
	maxProjection = theMax;
}

Projection::~Projection()
{

}

GLdouble Projection::GetMinProjection()
{
	return minProjection;
}

GLdouble Projection::GetMaxProjection()
{
	return maxProjection;
}