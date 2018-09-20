
#include <pch.h>

#include <math.h>
#include <algorithm>
#include <gl/glut.h>

#include "Collider.h"
#include "Projection.h"


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

bool Collider::AABBtoAABB(Collider objectOther)
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

	theNormalVector = maxPoint.UnitNormal(minPoint);
	std::cout << "Normal X:" << theNormalVector.GetPointX() << std::endl;
	std::cout << "Normal Y:" << theNormalVector.GetPointY() << std::endl;
	std::cout << "Normal Z:" << theNormalVector.GetPointZ() << std::endl;
	
	return theNormalVector;
}


// ProjectionAB should equal the scalar multiplication magnitude of source times cosine theta and the projection normal 
// the dot product can be decomposed to magnitude of source times the magnitude of target 
// multiplied by the cosine angle of the two
// this is suspect 
// this should gives us the min and max scalar projection on the normal
/*
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
*/


// https://math.stackexchange.com/questions/633181/formula-to-project-a-vector-onto-a-plane
// https://www.maplesoft.com/support/help/maple/view.aspx?path=MathApps%2FProjectionOfVectorOntoPlane
Vector3 Collider::VectorProjection()
{
	Vector3 resultNormal;
	Vector3 edgeVector;
	GLdouble scalarProjection;
	Vector3 theProjection;
	Vector3 projectionOntoPlane;


	resultNormal = ProjectionNormal();
	
	
	edgeVector = maxPoint.SubtractVector(minPoint); // this is suspect

	scalarProjection = resultNormal.DotProduct(edgeVector);

	theProjection = resultNormal.MultiplyByScalar(scalarProjection);

	projectionOntoPlane = edgeVector.SubtractVector(theProjection);

	std::cout << "@@@the Vector Projection X @@@: " << projectionOntoPlane.GetPointX() << std::endl;
	std::cout << "@@@the Vector Projection Y @@@: " << projectionOntoPlane.GetPointY() << std::endl;
	std::cout << "@@@the Vector Projection Z @@@: " << projectionOntoPlane.GetPointZ() << std::endl;

	return projectionOntoPlane;
}


Vector3 Collider::ProjectionOverlap(Vector3 targetProjection)
{
	Vector3 theProjection;
	Vector3 theOverlap;

	theProjection = VectorProjection();
	
	theOverlap = theProjection.SubtractVector(targetProjection);
	std::cout << "===The overlap X===" << theOverlap.GetPointX() << std::endl;
	std::cout << "===The overlap Y===" << theOverlap.GetPointY() << std::endl;
	std::cout << "===The overlap Z===" << theOverlap.GetPointZ() << std::endl;

	return theOverlap;
}

//float intersectionDepth = (mina < minb)? (maxa - minb) : (mina - maxb);
// This is correct need more vertices current data structure is not suited to this collision resolution
/*
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
*/


// https://gamedev.stackexchange.com/questions/32545/what-is-the-mtv-minimum-translation-vector-in-sat-seperation-of-axis
// https://stackoverflow.com/questions/40255953/finding-the-mtv-minimal-translation-vector-using-separating-axis-theorem
// calculating depth penetration using SAT to find the minimum translation vector
Vector3 Collider::MinimumTranslationVector(Collider &projectTarget)
{
	//Projection targetObject;
	Vector3 targetObject;
	
	Vector3 overlapDepth;
	Vector3 theMTV;


	targetObject = projectTarget.VectorProjection();
	overlapDepth = ProjectionOverlap(targetObject);

	if (overlapDepth.GetPointX() < 0 || overlapDepth.GetPointY() < 0 || overlapDepth.GetPointZ() < 0)
	{
		std::cout << "Collision True" << std::endl;
		theMTV = ProjectionNormal().CrossProduct(overlapDepth);
	}
	else
	{
		theMTV = Vector3(0.0, 0.0, 0.0);
	}
	// MTV is usually the normal of the vector times the overlapdepth
	// projection normal is analogous to axis
	
	

	return theMTV;
}