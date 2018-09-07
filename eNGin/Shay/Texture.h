#pragma once
#include<iostream>
#include<string>
#include<vector>
#include "lodepng.h"


class Texture
{
public:
	/**
	*	Returns the address of array of bytes, the texture in raw form
	*	@return texture as byte array address
	*/
	std::vector<unsigned char> & GetTexture();

	/**
	*	Returns the position of the Actor
	*	@param filePath the file path to the texture
	*	@param w width of texture
	*	@param h height of texture
	*/
	void LoadTexture(std::string filePath, unsigned w, unsigned h);

	/**
	*	Returns the width of the texture
	*	@return width of texture
	*/
	unsigned GetWidth();

	/**
	*	Returns the height of the texture
	*	@return height of texture
	*/
	unsigned GetHeight();

private:
	unsigned texW;/*<! Texture width*/
	unsigned texH;/*<! Texture height*/
	std::vector<unsigned char> data; /*<! Texture as array of bytes*/
};


