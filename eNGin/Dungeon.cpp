#include <pch.h>
#include "Dungeon.h"
#include "Game.h"
#include <random>

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
			if (grid[i][j] == 1)
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
			if (grid[i][j] == 1)
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
	}
	glDisable(GL_TEXTURE_2D);
}

Dungeon::Dungeon(Game* gameIn)
{
	owner = gameIn;
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(GO_LEFT, GO_DOWN); // guaranteed unbiased

	int ex, ez;

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
		prevDir = dir;
		dir = uni(rng);
		
		if (i == nSteps - 2) {
			ex = xPos;
			ez = yPos;
		}

		switch(dir)
		{
			case GO_LEFT:
				if (xPos > 2)
				{
					xPos--;
				}
				break;

			case GO_RIGHT:
				if (xPos < gridWidth - 3)
				{
					xPos++;
				}
				break;

			case GO_UP:
				if (yPos > 2)
				{
					yPos--;
				}
				break;

			case GO_DOWN:
				if (yPos < gridHeight - 3)
				{
					yPos++;
				}
				break;
		}
	}

	owner->AddExit(ex * 4, -1, ez * 4);

	for (xx = 1; xx < gridWidth-1; xx++)
	{
		for (yy = 1; yy < gridHeight-1; yy++)
		{
			if ((grid[xx][yy] == 0) && ((grid[xx-1][yy] == 1) || (grid[xx + 1][yy] == 1) || (grid[xx][yy+1] == 1) || (grid[xx][yy - 1] == 1)))
			{
				owner->AddWall(xx * 4, 0, yy * 4);
			}
			else
			{
				if (xx % 4 == 0)
				{
					owner->AddCoin(xx * 4, 0, yy * 4);
				}
			}
		}
	}

	owner->AddEnemy(ex * 4, 2, ez * 4);

	Vector3 startPos = Vector3((gridWidth / 2)*4, 0, (gridHeight / 2)*4);

	owner->GetPlayer()->SetPos(startPos);

	//Change to playing state
	owner->SetState(2);

}
