#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <gl/glut.h>

/**
 *	@class Model
 *	@brief Loads a .obj file
 *
 *	@author Liam Kinsella
 *	@version 1.0
 *	@date 15-08-2018
 *
 *	@author Aaron Thomson
 *	@version 1.1 Changes strtok (depricated) to strtok_s 
 *	@date 06-09-2018
 */
class Model {
public:
	/**
	 *	Constructor
	 *	Loads .obj from specified file path, counts number of points and stores in 2D arrays
	 *	@param filePath The path to the .obj file
	 */
	Model(std::string filePath);

	/**
	 *	Destructor
	 */
	~Model();

	/**
	 *	A normal member taking 6 arguments
	 *	Draws the loaded model to the screen via OpenGL calls
	 *	@param xOff x position of the Actor drawing the model
	 *	@param yOff y position of the Actor drawing the model
	 *	@param zOff z position of the Actor drawing the model
	 *	@param temp Address of texture to be drawn over model
	 *	@param w Width of texture to be drawn
	 *	@param h Height of texture to be drawn
	 */
	void DrawModel(float xOff, float yOff, float zOff, std::vector<unsigned char> & temp, unsigned int w, unsigned int h);

private:
	int i;

	int nPositions;		/*<! Number of positions in .obj */
	float** positions;	/*<! 2D array of positions */

	int nTexels;		/*<! Number of texels in .obj */
	float** texels;		/*<! 2D array of texels */

	int nNormals;		/*<! Number of normals in .obj */
	float** normals;	/*<! 2D array of normals */

	int nFaces;			/*<! Number of faces in .obj */
	int** faces;		/*<! 2D array of faces */


	/**
	 *	A normal member taking one argument
	 *	Places information about .obj file into specific 2D arrays
	 *	@param filePath The path to the obj file
	 */
	void ExtractObjData(std::string filePath);
	
	/**
	 *	A normal member taking one argument
	 *	Counts the specific number of each data type the .obj file has
	 *	@param filePath The path to the obj file
	 */
	void CountPoints(std::string filePath);
};

#endif
