#include <pch.h>
#include "Texture.h"


void Texture::LoadTexture(std::string filePath, unsigned w, unsigned h)
{
	texW = w;
	texH = h;

	unsigned error = lodepng::decode(data, texW, texH, filePath);

	if (error != 0)
	{
		std::cout << "error " << error << ": " << lodepng_error_text(error) << std::endl;
		exit(1);
	}
}

std::vector<unsigned char> & Texture::GetTexture()
{
	return data;
}


unsigned Texture::GetHeight()
{
	return texH;
}

unsigned Texture::GetWidth()
{
	return texW;
}