
#include <pch.h>

#include <math.h>
#include <algorithm>

#include "AABB.h"
#include "Projection.h"

using namespace std;

AABB::AABB() 
{
	minPoint = Vector3(0.0, 0.0, 0.0);
	maxPoint = Vector3(0.0, 0.0, 0.0);
}

void AABB::SetMinPoint(GLdouble tempX, GLdouble tempY, GLdouble tempZ) 
{
	minPoint = Vector3(tempX, tempY, tempZ);
}

void AABB::SetMaxPoint(GLdouble tempX, GLdouble tempY, GLdouble tempZ) 
{
	maxPoint = Vector3(tempX, tempY, tempZ);
}

Vector3 AABB::GetMinPoint() 
{
	return minPoint;
}

Vector3 AABB::GetMaxPoint() 
{
	return maxPoint;
}

bool AABB::AABBtoAABB(AABB &objectOther)
{


	return (	maxPoint.GetPointX() > objectOther.minPoint.GetPointX() &&
				minPoint.GetPointX() < objectOther.maxPoint.GetPointX() &&
				maxPoint.GetPointY() > objectOther.minPoint.GetPointY() &&
				minPoint.GetPointY() < objectOther.maxPoint.GetPointY() &&
				maxPoint.GetPointZ() > objectOther.minPoint.GetPointZ() &&
				minPoint.GetPointZ() < objectOther.maxPoint.GetPointZ());
}

bool AABB::operator<(AABB &other) 
{
	return AABBtoAABB(other);
}

bool AABB::operator>(AABB &other) 
{
	return !operator<(other);
}


Vector3 AABB::ProjectionNormal()
{
	Vector3 theProjection;
	Vector3 theNormalVector;

	theProjection = maxPoint.SubtractVector(minPoint);
	theNormalVector = theProjection.UnitNormal();

	return theNormalVector;
}


Projection AABB::VectorProjection()
{
	Vector3 resultNormal;
	GLdouble projectionOne;
	GLdouble projectionTwo;
	Projection resultProjection;

	resultNormal = ProjectionNormal();
	projectionOne = minPoint.DotProduct(resultNormal);
	projectionTwo = maxPoint.DotProduct(resultNormal);

	resultProjection = Projection(std::min(projectionOne, projectionTwo), std::max(projectionOne, projectionTwo));

	return resultProjection;
}


//float intersectionDepth = (mina < minb)? (maxa - minb) : (mina - maxb);
GLdouble AABB::ProjectionOverlap(Projection targetProjection)
{
	Projection theProjection;
	GLdouble theOverlap;

	theProjection = VectorProjection();

	if (theProjection.GetMinProjection() < targetProjection.GetMinProjection())
	{
		theOverlap = theProjection.GetMaxProjection() - targetProjection.GetMinProjection();
	}
	else
	{
		theOverlap = theProjection.GetMinProjection() - targetProjection.GetMaxProjection();
	}

	return theOverlap;

}

// https://stackoverflow.com/questions/40255953/finding-the-mtv-minimal-translation-vector-using-separating-axis-theorem
// calculating depth penetration using SAT to find the minimum translation vector
Vector3 AABB::MinimumTranslationVector(AABB &projectTarget)
{
	Projection targetObject;
	GLdouble overlapDepth;
	Vector3 theMTV;

	targetObject = projectTarget.VectorProjection();

	if (AABBtoAABB(projectTarget))
	{
		overlapDepth = ProjectionOverlap(targetObject);
	}

	// projection normal is analogous to axis
	theMTV.SetPointX(ProjectionNormal().GetPointX() * overlapDepth);
	theMTV.SetPointY(ProjectionNormal().GetPointY() * overlapDepth);
	theMTV.SetPointZ(ProjectionNormal().GetPointZ() * overlapDepth);

	return theMTV;
}