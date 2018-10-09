#include "Dungeon.h"
#include "Game.h"
#include <random>
#include<iostream>




Dungeon::~Dungeon()
{
	for (int i = 0; i < gridWidth; i++)
	{
		delete [] grid[i];
	}

	delete[] grid;
}

void Dungeon::DrawFloor(Texture & tex)
{
	int i, j;

	float xx, zz;
	float yy = -1;
	std::vector<unsigned char> temp = tex.GetTexture();
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, tex.GetWidth(), tex.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, &temp[0]);

	for (i = 0; i < gridWidth; i++)
	{
		for (j = 0; j < gridHeight; j++)
		{
			//Get Centre Position
			xx = i * 4;
			zz = j * 4;

			glPushMatrix();
			glBegin(GL_QUADS);
			glTexCoord2f(-1.0, 1.0);
			glVertex3f(xx - 2, yy, zz - 2);
			glTexCoord2f(-1.0, 0.0);
			glVertex3f(xx - 2, yy, zz + 2);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(xx + 2, yy, zz + 2);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(xx + 2, yy, zz - 2);
			glEnd();
			glPopMatrix();

		}
	}
	glDisable(GL_TEXTURE_2D);
}

void Dungeon::DrawRoof(Texture & tex)
{
	int i, j;

	float xx, zz;
	float yy = 7;
	std::vector<unsigned char> temp = tex.GetTexture();
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, tex.GetWidth(),tex.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, &temp[0]);

	for (i = 0; i < gridWidth; i++)
	{
		for (j = 0; j < gridHeight; j++)
		{			
			//Get Centre Position
			xx = i * 4;
			zz = j * 4;

			glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(-1.0, 1.0);
				glVertex3f(xx-2, yy, zz-2);
				glTexCoord2f(-1.0, 0.0);
				glVertex3f(xx - 2, yy, zz + 2);
				glTexCoord2f(0.0, 0.0);
				glVertex3f(xx + 2, yy, zz + 2);
				glTexCoord2f(0.0, 1.0);
				glVertex3f(xx + 2, yy, zz - 2);
			glEnd();
			glPopMatrix();
			
		}
	}
	glDisable(GL_TEXTURE_2D);
}


Dungeon::Dungeon(Game* gameIn)
{
	owner = gameIn;
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(GO_LEFT, GO_DOWN); // guaranteed unbiased

	dir = uni(rng);

	
	nSteps = 400;
	
	gridWidth = 20;
	gridHeight = 20;

	xPos = gridWidth / 2;
	yPos = gridHeight / 2;


	grid = new int*[gridWidth];

	for (int i = 0; i < gridWidth; i++)
	{
		grid[i] = new int[gridHeight];
	}

	int xx, yy;

	for (xx = 0; xx < gridWidth; xx++)
	{
		for (yy = 0; yy < gridHeight; yy++)
		{
			grid[xx][yy] = 0;
		}
	}

	

	for (int i = 0; i < nSteps; i++)
	{
		grid[xPos][yPos] = 1;
		std::cout << "Tile Placed" << std::endl;
		prevDir = dir;
		dir = uni(rng);
		std::cout << "Movement Chosen" << std::endl;
		
		switch(dir)
		{
			case GO_LEFT:
				if (xPos > 1)
				{
					xPos--;
				}
				break;

			case GO_RIGHT:
				if (xPos < gridWidth - 2)
				{
					xPos++;
				}
				break;

			case GO_UP:
				if (yPos > 1)
				{
					yPos--;
				}
				break;

			case GO_DOWN:
				if (yPos < gridHeight - 2)
				{
					yPos++;
				}
				break;
		}
		std::cout << "Movement Taken" << std::endl;
		std::cout << "Step: " << i << std::endl;
	}
	owner->AddExit(xPos * 4, -1, yPos * 4);

	for (xx = 0; xx < gridWidth; xx++)
	{
		for (yy = 0; yy < gridHeight; yy++)
		{
			if (grid[xx][yy] == 0)
			{
				owner->AddWall(xx * 4, 0, yy * 4);
			}
			else
			{
				flags.emplace_back(Vector3(xx * 4, 0, yy * 4));
			}
		}
	}

	Vector3 startPos = Vector3((gridWidth / 2)*4, 0, (gridHeight / 2)*4);

	owner->GetPlayer()->SetPos(startPos);

	//Change to playing state
	owner->SetState(2);

}