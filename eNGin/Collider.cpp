
#include <pch.h>

#include <math.h>
#include <algorithm>
#include <gl/glut.h>
#include <vector>

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



std::vector <Vector3> Collider::ProjectionNormal(std::vector <Vector3> targetVertices, std::vector <Vector3> playerVertices)
{
	std::vector <Vector3> theNormalVectors;
	

	for (int ii = 0; ii < targetVertices.size(); ii++)
	{
		for (int jj = 0; jj < playerVertices.size(); jj++)
		{
			theNormalVectors.push_back(targetVertices[ii].CrossProduct(playerVertices[jj]));
			/*
			std::cout << "index: " << ii << " Normal X:" << theNormalVectors[ii].GetPointX() << std::endl;
			std::cout << "index: " << ii << " Normal Y:" << theNormalVectors[ii].GetPointY() << std::endl;
			std::cout << "index: " << ii << " Normal Z:" << theNormalVectors[ii].GetPointZ() << std::endl;
			*/
		}
		
	}
	



	return theNormalVectors;
}

// https://math.stackexchange.com/questions/633181/formula-to-project-a-vector-onto-a-plane
// https://www.maplesoft.com/support/help/maple/view.aspx?path=MathApps%2FProjectionOfVectorOntoPlane
// https://math.oregonstate.edu/home/programs/undergrad/CalculusQuestStudyGuides/vcalc/dotprod/dotprod.html
std::vector <Vector3> Collider::VectorProjection(std::vector <Vector3> targetVectors, std::vector <Vector3> playerVectors)
{
	std::vector <Vector3> axisNormals;
	Vector3 minNormal;
	std::vector <GLdouble> theScalar;
	std::vector <GLdouble> theMagnitude;
	std::vector <GLdouble> theUnitScalar;
	std::vector <Vector3> theProjection;

	axisNormals = ProjectionNormal(targetVectors, playerVectors);

	minNormal = axisNormals[0];
	for (int ii = 0; ii < axisNormals.size(); ii++)
	{
		if (axisNormals[ii].VectorMagnitude() < minNormal.VectorMagnitude())
		{
			minNormal = axisNormals[ii];
		}
	}


	for (int ii = 0; ii < playerVectors.size(); ii++)
	{
		
		GLdouble tempScalar;
		tempScalar = minNormal.DotProduct(playerVectors[ii]);
		theScalar.push_back(tempScalar);
		
	}

	for (int ii = 0; ii < playerVectors.size(); ii++)
	{
		GLdouble squareX;
		GLdouble squareY;
		GLdouble squareZ;

		squareX = playerVectors[ii].GetPointX() * playerVectors[ii].GetPointX();
		squareY = playerVectors[ii].GetPointY() * playerVectors[ii].GetPointY();
		squareZ = playerVectors[ii].GetPointZ() * playerVectors[ii].GetPointZ();

		theMagnitude.push_back( squareX + squareY + squareZ);
	}

	for (int ii = 0; ii < theScalar.size(); ii++)
	{
		for (int jj = 0; jj < theMagnitude.size(); jj++)
		{
			GLdouble tempUnitScalar;

			tempUnitScalar = theScalar[ii] / theMagnitude[jj];
			theUnitScalar.push_back(tempUnitScalar);
		}
	}

	for (int ii = 0; ii < axisNormals.size(); ii++)
	{
		for (int jj = 0; jj < theUnitScalar.size(); jj++)
		{
			Vector3 tempProjection;
			tempProjection = axisNormals[ii].MultiplyByScalar(theUnitScalar[jj]);
			theProjection.push_back(tempProjection);
		}
	}

	std::cout << "Projection Size: " << theProjection.size() << std::endl;

	/*
	for (int ii = 0; ii < theProjection.size(); ii++)
	{
		std::cout << "@@@the Vector Projection X @@@: " << theProjection[ii].GetPointX() << std::endl;
		std::cout << "@@@the Vector Projection Y @@@: " << theProjection[ii].GetPointY() << std::endl;
		std::cout << "@@@the Vector Projection Z @@@: " << theProjection[ii].GetPointZ() << std::endl;
	}
	*/
	
	return theProjection;
}

//float intersectionDepth = (mina < minb)? (maxa - minb) : (mina - maxb);
std::vector <Vector3> Collider::ProjectionOverlap(std::vector <Vector3> targetVectors, std::vector <Vector3> playerVectors)
{
	std::vector <Vector3> targetNormals;
	std::vector <Vector3> playerNormals;
	std::vector <Vector3> checkParallel;
	std::vector <Vector3> targetProjection;
	std::vector <Vector3> playerProjection;
	std::vector <Vector3> theOverlap;
	
	std::cout << "target projection start" << std::endl;
	targetProjection = VectorProjection(targetVectors, playerVectors);
	std::cout << "target projection end" << std::endl;

	std::cout << "player projection start" << std::endl;
	playerProjection = VectorProjection(playerVectors, targetVectors);
	std::cout << "player projection end" << std::endl;

	for (int ii = 0; ii < targetProjection.size(); ii++)
	{
		for (int jj = 0; jj < playerProjection.size(); jj++)
		{
			Vector3 tempOverlap;
			tempOverlap = targetProjection[ii] - playerProjection[jj];
			
			//std::cout << "the overlap: " << tempOverlap.VectorMagnitude() << std::endl;
			
			theOverlap.push_back(tempOverlap);
		}
	}
	
	/*
	for (int kk = 0; kk < theOverlap.size(); kk++)
	{
		std::cout << "===The overlap X===" << theOverlap[kk].GetPointX() << std::endl;
		std::cout << "===The overlap Y===" << theOverlap[kk].GetPointY() << std::endl;
		std::cout << "===The overlap Z===" << theOverlap[kk].GetPointZ() << std::endl;
	}
	*/
	
	return theOverlap;
}


// https://gamedev.stackexchange.com/questions/32545/what-is-the-mtv-minimum-translation-vector-in-sat-seperation-of-axis
// https://stackoverflow.com/questions/40255953/finding-the-mtv-minimal-translation-vector-using-separating-axis-theorem
// calculating depth penetration using SAT to find the minimum translation vector
Vector3 Collider::MinimumTranslationVector(std::vector <Vector3> AABBVectors, std::vector <Vector3> playerVectors )
{
	std::vector <Vector3> axisNormal;
	std::vector <Vector3> theOverlap;
	GLdouble overlapDepth;
	Vector3 closestNormal;
	Vector3 theMTV;

	axisNormal = ProjectionNormal(AABBVectors, playerVectors);
	theOverlap = ProjectionOverlap(AABBVectors, playerVectors);
	
	closestNormal = axisNormal[0];
	for (int ii = 0; ii < axisNormal.size(); ii++)
	{
		if (axisNormal[ii].VectorMagnitude() < closestNormal.VectorMagnitude())
		{
			closestNormal = axisNormal[ii];
		}
	}

	overlapDepth = theOverlap[0].VectorMagnitude();
	for (int ii = 0; ii < theOverlap.size(); ii++)
	{
		if (theOverlap[ii].VectorMagnitude() > overlapDepth)
		{
			overlapDepth = theOverlap[ii].VectorMagnitude();
		}
	}
	
	std::cout << "overlap depth: " << overlapDepth << std::endl;
	
	// MTV is usually the normal of the vector times the overlapdepth
	// projection normal is analogous to axis
	theMTV = closestNormal.MultiplyByScalar(overlapDepth);
	
	std::cout << " MTV X:" << theMTV.GetPointX() << std::endl;
	std::cout << " MTV Y:" << theMTV.GetPointY() << std::endl;
	std::cout << " MTV Z:" << theMTV.GetPointZ() << std::endl;
	
	

	return theMTV;
}
