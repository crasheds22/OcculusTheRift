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
	int** grid; /*<! 2D Array holding the values of wall/floor tiles>*/

	int dir; /*<! Direction dungeon builder is moving in this step*/
	int prevDir; /*<! 2D Array holding the values of wall/floor tiles>*/

	int gridWidth; /*<! The width of the dungeon grid>*/

	int gridHeight; /*<! The height of the dungeon grid>*/

	int nSteps; /*<! The number of steps the dungeon builder takes>*/

	int xPos; /*<! the x position of the current step in the dungeon build>*/
	int yPos; /*<! the y position of the current step in the dungeon build>*/

	Game* owner; /*<! the Game object that the dungeon is contained in>*/

	std::vector<Vector3> flags; /*<! A vector of in game positions used by Enemy AI>*/

public:
	/**
	*	Default constructor
	*	Builds the dungeon and places objects inside the scene
	*/
	Dungeon(Game* gameIn);

	/**
	*	Default destructor
	*	Deletes the dungeon from memory
	*/
	~Dungeon();

	/**
	*	A normal member taking 1 argument
	*	Called by game to play draw the floor of the dungeon
	*	@param tex the texture used to draw the floor
	*/
	void DrawFloor(Texture & tex);

	/**
	*	A normal member taking 1 argument
	*	Called by game to play draw the roof of the dungeon
	*	@param tex the texture used to draw the roof
	*/
	void DrawRoof(Texture & tex);

};
#endif