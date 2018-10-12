#include <pch.h>

#include "Game.h"

Game::Game()
{
	playerCharacter = Player::GetInstance();
	
	shaysWorld = new Shay(this);
	state = SHAY_STATE;
	textures.resize(10);
	models.resize(10);

	exitScreen = false;
}

Game::~Game()
{
	if (shaysWorld != NULL)
	{
		delete shaysWorld;
	}
	delete models[0];

	if (dungeon != NULL)
	{
		delete dungeon;
	}
}

void Game::Run() 
{
	
	endTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (endTime - startTime)/1000;
	Draw();
	Update(deltaTime);

	startTime = endTime;
}

void Game::Initialise() 
{
	shaysWorld->Init();
	
	centreX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	centreY = glutGet(GLUT_WINDOW_HEIGHT) / 2;

	startTime = glutGet(GLUT_ELAPSED_TIME);

	playerCharacter->SetMoveSpeed(8);
	playerCharacter->SetRotateSpeed(1);
	/*
	Quarternion tempQuart;
	tempQuart.SetQuartW(0);
	tempQuart.SetQuartX(playerCharacter->GetPos().GetPointX());
	tempQuart.SetQuartY(playerCharacter->GetPos().GetPointY());
	tempQuart.SetQuartZ(playerCharacter->GetPos().GetPointZ());
	playerCharacter->SetCameraViewDelta(tempQuart);
	*/
	textures[0].LoadTexture("data/Group.png", 768, 768);
	textures[1].LoadTexture("data/wall1.png", 64, 64);
	textures[2].LoadTexture("data/roof.png", 32, 32);
	textures[3].LoadTexture("data/floor.png", 32, 32);

	models[0] = new Model("data/wall1.obj");

	std::vector <Actor> tempObjectVectorOne;

	std::pair <Tag, std::vector <Actor>> enumActor;
	enumActor.first = Tag::WALL;
	enumActor.second = tempObjectVectorOne;

	Entities.insert(enumActor);
}

void Game::Update(float deltaTime)
{
	std::vector <Actor> resultObjectList;

	bgmControl.PlaySong();
	
	switch (state)
	{
		case GAME_STATE:			
			for (std::map <Tag, std::vector<Actor>>::iterator object = Entities.begin(); object != Entities.end(); ++object)
			{
				for (std::vector<Actor>::iterator col = object->second.begin(); col != object->second.end(); col++)
				{
					Vector3 temp = col->GetPos();
					
					if (ProximityCull(playerCharacter->GetPos(), temp))
					{
						std::cout << "Object added" << std::endl;
						resultObjectList.push_back(*col);
					}
				}
			}

			playerCharacter->Update(deltaTime, resultObjectList);

			for (std::map <Tag, std::vector<Actor>>::iterator object = Entities.begin(); object != Entities.end(); ++object)
			{
				for (std::vector<Actor>::iterator col = object->second.begin(); col != object->second.end(); col++)
				{
					col->Update(deltaTime);
				}
			}
			
			break;

		case MENU_STATE:
			break;

		case LOAD_STATE:
			if (dungeon == NULL)
			{
				dungeon = new Dungeon(this);
			}
			break;
	}
}

void Game::Draw()
{
	switch (state)
	{
		case MENU_STATE:
			break;

		case SHAY_STATE:
			if (shaysWorld != NULL)
			{
				shaysWorld->Draw();
			}
			break;

		case GAME_STATE:
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			playerCharacter->Draw();

			glPushMatrix();
			for (int ii = 0; ii < Entities[Tag::WALL].size(); ii++)
			{
				Entities[Tag::WALL][ii].Draw();
			}
			glPopMatrix();

			dungeon->DrawRoof(textures[2]);
			dungeon->DrawFloor(textures[3]);

			glPushMatrix();
				if (exitScreen)
					DrawGUI();
			glPopMatrix();

			glFlush();
			
			break;

		case LOAD_STATE:
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0, 0, 0, 1);
			glFlush();
			break;
	}
}

void Game::InputDown(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a':
	case 'A':
		playerCharacter->DirectionL(1);
		break;
	case 's':
	case 'S':
		playerCharacter->DirectionB(1);
		break;
	case 'd':
	case 'D':
		playerCharacter->DirectionR(1);
		break;
	case 'w':
	case 'W':
		playerCharacter->DirectionF(1);
		break;
	case 't':
	case 'T':
		if (state == GAME_STATE)
		{
			ClearLevel();
		}
		//exitScreen = !exitScreen;
		break;
	case'z':
		Vector3 yawAxis;
		Vector3 pitchAxis;
		GLdouble radian;
		
		radian = 90 * (PI / 180);
		yawAxis = Vector3(0, 1, 0);
		pitchAxis = Vector3(1, 0, -1);

		playerCharacter->RotateCamera(radian, yawAxis, playerCharacter->GetCameraViewDelta(), deltaTime);
		//playerCharacter->RotateCamera(radian, pitchAxis, playerCharacter->GetCameraViewDelta(), deltaTime);
	}
}

void Game::InputUp(unsigned char key, int x, int y) 
{
	switch (key) {
	case 'a':
	case 'A':
		playerCharacter->DirectionL(0);
		break;
	case 'd':
	case 'D':
		playerCharacter->DirectionR(0);
		break;
	case 'w':
	case 'W':
		playerCharacter->DirectionF(0);
		break;
	case 's':
	case 'S':
		playerCharacter->DirectionB(0);
		break;
	}
}

void Game::MouseLook(int x, int y)
{
	int deadzone = 1;
	Vector3 pitchAxis;
	GLdouble currentRotation;
	GLdouble mouseSensitivity = 10;

	
	//If the mouse pointer has moved far enough, rotate camera
	if ((abs((long double)x) > deadzone) || (abs((long double)y) > deadzone)) 
	{	
		//std::cout << "Delta Time: " << deltaTime << std::endl;
		int deltaX = ((centreX - x) < 0) - (0 < (centreX - x));
		int deltaY = -(((centreY - y) < 0) - (0 < (centreY - y)));

		//int deltaX = (centreX - x);
		//int deltaY = (centreY - y);

		if (deltaX > 1)
		{
			deltaX = 1;
		}

		if (deltaX < -1)
		{
			deltaX = -1;
		}

		if (deltaY > 1)
		{
			deltaY = 1;
		}

		if (deltaY < -1)
		{
			deltaY = -1;
		}

		double radianX = deltaX * (PI / 180);
		double radianY = deltaY * (PI / 180);

		//std::cout << "Delta X " << deltaX << std::endl;
		//std::cout << "Delta Y " << deltaY << std::endl;
		//std::cout << "Radian X " << radianX << std::endl;
		//std::cout << "Radian Y " << radianY << std::endl;

		if (radianX != 0 || radianY != 0)
		{
			pitchAxis = playerCharacter->GetCameraViewDeltaVector().CrossProduct(playerCharacter->GetCameraUp());
			pitchAxis = pitchAxis.UnitVector();
			// pitch
			playerCharacter->RotateCamera(radianY, pitchAxis, playerCharacter->GetCameraViewDelta(), deltaTime);
			// yaw
			playerCharacter->RotateCamera(radianX, Vector3(0, 1, 0), playerCharacter->GetCameraViewDelta(), deltaTime);
		}
		

		glutWarpPointer(centreX, centreY);
		//playerCharacter->DirectionLookLR(deltaX);
		//playerCharacter->DirectionLookUD(deltaY);
	}
	/*
	glutWarpPointer(centreX, centreY);
	
	int deltaX = (centreX - x);
	int deltaY = (centreY - y);
	/*
	if (deltaX > 1)
	{
		deltaX = 1;
	}

	if (deltaX > -1)
	{
		deltaX = -1;
	}

	if (deltaY > 1)
	{
		deltaY = 1;
	}

	if (deltaY > -1)
	{
		deltaY = -1;
	}
	

	double radianX = deltaX * (PI / 180);
	double radianY = deltaY * (PI / 180);

	std::cout << "Delta X " << deltaX << std::endl;
	std::cout << "Delta Y " << deltaY << std::endl;
	std::cout << "Radian X " << radianX << std::endl;
	std::cout << "Radian Y " << radianY << std::endl;

	if (radianX != 0 || radianY != 0)
	{
		//pitchAxis = playerCharacter->GetCameraViewLR().CrossProduct(playerCharacter->GetCameraViewUD());
		// pitch
		playerCharacter->RotateCamera(radianY, Vector3(1, 0, 0), playerCharacter->GetCameraViewDelta(), deltaTime);
		// yaw
		playerCharacter->RotateCamera(radianX, Vector3(0, 1, 0), playerCharacter->GetCameraViewDelta(),deltaTime);
	}
	*/
}

void Game::MouseClick(int button, int state, int x, int y) {
	if (exitScreen && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		exit(0);
	}
}

Shay * Game::GetShaysWorld() const
{
	return shaysWorld;
}

int Game::GetState() const
{
	return state;
}

void Game::SetState(int stateIn)
{
	state = stateIn;
}

void Game::SwitchState()
{
	if (state == SHAY_STATE)
	{
		state = LOAD_STATE;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0, 0, 1);
		glFlush();
		delete shaysWorld;
		shaysWorld = NULL;
		// temporary the need to work in silence
		//bgmControl.SetSong(1);
	}
}

void Game::DrawGUI()
{
	//Set View mode to orthographic
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-8.0, 8.0, -5.0, 5.0, 1.0, 30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Assign Texture
	std::vector<unsigned char> temp = textures[0].GetTexture();
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textures[0].GetWidth(), textures[0].GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, &temp[0]);

	//Draw Healthbar
	glPushMatrix();
	glBegin(GL_QUADS);
		glTexCoord2f(-1.0, 1.0);
		glVertex3f(-4, -4, -1);
		glTexCoord2f(-1.0, 0.0);
		glVertex3f(-4, 4, -1);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(4, 4, -1);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(4, -4, -1);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, 1, 1.0, 30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Game::SetCentreX(int x) {
	centreX = x;
}

void Game::SetCentreY(int y) {
	centreY = y;
}

int Game::GetCentreX()
{
	return centreX;
}

int Game::GetCentreY()
{
	return centreY;
}

void Game::AddWall(float x, float y, float z)
{
	
	Entities[Tag::WALL].push_back(Wall(x, y, z, models[0], &textures[1]));
	wallCount++;
}

Player * Game::GetPlayer() const
{
	return playerCharacter;
}


bool Game::ProximityCull(Vector3 actorPosition, Vector3 &inputObject)
{
	Vector3 positionOffset;
	Vector3 minCullBox;
	Vector3 maxCullBox;

	positionOffset = Vector3(4.0, 10.0, 4.0);
	minCullBox = actorPosition.SubtractVector(positionOffset);
	maxCullBox = actorPosition.AddVector(positionOffset);

	return (maxCullBox.GetPointX() > inputObject.GetPointX() &&
		minCullBox.GetPointX() < inputObject.GetPointX() &&
		maxCullBox.GetPointY() > inputObject.GetPointY() &&
		minCullBox.GetPointY() < inputObject.GetPointY() &&
		maxCullBox.GetPointZ() > inputObject.GetPointZ() &&
		minCullBox.GetPointZ() < inputObject.GetPointZ());

}

void Game::ClearLevel()
{
	Entities[Tag::WALL].clear();
	delete dungeon;
	dungeon = NULL;
	state = LOAD_STATE;
}