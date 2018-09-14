#include <pch.h>
#include "Model_Shay.h"
#include <iostream>


ModelShay::ModelShay(string filePath)
{
	//Set data counts to 0;
	nPositions = 0;
	nTexels = 0;
	nNormals = 0;
	nFaces = 0;

	//Get Numbers for arrays
	CountPoints(filePath);

	//==============================
	// Initialise Arrays
	//==============================

	//Init positions 2d array
	positions = new float*[nPositions];

	for (int i = 0; i < nPositions; i++)
	{
		positions[i] = new float[3];
	}

	//Init texels array
	texels = new float*[nTexels];

	for (int i = 0; i < nTexels; i++)
	{
		texels[i] = new float[2];
	}

	//Init Normals array
	normals = new float*[nNormals];

	for (int i = 0; i < nNormals; i++)
	{
		normals[i] = new float[3];
	}

	//Init Faces array
	faces = new int*[nFaces];

	for (int i = 0; i < nFaces; i++)
	{
		faces[i] = new int[9];
	}
	//=============================
	//
	//=============================

	//Fill arrays with data
	ExtractObjData(filePath);

}

ModelShay::~ModelShay()
{
	for (int i = 0; i < nPositions; i++)
	{
		delete[] positions[i];
	}

	delete[] positions;

	for (int i = 0; i < nTexels; i++)
	{
		delete[] texels[i];
	}

	delete[] texels;

	for (int i = 0; i < nNormals; i++)
	{
		delete[] normals[i];
	}

	delete[] normals;

	for (int i = 0; i < nFaces; i++)
	{
		delete[] faces[i];
	}

	delete[] faces;
}

void ModelShay::CountPoints(string filePath)
{
	ifstream inObj;

	inObj.open(filePath);

	if (!inObj.good())
	{
		cout << "ERROR, Cannot open: " << filePath << endl;
		exit(1);
	}

	while (!inObj.eof())
	{
		string line;
		getline(inObj, line);
		string type = line.substr(0, 2);

		if (type.compare("v ") == 0)
		{
			nPositions++;
		}
		else
		{
			if (type.compare("vt") == 0)
			{
				nTexels++;
			}
			else
			{
				if (type.compare("vn") == 0)
				{
					nNormals++;
				}
				else
				{
					if (type.compare("f ") == 0)
					{
						nFaces++;
					}
				}
			}
		}

	}


	inObj.close();
}

void ModelShay::ExtractObjData(std::string filePath) 
{
	int p = 0,
		t = 0,
		n = 0,
		f = 0;
	int i;
	std::string line, type;
	char *context = NULL;

	std::ifstream inObj;
	inObj.open(filePath);

	if (!inObj.good()) {
		std::cout << "Cannot open obj file: " << filePath << std::endl;
		exit(1);
	}

	while (!inObj.eof()) {
		getline(inObj, line);
		type = line.substr(0, 2);

		//Positions
		if (type.compare("v ") == 0) {
			//Copy line for parsing
			char* l = new char[line.size() + 1];
			memcpy(l, line.c_str(), line.size() + 1);

			//Extract tokens
			//strtok(l, " "); <=== Depricated
			strtok_s(l, " ", &context);
			for (i = 0; i < 3; i++)
				positions[p][i] = atof(strtok_s(NULL, " ", &context));

			//Wrap up
			delete[] l;
			p++;
		}

		//Texels
		else if (type.compare("vt") == 0) {
			//Copy line for parsing
			char* l = new char[line.size() + 1];
			memcpy(l, line.c_str(), line.size() + 1);

			//Extract tokens
			//strtok(l, " ");
			strtok_s(l, " ", &context);
			for (i = 0; i < 2; i++)
				texels[t][i] = atof(strtok_s(NULL, " ", &context));

			//Wrap up
			delete l;
			t++;
		}

		//Normals
		else if (type.compare("vn") == 0) {
			//Copy line for parsing
			char* l = new char[line.size() + 1];
			memcpy(l, line.c_str(), line.size() + 1);

			//Extract tokens
			//strtok(l, " ");
			strtok_s(l, " ", &context);
			for (int i = 0; i < 3; i++)
				normals[n][i] = atof(strtok_s(NULL, " ", &context));

			delete[] l;
			n++;
		}

		//face
		else if (type.compare("f ") == 0) {
			//Copy line for parsing
			char* l = new char[line.size() + 1];
			memcpy(l, line.c_str(), line.size() + 1);

			//Extract tokens
			//strtok(l, " ");
			strtok_s(l, " ", &context);
			for (i = 0; i < 9; i++)
				faces[f][i] = atof(strtok_s(NULL, " /", &context));

			delete[] l;
			f++;
		}
	}

	inObj.close();
}

void ModelShay::TestData()
{
	cout << texels[faces[0][1]][0] << endl;
}

void ModelShay::DrawModel(float xOff, float yOff, float zOff, GLuint tex)
{
	// Enable the texture for OpenGL.
	//glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, &temp[0]);
	//glBindTexture(GL_TEXTURE_2D, tex);

	//Loop through the faces and draw vertices, map texture and create normals
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < nFaces; i++)
	{
		float nX = normals[faces[i][8] - 1][0];
		float nY = normals[faces[i][8] - 1][1];
		float nZ = normals[faces[i][8] - 1][2];

		float x = positions[faces[i][6] - 1][0];
		float y = positions[faces[i][6] - 1][1];
		float z = positions[faces[i][6] - 1][2];

		float tX = texels[faces[i][7] - 1][0];
		float tY = texels[faces[i][7] - 1][1];

		glNormal3f(nX, nY, nZ);
		glTexCoord2f(tX, -tY);
		glVertex3f(x + xOff, y + yOff, z + zOff);


		nX = normals[faces[i][5] - 1][0];
		nY = normals[faces[i][5] - 1][1];
		nZ = normals[faces[i][5] - 1][2];
		x = positions[faces[i][3] - 1][0];
		y = positions[faces[i][3] - 1][1];
		z = positions[faces[i][3] - 1][2];
		tX = texels[faces[i][4] - 1][0];
		tY = texels[faces[i][4] - 1][1];

		glNormal3f(nX, nY, nZ);
		glTexCoord2f(tX, -tY);
		glVertex3f(x + xOff, y + yOff, z + zOff);


		nX = normals[faces[i][2] - 1][0];
		nY = normals[faces[i][2] - 1][1];
		nZ = normals[faces[i][2] - 1][2];
		x = positions[faces[i][0] - 1][0];
		y = positions[faces[i][0] - 1][1];
		z = positions[faces[i][0] - 1][2];
		tX = texels[faces[i][1] - 1][0];
		tY = texels[faces[i][1] - 1][1];

		glNormal3f(nX, nY, nZ);
		glTexCoord2f(tX, -tY);
		glVertex3f(x + xOff, y + yOff, z + zOff);
	}
	glEnd();
}