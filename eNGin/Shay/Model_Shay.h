#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <gl/glut.h>
#include <vector>

using namespace std;

/** @class Model
*	@brief Loads a .obj file and draws it to screen
*
*	@author Liam Kinsella
*	@date: 15/08/2018
*/

class ModelShay
{
private:
	int nPositions; //*!< Number of positions in .obj*/
	float** positions; //*!< 2D array of positions*/

	int nTexels; //*!< Number of texels in .obj*/
	float** texels; //*!< 2D array of texels*/

	int nNormals; //*!< Number of normals in .obj*/
	float** normals;//*!< 2D array of normals*/

	int nFaces; //*!< Number of faces in .obj*/
	int** faces;//*!< 2D array of faces*/

	/**
	* Places information about .obj file into specific 2d arrays
	*
	**/
	void ExtractObjData(string filePath);

	/**
	* Counts the specific number of each data type the obj file has
	*
	**/
	void CountPoints(string filePath);


public:
	/**
	* Loads .obj from specific file path, counts number of points and stores data in 2d arrays
	* @param filePath file path of .obj to be loaded
	**/
	ModelShay(string filePath);

	/**
	* Deletes dynamically sized 2d arrays at destruction of model
	*
	*/
	~ModelShay();

	/**
	* Draws model to screen via OpenGL calls
	*
	*@param xOff xPosition of Actor drawing model
	*@param yOff yPosition of Actor drawing model
	*@param zOff zPosition of Actor drawing model
	*@param temp Address of texture to be drawn over model
	*@param w width of texture to be drawn
	*@param h height of texture to be drawn
	*/
	void DrawModel(float xOff, float yOff, float zOff, GLuint tex);


	/**
	*Function used to unit test 2d arrays
	*/
	void TestData();

};


