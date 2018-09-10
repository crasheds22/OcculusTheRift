
#include <pch.h>

#include <math.h>
#include <algorithm>
#include <gl/glut.h>

#include "Collider.h"
#include "Projection.h"


using namespace std;

Collider::Collider() 
{
	minPoint = Vector3(0.0, 0.0, 0.0);
	maxPoint = Vector3(0.0, 0.0, 0.0);
}

void Collider::SetMinPoint(GLdouble tempX, GLdouble tempY, GLdouble tempZ) 
{
	minPoint = Vector3(tempX, tempY, tempZ);
}

void Collider::SetMaxPoint(GLdouble tempX, GLdouble tempY, GLdouble tempZ) 
{
	maxPoint = Vector3(tempX, tempY, tempZ);
}

Vector3 Collider::GetMinPoint() 
{
	return minPoint;
}

Vector3 Collider::GetMaxPoint() 
{
	return maxPoint;
}

bool Collider::AABBtoAABB(Collider &objectOther)
{


	return (	maxPoint.GetPointX() > objectOther.minPoint.GetPointX() &&
				minPoint.GetPointX() < objectOther.maxPoint.GetPointX() &&
				maxPoint.GetPointY() > objectOther.minPoint.GetPointY() &&
				minPoint.GetPointY() < objectOther.maxPoint.GetPointY() &&
				maxPoint.GetPointZ() > objectOther.minPoint.GetPointZ() &&
				minPoint.GetPointZ() < objectOther.maxPoint.GetPointZ());
}

bool Collider::operator < (Collider &other) 
{
	return AABBtoAABB(other);
}

bool Collider::operator > (Collider &other) 
{
	return !operator<(other);
}



Vector3 Collider::ProjectionNormal()
{
	Vector3 theNormalVector;

	theNormalVector = minPoint.UnitNormal(maxPoint);
	
	return theNormalVector;
}


// ProjectionAB should equal the scalar multiplication magnitude of source times cosine theta and the projection normal 
// the dot product can be decomposed to magnitude of source times the magnitude of target 
// multiplied by the cosine angle of the two
// this is suspect 
Projection Collider::VectorProjection()
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
GLdouble Collider::ProjectionOverlap(Projection targetProjection)
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

// https://gamedev.stackexchange.com/questions/32545/what-is-the-mtv-minimum-translation-vector-in-sat-seperation-of-axis
// https://stackoverflow.com/questions/40255953/finding-the-mtv-minimal-translation-vector-using-separating-axis-theorem
// calculating depth penetration using SAT to find the minimum translation vector
Vector3 Collider::MinimumTranslationVector(Collider &projectTarget)
{
	Projection targetObject;
	Vector3 sourceVector;
	Vector3 targetVector;
	Vector3 unitVector;
	GLdouble overlapDepth;
	GLdouble sourceMagnitude;
	GLdouble targetMagnitude;
	GLdouble sourceTheta;
	Vector3 theMTV;

	targetObject = projectTarget.VectorProjection();

	if (AABBtoAABB(projectTarget))
	{
		overlapDepth = ProjectionOverlap(targetObject);
	}

	// MTV is usually the normal of the vector times the overlapdepth
	// projection normal is analogous to axis
	
	theMTV = ProjectionNormal().MultiplyByScalar(overlapDepth);

	return theMTV;
}