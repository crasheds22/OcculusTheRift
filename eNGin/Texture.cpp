#include <pch.h>
#include <stdio.h>
#include "Texture.h"



Texture::~Texture()
{
	
}

std::vector<unsigned char>& Texture::GetTexture() {
	return data;
}


void Texture::LoadTexture(std::string filePath, unsigned int w, unsigned int h) {
	texW = w;
	texH = h;

	unsigned error = lodepng::decode(data, texW, texH, filePath);

	if (error != 0) {
		std::cout << "Error " << error << ": " << lodepng_error_text(error) << std::endl;
		exit(1);
	}
}

unsigned int Texture::GetHeight() {
	return texH;
}

unsigned int Texture::GetWidth() {
	return texW;
}
