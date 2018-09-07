#include "AABB.h"

AABB::AABB() {
	minPoint = Vector3(0.0, 0.0, 0.0);
	maxPoint = Vector3(0.0, 0.0, 0.0);
}

void AABB::SetMinPoint(GLdouble tempX, GLdouble tempY, GLdouble tempZ) {
	minPoint = Vector3(tempX, tempY, tempZ);
}

void AABB::SetMaxPoint(GLdouble tempX, GLdouble tempY, GLdouble tempZ) {
	maxPoint = Vector3(tempX, tempY, tempZ);
}

Vector3 AABB::GetMinPoint() {
	return minPoint;
}

Vector3 AABB::GetMaxPoint() {
	return maxPoint;
}

bool AABB::operator<(AABB &other) {
	return (maxPoint.GetPointX() > other.minPoint.GetPointX() &&
			minPoint.GetPointX() < other.maxPoint.GetPointX() &&
			maxPoint.GetPointY() > other.minPoint.GetPointY() &&
			minPoint.GetPointY() < other.maxPoint.GetPointY() &&
			maxPoint.GetPointZ() > other.minPoint.GetPointZ() &&
			minPoint.GetPointZ() < other.maxPoint.GetPointZ());
}

bool AABB::operator>(AABB &other) {
	return !operator<(other);
}
