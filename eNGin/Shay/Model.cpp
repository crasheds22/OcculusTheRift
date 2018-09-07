#include "Model.h"
#include <iostream>


Model::Model(string filePath)
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

Model::~Model()
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

void Model::CountPoints(string filePath)
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

void Model::ExtractObjData(string filePath)
{
	int p = 0;
	int t = 0;
	int n = 0;
	int f = 0;

	//Open Obj file
	ifstream inObj;
	inObj.open(filePath);

	if (!inObj.good())
	{
		cout << "Cannot open obj file: " << filePath << endl;
		exit(1);
	}

	//Read obj file
	while (!inObj.eof())
	{
		string line;
		getline(inObj, line);
		string type = line.substr(0, 2);

		//Positions
		if (type.compare("v ") == 0)
		{
			//Copy line for parsing
			char* l = new char[line.size() + 1];
			memcpy(l, line.c_str(), line.size() + 1);

			//Extract tokens
			strtok(l, " ");
			for (int i = 0; i < 3; i++)
			{
				positions[p][i] = atof(strtok(NULL, " "));
			}

			//Wrap up
			delete[] l;
			p++;
		}

		//Texels
		else if (type.compare("vt") == 0)
		{
			//Copy line for parsing
			char* l = new char[line.size() + 1];
			memcpy(l, line.c_str(), line.size() + 1);

			//Extract tokens
			strtok(l, " ");
			for (int i = 0; i < 2; i++)
			{
				texels[t][i] = atof(strtok(NULL, " "));
			}

			//Wrap up
			delete[] l;
			t++;
		}

		//Normals
		else if (type.compare("vn") == 0)
		{
			char* l = new char[line.size() + 1];
			memcpy(l, line.c_str(), line.size() + 1);

			strtok(l, " ");
			for (int i = 0; i < 3; i++)
			{
				normals[n][i] = atof(strtok(NULL, " "));
			}

			delete[] l;
			n++;
		}

		//Face
		else if (type.compare("f ") == 0)
		{
			char* l = new char[line.size() + 1];
			memcpy(l, line.c_str(), line.size() + 1);

			strtok(l, " ");
			for (int i = 0; i<9; i++)
			{
				faces[f][i] = atof(strtok(NULL, " /"));
			}
			/*faces[f][0] = atof(strtok(NULL, " //"));
			faces[f][2] = atof(strtok(NULL, " //"));
			faces[f][3] = atof(strtok(NULL, " //"));
			faces[f][5] = atof(strtok(NULL, " //"));
			faces[f][6] = atof(strtok(NULL, " //"));
			faces[f][8] = atof(strtok(NULL, " //"));*/

			delete[] l;
			f++;
		}
	}

	inObj.close();
}

void Model::TestData()
{
	cout << texels[faces[0][1]][0] << endl;
}

void Model::DrawModel(float xOff, float yOff, float zOff, GLuint tex)
{
	// Enable the texture for OpenGL.
	//glEnable(GL_TEXTURE_2D);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
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