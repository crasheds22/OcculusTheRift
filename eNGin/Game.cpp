#include <pch.h>

#include "Game.h"

Game::Game() 
{
	playerCharacter = Player::GetInstance();
	

	/*
	cubist = new Cube[50];
	Vector3 * cubePos;
	cubePos = new Vector3[50];
	
	Vector3 * cubeScale;
	cubeScale = new Vector3[50];

	for (int ii = 0; ii < 50; ii++)
	{
		int jj;
		jj = ii + 10;
		cubePos[ii] = Vector3(jj, 0, 0);
	
	}
	
	for (int ii = 0; ii < 50; ii++)
	{
		cubeScale[ii] = Vector3(1, 1, 1);
	}
	

	std::vector <Actor> tempObjectVector;
	
	for (int ii = 0; ii < 50; ii++)
	{
		cubist[ii].SetPos(cubePos[ii]);
		cubist[ii].SetScale(cubeScale[ii]);
		cubist[ii].SetAABB();
		tempObjectVector.push_back(cubist[ii]);
		
	}

	std::pair <Actor::ActorClass, std::vector <Actor>> enumActor;
	enumActor.first = Actor::ActorClass::Object;
	enumActor.second = tempObjectVector;

	theEntities.insert(enumActor);
	*/
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
	delete[] cubist;
}

void Game::Run() 
{
	Draw();



	Update();
}

void Game::Initialise() 
{
	shaysWorld->Init();
	
	//centreX = 400;
	//centreY = 250;
	centreX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	centreY = glutGet(GLUT_WINDOW_HEIGHT) / 2;

	deltaTime = clock();

	playerCharacter->SetMoveSpeed(0.05);
	playerCharacter->SetRotateSpeed(0.05);

	textures[0].LoadTexture("data/Group.png", 768, 768);
	textures[1].LoadTexture("data/wall1.png", 64, 64);

	models[0] = new Model("data/wall1.obj");

	testWall = new Wall[50];

	for (int ii = 0; ii < 50; ii++)
	{
		int jj;
		jj = ii + 1;
		testWall[ii] = Wall(5 * jj, 0, 5 * jj, models[0], &textures[1]);
	}
	
	
	std::vector <Actor> tempObjectVectorOne;
	for (int ii = 0; ii < 50; ii++)
	{
		tempObjectVectorOne.push_back(testWall[ii]);
	}
	

	std::pair <Actor::ActorTag, std::vector <Actor>> enumActorOne;
	enumActorOne.first = Actor::ActorTag::Object;
	enumActorOne.second = tempObjectVectorOne;

	theEntities.insert(enumActorOne);

	/*
	textures[0].LoadTexture("data/hb_empty_left.png", 32, 32);
	textures[1].LoadTexture("data/hb_empty_middle.png", 32, 32);
	textures[2].LoadTexture("data/hb_empty_right.png", 32, 32);

	textures[3].LoadTexture("data/hb_full_left.png", 32, 32);
	textures[4].LoadTexture("data/hb_full_middle.png", 32, 32);
	textures[5].LoadTexture("data/hb_full_right.png", 32, 32);
	*/
}

void Game::Update()
{
	bgmControl.PlaySong();
	
	switch (state)
	{
		case GAME_STATE:
			playerCharacter->Update(theEntities);
			break;

		case MENU_STATE:
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
			for (int ii = 0; ii < 50; ii++)
			{
				testWall[ii].Draw();
			}
			glPopMatrix();
			
			glPushMatrix();
			
			
			/*
			for (int ii = 0; ii < 50; ii++)
			{
				glTranslatef(cubist[ii].GetPos().GetPointX(), cubist[ii].GetPos().GetPointY(), cubist[ii].GetPos().GetPointZ());
				glScalef(cubist[ii].GetScale().GetPointX(), cubist[ii].GetScale().GetPointY(), cubist[ii].GetScale().GetPointZ());
				cubist[ii].Draw();
			}
			*/
			glPopMatrix();

			glPushMatrix();
				if (exitScreen)
					DrawGUI();
			glPopMatrix();

			glFlush();

			

			break;
	}
}

void Game::InputDown(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a':
	case 'A':
		playerCharacter->DirectionLR(-1);
		break;
	case 's':
	case 'S':
		playerCharacter->DirectionFB(-1);
		break;
	case 'd':
	case 'D':
		playerCharacter->DirectionLR(1);
		break;
	case 'w':
	case 'W':
		playerCharacter->DirectionFB(1);
		break;
	case 't':
	case 'T':
		exitScreen = !exitScreen;
		break;
	}
}

void Game::InputUp(unsigned char key, int x, int y) 
{
	switch (key) {
	case 'a':
	case 'A':
	case 'd':
	case 'D':
		playerCharacter->DirectionLR(0);
		break;
	case 'w':
	case 'W':
	case 's':
	case 'S':
		playerCharacter->DirectionFB(0);
		break;
	}
}

void Game::MouseLook(int x, int y)
{
	int deadzone = 15;

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
		state = GAME_STATE;
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
