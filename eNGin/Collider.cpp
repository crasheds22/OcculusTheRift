
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



Vector3 Collider::ProjectionNormal(std::vector <Vector3> targetVertices, std::vector <Vector3> playerVertices)
{
	std::vector <Vector3> theNormalVectors;
	std::vector <Vector3> tempEdges;
	std::vector <Vector3> edgeVectors;
	Vector3 magnitudeCheck;
	Vector3 magnitudeComparison;
	int targetIndex;
	int playerIndex;
	Vector3 resultNormal;

	
	for (int ii = 0; ii < targetVertices.size(); ii++)
	{
		for (int jj = 0; jj < targetVertices.size(); jj++)
		{
			Vector3 tempVector;
			tempVector = targetVertices[ii] - targetVertices[jj];
			if (tempVector.VectorMagnitude() != 0)
			{
				tempEdges.push_back(tempVector);
			}
				
		}
	}

	std::cout << "temp edges size: " << tempEdges.size() << std::endl;

	for (int ii = 0; ii < tempEdges.size(); ii++)
	{
		for (int jj = 0; jj < tempEdges.size(); jj++)
		{
			Vector3 tempVector;
			tempVector = tempEdges[ii] - tempEdges[jj];
			if (tempVector.VectorMagnitude() != 0)
			{
				edgeVectors.push_back(tempVector);
			}
		}
	}

	std::cout << "edge vector size: " << edgeVectors.size() << std::endl;
	
	for (int ii = 0; ii < targetVertices.size(); ii++)
	{
		edgeVectors.push_back(targetVertices[ii]);
	}

	
	magnitudeCheck = edgeVectors[0] - playerVertices[0];
	for (int ii = 0; ii < edgeVectors.size(); ii++)
	{
		for (int jj = 0; jj < playerVertices.size(); jj++)
		{
			
			magnitudeComparison = edgeVectors[ii] - playerVertices[jj];
			if (magnitudeComparison.VectorMagnitude() < magnitudeCheck.VectorMagnitude())
			{
				magnitudeCheck = magnitudeComparison;
				targetIndex = ii;
				playerIndex = jj;
			}
		}
		
	}

	//theNormalVectors.push_back(edgeVectors[targetIndex].CrossProduct(playerVertices[playerIndex]));
	resultNormal = edgeVectors[targetIndex].CrossProduct(playerVertices[playerIndex]);
	/*
	for (int ii = 0; ii < edgeVectors.size(); ii++)
	{
		for (int jj = 0; jj < playerVertices.size(); jj++)
		{
			theNormalVectors.push_back(edgeVectors[ii].CrossProduct(playerVertices[jj]));
		}

	}


	resultNormal = theNormalVectors[0];
	for (int ii = 0; ii < theNormalVectors.size(); ii++)
	{
		if (theNormalVectors[ii].VectorMagnitude() < resultNormal.VectorMagnitude())
		{
			resultNormal = theNormalVectors[ii];
		}

	}
	*/
	
	std::cout << " Normal X:" << resultNormal.GetPointX() << std::endl;
	std::cout << " Normal Y:" << resultNormal.GetPointY() << std::endl;
	std::cout << " Normal Z:" << resultNormal.GetPointZ() << std::endl;
			

	return resultNormal;
}

// https://math.stackexchange.com/questions/633181/formula-to-project-a-vector-onto-a-plane
// https://www.maplesoft.com/support/help/maple/view.aspx?path=MathApps%2FProjectionOfVectorOntoPlane
// https://math.oregonstate.edu/home/programs/undergrad/CalculusQuestStudyGuides/vcalc/dotprod/dotprod.html
std::vector <Vector3> Collider::VectorProjection(std::vector <Vector3> targetVectors, std::vector <Vector3> playerVectors)
{
	Vector3 axisNormals;
	std::vector <Vector3> edgeVectors;
	Vector3 minNormal;
	Vector3 magnitudeCheck;
	Vector3 magnitudeComparison;
	int targetIndex;
	int playerIndex;
	std::vector <GLdouble> theScalar;
	std::vector <GLdouble> theMagnitude;
	std::vector <GLdouble> theUnitScalar;
	std::vector <Vector3> theProjection;

	axisNormals = ProjectionNormal(targetVectors, playerVectors);

	for (int ii = 0; ii < targetVectors.size() - 2; ii++)
	{
		Vector3 tempEdgeOne;
		Vector3 tempEdgeTwo;
		Vector3 tempEdgeClosest;

		tempEdgeOne = targetVectors[ii] - targetVectors[ii + 1];
		tempEdgeTwo = targetVectors[ii + 1] - targetVectors[ii + 2];
		tempEdgeClosest = tempEdgeOne - tempEdgeTwo;
		edgeVectors.push_back(tempEdgeClosest);
	}

	for (int ii = 0; ii < targetVectors.size(); ii++)
	{
		edgeVectors.push_back(targetVectors[ii]);
	}


	magnitudeCheck = edgeVectors[0] - playerVectors[0];
	for (int ii = 0; ii < edgeVectors.size(); ii++)
	{
		for (int jj = 0; jj < playerVectors.size(); jj++)
		{

			magnitudeComparison = edgeVectors[ii] - playerVectors[jj];
			if (magnitudeComparison.VectorMagnitude() < magnitudeCheck.VectorMagnitude())
			{
				magnitudeCheck = magnitudeComparison;
				targetIndex = ii;
				playerIndex = jj;
			}
		}

	}

	/*
	for (int hh = 0; hh < axisNormals.size(); hh++)
	{
		for (int ii = 0; ii < playerVectors.size(); ii++)
		{

			GLdouble tempScalar;
			tempScalar = axisNormals[hh].DotProduct(playerVectors[ii]);
			theScalar.push_back(tempScalar);
		}
	}
	*/
	
	
	GLdouble tempScalar;
	tempScalar = axisNormals.DotProduct(playerVectors[playerIndex]);
	theScalar.push_back(tempScalar);
	
	/*
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
	*/
	
	GLdouble squareX;
	GLdouble squareY;
	GLdouble squareZ;

	squareX = playerVectors[playerIndex].GetPointX() * playerVectors[playerIndex].GetPointX();
	squareY = playerVectors[playerIndex].GetPointY() * playerVectors[playerIndex].GetPointY();
	squareZ = playerVectors[playerIndex].GetPointZ() * playerVectors[playerIndex].GetPointZ();
	
	theMagnitude.push_back(squareX + squareY + squareZ);
	

	for (int ii = 0; ii < theScalar.size(); ii++)
	{
		for (int jj = 0; jj < theMagnitude.size(); jj++)
		{
			GLdouble tempUnitScalar;

			tempUnitScalar = theScalar[ii] / theMagnitude[jj];
			theUnitScalar.push_back(tempUnitScalar);
		}
	}
	
	
	for (int jj = 0; jj < theUnitScalar.size(); jj++)
	{
		Vector3 tempProjection;
		tempProjection = axisNormals.MultiplyByScalar(theUnitScalar[jj]);
		theProjection.push_back(tempProjection);
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
	std::vector <Vector3> targetProjection;
	std::vector <Vector3> playerProjection;
	std::vector <Vector3> theOverlap;
	
	targetProjection = VectorProjection(targetVectors, playerVectors);
	playerProjection = VectorProjection(playerVectors, targetVectors);
	
	for (int ii = 0; ii < targetProjection.size(); ii++)
	{
		for (int jj = 0; jj < playerProjection.size(); jj++)
		{
			Vector3 tempOverlap;
			tempOverlap = targetProjection[ii] - playerProjection[jj];
			
			std::cout << "the overlap: " << tempOverlap.VectorMagnitude() << std::endl;
			
			theOverlap.push_back(tempOverlap);
		}
	}
	
	std::cout << "the overlap size: " << theOverlap.size() << std::endl;

	
	for (int kk = 0; kk < theOverlap.size(); kk++)
	{
		std::cout << "===The overlap X===" << theOverlap[kk].GetPointX() << std::endl;
		std::cout << "===The overlap Y===" << theOverlap[kk].GetPointY() << std::endl;
		std::cout << "===The overlap Z===" << theOverlap[kk].GetPointZ() << std::endl;
	}
	
	
	return theOverlap;
}


// https://gamedev.stackexchange.com/questions/32545/what-is-the-mtv-minimum-translation-vector-in-sat-seperation-of-axis
// https://stackoverflow.com/questions/40255953/finding-the-mtv-minimal-translation-vector-using-separating-axis-theorem
// calculating depth penetration using SAT to find the minimum translation vector
Vector3 Collider::MinimumTranslationVector(std::vector <Vector3> AABBVectors, std::vector <Vector3> playerVectors )
{
	Vector3 axisNormal;
	std::vector <Vector3> theOverlap;
	GLdouble overlapDepth;
	Vector3 closestNormal;
	int closestIndex;
	Vector3 theMTV;

	axisNormal = ProjectionNormal(AABBVectors, playerVectors);
	
	
	theOverlap = ProjectionOverlap(AABBVectors, playerVectors);
	
	overlapDepth = theOverlap[0].VectorMagnitude();
	for (int ii = 0; ii < theOverlap.size(); ii++)
	{
		if ((theOverlap[ii].VectorMagnitude() < overlapDepth))
		{
			if (overlapDepth != 0)
			{
				overlapDepth = theOverlap[ii].VectorMagnitude();
				closestIndex = ii;
			}
		}
	}

	/*
	if (overlapDepth < 0)
	{
		overlapDepth = overlapDepth - 0.01;
	}
	else
	{
		overlapDepth = overlapDepth + 0.01;
	}
	*/

	overlapDepth = overlapDepth + 0.01;
	
	std::cout << "overlap depth: " << overlapDepth << std::endl;
	
	// MTV is usually the normal of the vector times the overlapdepth
	// projection normal is analogous to axis
	
	theMTV = axisNormal.MultiplyByScalar(overlapDepth);
	//theMTV = axisNormal.MultiplyByScalar(0.05);

	std::cout << " MTV X:" << theMTV.GetPointX() << std::endl;
	std::cout << " MTV Y:" << theMTV.GetPointY() << std::endl;
	std::cout << " MTV Z:" << theMTV.GetPointZ() << std::endl;
	
	

	return theMTV;
}
