#include <pch.h>

#include "Game.h"

Game::Game()
{
	playerCharacter = Player::GetInstance();
	
	shaysWorld = new Shay(this);
	menuScreens = new Menu(this);

	state = MENU_STATE;
	
	textures.resize(10);
	models.resize(10);

	exitScreen = false;
	menuScreen = true;
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
	menuScreens->Init();
	
	centreX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	centreY = glutGet(GLUT_WINDOW_HEIGHT) / 2;

	startTime = glutGet(GLUT_ELAPSED_TIME);

	playerCharacter->SetMoveSpeed(8);
	playerCharacter->SetRotateSpeed(5);

	textures[0].LoadTexture("data/Group.png", 768, 768);
	textures[1].LoadTexture("data/wall1.png", 64, 64);
	textures[2].LoadTexture("data/roof.png", 32, 32);
	textures[3].LoadTexture("data/floor.png", 32, 32);
	textures[4].LoadTexture("data/Statue.png", 1024, 1024);
	textures[5].LoadTexture("data/Menu.png", 768, 768);
	textures[6].LoadTexture("data/eyeball.png", 128, 128);

	models[0] = new Model("data/wall1.obj");
	models[1] = new Model("data/statue_base.obj");
	models[2] = new Model("data/eyeball.obj");

	std::vector <Actor> tempObjectVectorOne;
	std::vector <Actor> tempObjectVectorTwo;
	std::vector <Actor> tempObjectVectorThree;


	std::pair <int, std::vector <Actor>> enumActor;
	enumActor.first = tWALL;
	enumActor.second = tempObjectVectorOne;

	Entities.insert(enumActor);

	std::pair <int, std::vector <Actor>> enumActorTwo;
	enumActor.first = tEXIT;
	enumActor.second = tempObjectVectorTwo;

	Entities.insert(enumActorTwo);
	
	std::pair <int, std::vector <Actor>> enumActorThree;
	enumActor.first = tEnemy;
	enumActor.second = tempObjectVectorThree;

	Entities.insert(enumActorThree);
}

void Game::Update(float deltaTime)
{
	std::map<int, std::vector<Actor>> tempMap;

	bgmControl.PlaySong();
	
	switch (state)
	{
		case GAME_STATE:

			if (Entities[tEXIT][0].GetCollider().AABBtoAABB(playerCharacter->GetCollider()))
			{
				ClearLevel();
			}
			
			for (int i = 0; i < Entities[tEnemy].size(); i++) {
				Entities[tEnemy][i].Update(deltaTime);
			}

			for (std::map <int, std::vector<Actor>>::iterator object = Entities.begin(); object != Entities.end(); ++object)
			{
				std::vector <Actor> resultObjectList;
				std::pair <int, std::vector <Actor>> enumActor;


				for (std::vector<Actor>::iterator col = object->second.begin(); col != object->second.end(); col++)
				{
					Vector3 temp = col->GetPos();
					
					if (ProximityCull(playerCharacter->GetPos(), temp))
					{
						resultObjectList.push_back(*col);
					}
				}

				enumActor.first = object->first;
				enumActor.second = resultObjectList;
				tempMap.insert(enumActor);
			}

			playerCharacter->Update(deltaTime, tempMap);

			

			/*for (std::map <int, std::vector<Actor>>::iterator object = Entities.begin(); object != Entities.end(); ++object)
			{
				for (std::vector<Actor>::iterator col = object->second.begin(); col != object->second.end(); col++)
				{
					col->Update(deltaTime);
				}
			}*/
			
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
			if (menuScreens != NULL)
			{
				menuScreens->Draw(textures[5]);
			}
			break;

		case SHAY_STATE:
			if (shaysWorld != NULL)
			{
				shaysWorld->SetWidthHeight(800, 500);
				glEnable(GL_DEPTH_TEST);
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();

				gluPerspective(60.0, 1, 1.0, 30.0);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				shaysWorld->Draw();
			}
			break;

		case GAME_STATE:
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			playerCharacter->Draw();

			glPushMatrix();
			for (int ii = 0; ii < Entities[tWALL].size(); ii++)
			{
				Entities[tWALL][ii].Draw();
			}

			for (int ii = 0; ii < Entities[tEXIT].size(); ii++)
			{
				Entities[tEXIT][ii].Draw();
			}
			glPopMatrix();

			dungeon->DrawRoof(textures[2]);
			dungeon->DrawFloor(textures[3]);

			for (int i = 0; i < Entities[tEnemy].size(); i++) 
			{
				Entities[tEnemy][i].Draw();
			}

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
	case 'p':
	case 'P':
		menuScreen = !menuScreen;
		if (!menuScreen)
			SetState(MENU_STATE);
		else
			SetState(GAME_STATE);
		break;
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
	int deadzone = PI * 0.15915494309;

	//If the mouse pointer has moved far enough, rotate camera
	if ((abs((long double)x) > deadzone) || (abs((long double)y) > deadzone)) {
		int deltaX = ((centreX - x) < 0) - (0 < (centreX - x));
		int deltaY = -(((centreY - y) < 0) - (0 < (centreY - y)));

		playerCharacter->DirectionLookLR(deltaX);
		playerCharacter->DirectionLookUD(deltaY);
	}
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

Menu * Game::GetMenu() const
{
	return menuScreens;
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
	Entities[tWALL].push_back(Wall(x, y, z, models[0], &textures[1]));
}

void Game::AddExit(float x, float y, float z)
{
	Entities[tEXIT].push_back(LevelExit(x, y, z, models[0], &textures[4]));
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
	Entities[tWALL].clear();
	Entities[tEXIT].clear();
	delete dungeon;
	dungeon = NULL;
	state = LOAD_STATE;
}

void Game::AddEnemy(float x, float y, float z, std::vector<Vector3> &f)
{
	Enemy temp(models[2], &textures[6], x, y, z, f);

	Entities[tEnemy].push_back(temp);
}