#ifndef Dungeon_H
#define Dungeon_H
class Game;

#include "gl/glut.h"
#include "Texture.h"
#include "Vector3.h"
#include <vector>

#define GO_LEFT 0
#define GO_RIGHT 1
#define GO_UP 2
#define GO_DOWN 3

class Dungeon
{
protected:
	int** grid;

	int dir;
	int prevDir;

	int gridWidth;

	int gridHeight;

	int nSteps;

	int xPos;
	int yPos;

	Game* owner;

	std::vector<Vector3> flags;

public:
	Dungeon(Game* gameIn);

	~Dungeon();

	void DrawFloor(Texture & tex);

	void DrawRoof(Texture & tex);

};
#endif