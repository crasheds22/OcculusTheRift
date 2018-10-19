#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <vector>
#include <string>
#include "lodepng.h"
#include <soil/SOIL.h>
#include <gl/glut.h>

/**
 *	@class Texture
 *	@brief Loads a texture
 *	
 *	@author Liam Kinsella
 *	@version 1.0
 *	@date 15-08-2018
 */
class Texture {
public:

	virtual~Texture();

	/**
	 *	Returns the address of the texture in raw form
	 *	@return The texture as a byte array address
	 */
	std::vector<unsigned char>& GetTexture();

	/**
	 *	Returns the address of the texture in raw form
	 *	@return The texture as a byte array address
	 */
	std::vector<GLuint>& GetTextureSOIL();

	/**
	 *	A normal member taking 3 arguments
	 *	Takes a path to a file, the width and height and loads a texture file
	 *	@param filePath The path to the file to load
	 *	@param w The width of the texture
	 *	@param h The height of the texture
	 */
	void LoadTexture(std::string filePath, unsigned int w, unsigned int h);

	/**
	 *	A normal member taking 3 arguments
	 *	Takes a path to a file, the width and height and loads a texture file
	 *	@param filePath The path to the file to load
	 *	@param w The width of the texture
	 *	@param h The height of the texture
	 */
	void LoadTextureSOIL(const char * filePath, unsigned int w, unsigned int h);


	/**
	 *	A normal member returning an unsigned
	 *	@return The width of the texture
	 */
	unsigned int GetWidth();

	/**
	 *	A normal member returning an unsigned
	 *	@return The height of the texture
	 */
	unsigned int GetHeight();

private:
	unsigned int texW,	/*<! The texture width */
				 texH;	/*<! The texture height */

	std::vector<unsigned char> data; /*<! The texture data array */
	std::vector<GLuint> dataSOIL; /*<! The texture data array */
};

#endif
