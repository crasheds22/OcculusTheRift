
#include <pch.h>

#include <math.h>
#include <algorithm>
#include <gl/glut.h>

#include "Collider.h"
#include "Projection.h"
#include "Actor.h"


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

bool Collider::ProximityCull(Vector3 actorPosition, Actor &inputObject)
{
	Vector3 positionOffset;
	Vector3 minCullBox;
	Vector3 maxCullBox;

	positionOffset = Vector3(2.0, 2.0, 2.0);
	minCullBox = actorPosition.SubtractVector(positionOffset);
	maxCullBox = actorPosition.AddVector(positionOffset);

	return (maxCullBox.GetPointX() > inputObject.GetPos().GetPointX() &&
			minCullBox.GetPointX() < inputObject.GetPos().GetPointX() &&
			maxCullBox.GetPointY() > inputObject.GetPos().GetPointY() &&
			minCullBox.GetPointY() < inputObject.GetPos().GetPointY() &&
			maxCullBox.GetPointZ() > inputObject.GetPos().GetPointZ() &&
			minCullBox.GetPointZ() < inputObject.GetPos().GetPointZ());
		
}



void Collider::CollideWith(Actor *thisObject, Actor &otherObject)
{
	float intersectX = thisObject->GetPos().GetPointX() - otherObject.GetPos().GetPointX();
	float intersectZ = thisObject->GetPos().GetPointZ() - otherObject.GetPos().GetPointZ();

	if (abs(intersectX) > abs(intersectZ))
	{
		if (intersectX > 0)
		{
			thisObject->SetPos(otherObject.GetPos().GetPointX() + otherObject.GetScale().GetPointX() + 0.5, thisObject->GetPos().GetPointY(), thisObject->GetPos().GetPointZ());
		}
		else
		{
			thisObject->SetPos(otherObject.GetPos().GetPointX() - otherObject.GetScale().GetPointX() - 0.5, thisObject->GetPos().GetPointY(), thisObject->GetPos().GetPointZ());
		}
	}
	else
	{
		if (intersectZ > 0)
		{
			thisObject->SetPos(thisObject->GetPos().GetPointX(), thisObject->GetPos().GetPointY(), otherObject.GetPos().GetPointZ() + otherObject.GetScale().GetPointZ() + 0.5);
		}
		else
		{
			thisObject->SetPos(thisObject->GetPos().GetPointX(), thisObject->GetPos().GetPointY(), otherObject.GetPos().GetPointZ() - otherObject.GetScale().GetPointZ() - 0.5);
		}
	}
}
