#include <pch.h>

#include "Game.h"
#include <random>

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

	Game::Draw();
	
	Game::Update(deltaTime);

	startTime = endTime;
}

void Game::Initialise() 
{
	count = 0;
	shaysWorld->Init();
	menuScreens->Init();
	
	centreX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	centreY = glutGet(GLUT_WINDOW_HEIGHT) / 2;

	startTime = glutGet(GLUT_ELAPSED_TIME);

	
	playerCharacter->SetMoveSpeed(8);
	playerCharacter->SetRotateSpeed(1);
	
	textures[0].LoadTexture("data/Group.png", 768, 768);
	textures[1].LoadTexture("data/wall2.png", 64, 64);
	textures[2].LoadTexture("data/roof.png", 32, 32);
	textures[3].LoadTexture("data/floor2.png", 32, 32);
	textures[4].LoadTexture("data/Statue.png", 1024, 1024);
	textures[5].LoadTexture("data/Menu.png", 768, 768);
	textures[6].LoadTexture("data/eyeball.png", 128, 128);
	textures[7].LoadTexture("data/wall2_vines.png", 64, 64);
	textures[8].LoadTexture("data/exit.png", 128, 128);

	models[0] = new Model("data/wall1.obj");
	models[1] = new Model("data/statue_base.obj");
	models[2] = new Model("data/eyeball.obj");
	models[3] = new Model("data/exit.obj");

	std::vector <Actor*> tempObjectVectorOne;
	std::vector <Actor*> tempObjectVectorTwo;
	std::vector <Actor*> tempObjectVectorThree;

	std::pair <int, std::vector <Actor*>> enumActor;
	enumActor.first = tWALL;
	enumActor.second = tempObjectVectorOne;

	Entities.insert(enumActor);

	std::pair <int, std::vector <Actor*>> enumActorTwo;
	enumActor.first = tEXIT;
	enumActor.second = tempObjectVectorTwo;

	Entities.insert(enumActorTwo);
	
	std::pair <int, std::vector <Actor*>> enumActorThree;
	enumActor.first = tEnemy;
	enumActor.second = tempObjectVectorThree;

	Entities.insert(enumActorThree);
}

void Game::Update(float deltaTime)
{

	std::map<int, std::vector<Actor*>> tempMap;


	bgmControl.PlaySong();
	
	switch (state)
	{

		case GAME_STATE:

			if (count <= 0)
			{
				playerCharacter->Initialise();
				count++;
			}

			if (Entities[tEXIT][0]->GetCollider().AABBtoAABB(playerCharacter->GetCollider()))
			{
				ClearLevel();
			}
			
			for (int i = 0; i < Entities[tEnemy].size(); i++) {
				Entities[tEnemy][i]->Update(deltaTime);
			}

			for (int i = 0; i < Entities.size(); ++i)
			{
				std::vector<Actor*> resultObjectList;
				std::pair <int, std::vector<Actor*>> enumActor;

				for (int j = 0; j < Entities[i].size(); j++)
				{
					Vector3 temp = Entities[i][j]->GetPos();
					
					if (ProximityCull(playerCharacter->GetPos(), temp))
					{
						resultObjectList.push_back(Entities[i][j]);

					}
				}

				enumActor.first = i;
				enumActor.second = resultObjectList;
				tempMap.insert(enumActor);
			}

			playerCharacter->Update(deltaTime, tempMap);
			
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
				Entities[tWALL][ii]->Draw();
			}

			for (int ii = 0; ii < Entities[tEXIT].size(); ii++)
			{
				Entities[tEXIT][ii]->Draw();
			}
			glPopMatrix();

			dungeon->DrawRoof(textures[2]);
			dungeon->DrawFloor(textures[3]);

			for (int i = 0; i < Entities[tEnemy].size(); i++) 
			{
				Entities[tEnemy][i]->Draw();
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
		soundControl.PlaySound(0);
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
	int deadzone = 0.25;
	Vector3 pitchAxis;
	GLdouble fps = 60;
	GLdouble mouseSensitivity = 2;

	//If the mouse pointer has moved far enough, rotate camera
	if ((abs((long double)x) > deadzone) || (abs((long double)y) > deadzone)) 
	{	
		
		int deltaX = ((centreX - x) < 0) - (0 < (centreX - x));
		int deltaY = -(((centreY - y) < 0) - (0 < (centreY - y)));

		
		if (deltaX >= 1)
		{
			deltaX = 1 * deltaTime * fps * mouseSensitivity;
		}

		if (deltaX <= -1)
		{
			deltaX = -1 * deltaTime * fps * mouseSensitivity;
		}

		if (deltaY >= 1)
		{
			deltaY = 1 * deltaTime * fps * mouseSensitivity;
		}

		if (deltaY <= -1)
		{
			deltaY = -1 * deltaTime * fps * mouseSensitivity;
		}

		double radianX = deltaX * (PI / 180);
		double radianY = deltaY * (PI / 180);

		if (radianX != 0 || radianY != 0)
		{
			pitchAxis = playerCharacter->GetCameraViewDeltaVector().CrossProduct(playerCharacter->GetCameraUp());
			pitchAxis = pitchAxis.UnitVector();
			// pitch
			playerCharacter->RotateCamera(radianY, pitchAxis, playerCharacter->GetCameraViewDelta(), deltaTime);
			// yaw
			playerCharacter->RotateCamera(-radianX, Vector3(0, 1, 0), playerCharacter->GetCameraViewDelta(), deltaTime);
		}
		
		glutWarpPointer(centreX, centreY);

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

	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(0, 4); // guaranteed unbiased
	int chance = uni(rng);
	Wall *temp = NULL;

	if (chance < 4)
	{
		temp = new Wall(x, y, z, models[0], &textures[1]);
	}
	else
	{
		temp = new Wall(x, y, z, models[0], &textures[7]);
	}
	Entities[tWALL].push_back(temp);
}

void Game::AddExit(float x, float y, float z)
{
	LevelExit *exit = new LevelExit(x, y, z, models[3], &textures[8]);

	Entities[tEXIT].push_back(exit);
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
	Entities[tEnemy].clear();
	delete dungeon;
	dungeon = NULL;
	state = LOAD_STATE;
}

void Game::AddEnemy(float x, float y, float z, std::vector<Vector3> &f)
{
	Enemy *enemy = new Enemy(this, models[2], &textures[6], x, y, z, f);

	Entities[tEnemy].push_back(enemy);
}