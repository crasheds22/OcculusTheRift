#include <pch.h>

#include "Game.h"
#include <random>

Game::Game()
{
	playerCharacter = Player::GetInstance();
	
	shaysWorld = new Shay(this);
	menuScreens = new Menu(this);
	playerInterface = new GUI(this);

	state = SHAY_STATE;
	
	textures.resize(35);
	models.resize(10);

	pauseScreen = false;
	deathScreen = false;

	currentSpeed = 1;
	currentStage = 1;
	currentLevel = 1;
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
	playerCharacter->SetRotateSpeed(2);
	
	textures[0].LoadTexture("data/Group.png", 768, 768);
	textures[1].LoadTexture("data/wall1.png", 64, 64);
	textures[2].LoadTexture("data/roof.png", 32, 32);
	textures[3].LoadTexture("data/floor.png", 32, 32);
	textures[4].LoadTexture("data/Statue.png", 1024, 1024);
	textures[5].LoadTexture("data/Menu.png", 768, 768);
	textures[6].LoadTexture("data/eyeball.png", 128, 128);
	textures[7].LoadTexture("data/wall1_vines.png", 64, 64);
	textures[8].LoadTexture("data/exit.png", 128, 128);
	textures[9].LoadTexture("data/wall2.png", 64, 64);
	textures[10].LoadTexture("data/wall2_vines.png", 64, 64);
	textures[11].LoadTexture("data/roof2.png", 32, 32);
	textures[12].LoadTexture("data/floor2.png", 32, 32);
	textures[13].LoadTexture("data/wall3.png", 64, 64);
	textures[14].LoadTexture("data/wall3_vines.png", 64, 64);
	textures[15].LoadTexture("data/roof3.png", 32, 32);
	textures[16].LoadTexture("data/floor3.png", 32, 32);
	textures[17].LoadTexture("data/player_laser.png", 32, 32);
	textures[18].LoadTexture("data/enemy_laser.png", 32, 32);
	textures[19].LoadTexture("data/coin.png", 128, 128);
	textures[20].LoadTexture("data/crosshairRGBA.png", 64, 64);
	textures[21].LoadTexture("data/hb_empty_left.png", 32, 32);
	textures[23].LoadTexture("data/hb_empty_middle.png", 32, 32);
	textures[25].LoadTexture("data/hb_empty_right.png", 32, 32);
	textures[22].LoadTexture("data/hb_full_left.png", 32, 32);
	textures[24].LoadTexture("data/hb_full_middle.png", 32, 32);
	textures[26].LoadTexture("data/hb_full_right.png", 32, 32);
	textures[27].LoadTexture("data/Pause.png", 512, 512);
	textures[28].LoadTexture("data/Death.png", 512, 512);
	textures[29].LoadTexture("data/Story.png", 768, 768);
	textures[30].LoadTexture("data/hud_box.png", 64, 64);

	models[0] = new Model("data/wall1.obj");
	models[1] = new Model("data/statue_base.obj");
	models[2] = new Model("data/eyeball.obj");
	models[3] = new Model("data/exit.obj");
	models[4] = new Model("data/laser.obj");
	models[5] = new Model("data/coin.obj");

	gameScore = 0;
}

void Game::Update(float deltaTime)
{
	std::map<int, std::vector<Actor*>> playerMap;
	std::map<int, std::vector<Actor*>> enemyMap;

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
				if (currentStage < 3)
				{
					currentStage++;
				}
				else
				{
					currentLevel++;
					currentStage = 1;
				}
				soundControl.PlaySound(1);
				ClearLevel();
			}

			for (std::size_t i = 0; i < Entities[tPOWERUP].size(); i++) 
			{
				if (Entities[tPOWERUP][i]->GetCollider().AABBtoAABB(playerCharacter->GetCollider()))
				{
					soundControl.PlaySound(0);
					gameScore += 20;
					Entities[tPOWERUP].erase(Entities[tPOWERUP].begin() + i);
				}
				else
					Entities[tPOWERUP][i]->Update(deltaTime);
			}
			
			for (std::size_t i = 0; i < Entities[tEnemy].size(); i++)
			{
				enemyMap.clear();
				if (Entities[tEnemy][i] != NULL) {
					for (std::size_t j = 0; j < Entities.size(); ++j)
					{
						std::vector<Actor*> resultObjectList;
						std::pair <int, std::vector<Actor*>> enumActor;

						for (std::size_t k = 0; k < Entities[j].size(); k++)
						{
							if (Entities[j][k] != NULL && Entities[j][k] != Entities[tEnemy][i]) {
								Vector3 temp = Entities[j][k]->GetPos();

								if (ProximityCull(Entities[tEnemy][i]->GetPos(), temp))
								{
									resultObjectList.push_back(Entities[j][k]);
								}
							}
						}

						enumActor.first = j;
						enumActor.second = resultObjectList;
						enemyMap.insert(enumActor);
					}

					if (!pauseScreen) {
						Entities[tEnemy][i]->Update(deltaTime, enemyMap);
						//Entities[tEnemy][i]->Update(deltaTime);
					}
					
					if(Entities[tEnemy][i]->GetCurrentHealth() <= 0) {
						Entities[tEnemy].erase(Entities[tEnemy].begin() + i);
						gameScore += 35;
					}
				}
			}

			for (std::size_t i = 0; i < Entities[tProjectile].size(); i++) {
				Projectile* p = dynamic_cast<Projectile*>(Entities[tProjectile][i]);
				if (p) {
					if (p->GetTime() > 2) {
						Entities[tProjectile].erase(Entities[tProjectile].begin() + i);
					}
					else {
						Entities[tProjectile][i]->Update(deltaTime);
					}
				}
			}

			playerMap.clear();
			for (std::size_t i = 0; i < Entities.size(); ++i)
			{
				std::vector<Actor*> resultObjectList;
				std::pair <int, std::vector<Actor*>> enumActor;

				for (std::size_t j = 0; j < Entities[i].size(); j++)
				{
					if (Entities[i][j] != NULL) {
						Vector3 temp = Entities[i][j]->GetPos();

						if (ProximityCull(playerCharacter->GetPos(), temp))
						{
							resultObjectList.push_back(Entities[i][j]);
						}
					}
				}

				enumActor.first = i;
				enumActor.second = resultObjectList;
				playerMap.insert(enumActor);
			}

			playerCharacter->Update(deltaTime, playerMap);

			if (playerCharacter->GetCurrentHealth() <= 0)
			{
				deathScreen = true;
				currentLevel = 1;
				currentStage = 1;
				bgmControl.StopMusic();
				PlaySoundAt(6);
				SetState(MENU_STATE);
			}

			if (pauseScreen && !deathScreen)
			{
				currentSpeed = 0;
			}
			else
			{
				currentSpeed = 1;
			}

			break;

		case MENU_STATE:
			break;

		case LOAD_STATE:
			if (dungeon == NULL)
			{
				switch (currentStage)
				{
					case 1:
						bgmControl.SetSong(2);
						break;

					case 2:
						bgmControl.SetSong(3);
						break;

					case 3:
						bgmControl.SetSong(4);
						break;
				}

				dungeon = new Dungeon(this);
			}
			else
			{
				if (menuScreens->GetMenuState() == MAIN_MENU)
				{
					bgmControl.SetSong(1);
				}
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
				glutSetCursor(GLUT_CURSOR_LEFT_ARROW);

				if (menuScreens->GetExit())
				{
					menuScreens->Draw(textures[0]);
				}
				else if(deathScreen && !pauseScreen)
				{
					menuScreens->Draw(textures[28]);
					menuScreens->SetMenuState(DEATH_MENU);
				}
				else if (menuScreens->GetMenuState() == STORY_MENU)
				{
					menuScreens->Draw(textures[29]);
				}
				else
				{
					menuScreens->Draw(textures[5]);
					menuScreens->SetMenuState(MAIN_MENU);
				}
			}
			break;

		case SHAY_STATE:
			if (shaysWorld != NULL)
			{
				shaysWorld->SetWidthHeight(800, 500);
				glEnable(GL_DEPTH_TEST);
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();

				glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
				gluPerspective(45.0, 1.0 * glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT), 1.0, 250000.0);
				glMatrixMode(GL_MODELVIEW);
				shaysWorld->Draw();
			}
			
			break;

		case GAME_STATE:
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			playerCharacter->Draw();

			glPushMatrix();
			for (std::size_t ii = 0; ii < Entities[tWALL].size(); ii++)
			{
				Entities[tWALL][ii]->Draw();
			}

			for (std::size_t ii = 0; ii < Entities[tEXIT].size(); ii++)
			{
				Entities[tEXIT][ii]->Draw();
			}

			glPopMatrix();

			switch (currentStage)
			{
				case 1:
					dungeon->DrawRoof(textures[2]);
					dungeon->DrawFloor(textures[3]);
					break;
				
				case 2:
					dungeon->DrawRoof(textures[11]);
					dungeon->DrawFloor(textures[12]);
					break;
				
				case 3:
					dungeon->DrawRoof(textures[15]);
					dungeon->DrawFloor(textures[16]);
					break;
			}

			for (std::size_t i = 0; i < Entities[tEnemy].size(); i++)
			{
				if (Entities[tEnemy][i] != NULL)
					Entities[tEnemy][i]->Draw();
			}

			for (std::size_t i = 0; i < Entities[tProjectile].size(); i++) {
				if (Entities[tProjectile][i] != NULL) {
					Entities[tProjectile][i]->Draw();
				}
			}

			for (std::size_t i = 0; i < Entities[tPOWERUP].size(); i++) {
				if (Entities[tPOWERUP][i] != NULL)
					Entities[tPOWERUP][i]->Draw();
			}


			
			if(menuScreens->GetExit())
			{
				SetState(MENU_STATE);
			}
			else if(pauseScreen && !deathScreen)
			{
				glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
				menuScreens->Draw(textures[27]);
				menuScreens->SetMenuState(PAUSE_MENU);
			}
			else
			{
				glutSetCursor(GLUT_CURSOR_NONE);
				menuScreens->SetMenuState(0);
			}

			if (!pauseScreen)
			{
				DrawGUI();
				DrawHUD();
				std::string scoreText = "Score: ";
				DrawText(20, -10, scoreText);
				scoreText = std::to_string(gameScore);
				DrawText(20, -11, scoreText);
			}

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
		playerCharacter->DirectionL(currentSpeed);
		break;
	case 's':
	case 'S':
		playerCharacter->DirectionB(currentSpeed);
		break;
	case 'd':
	case 'D':
		playerCharacter->DirectionR(currentSpeed);
		break;
	case 'w':
	case 'W':
		playerCharacter->DirectionF(currentSpeed);
		break;
	case 't':
	case 'T':
		playerCharacter->SetCurrentHealth(playerCharacter->GetCurrentHealth() - 1);
		break;
	case 'p':
	case 'P':
		if(!deathScreen)
			pauseScreen = !pauseScreen;
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
	GLdouble mouseSensitivity = 0.95;

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
			playerCharacter->SetRot(deltaX, 0, 0);
		}
		
		glutWarpPointer(centreX, centreY);

	}

}

void Game::MouseClick(int button, int state, int x, int y) {
	if (playerCharacter->GetShotTimer() <= 0) {
		Vector3 playerPos(playerCharacter->GetPos().GetPointX(), playerCharacter->GetPos().GetPointY() + playerCharacter->GetCameraUp().GetPointY(), playerCharacter->GetPos().GetPointZ());

		AddProjectile(playerCharacter, playerPos, playerCharacter->GetCameraViewDeltaVector().UnitVector() * 5, 17, false);
		playerCharacter->SetShotTimer(playerCharacter->GetShotTime());
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
		state = MENU_STATE;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0, 0, 1);
		glFlush();
		delete shaysWorld;
		shaysWorld = NULL;
		bgmControl.SetSong(1);
	}
	else if (state == GAME_STATE && menuScreens->GetMenuState() == PAUSE_MENU)
	{
		pauseScreen = false;
		deathScreen = false;
		gameScore = 0;
		currentLevel = 1;
		currentStage = 1;
		state = MENU_STATE;
		menuScreens->SetMenuState(MAIN_MENU);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0, 0, 1);
		glFlush();
		bgmControl.SetSong(1);
	}
	else if (state == MENU_STATE && menuScreens->GetMenuState() == STORY_MENU)
	{
		pauseScreen = false;
		deathScreen = false;
		menuScreens->SetMenuState(STORY_MENU);
		menuScreens->SetMenuState(MAIN_MENU);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0, 0, 1);
		glFlush();
	}
}

void Game::DrawGUI()
{
	playerInterface->DrawReticle();
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

	switch (currentStage)
	{
	case 1:
		if (chance < 4)
		{
			temp = new Wall(x, y, z, models[0], &textures[1]);
		}
		else
		{
			temp = new Wall(x, y, z, models[0], &textures[7]);
		}
		break;

	case 2:
		if (chance < 4)
		{
			temp = new Wall(x, y, z, models[0], &textures[9]);
		}
		else
		{
			temp = new Wall(x, y, z, models[0], &textures[10]);
		}
		break;

	case 3:
		if (chance < 4)
		{
			temp = new Wall(x, y, z, models[0], &textures[13]);
		}
		else
		{
			temp = new Wall(x, y, z, models[0], &textures[14]);
		}
		break;
	}



	Entities[tWALL].push_back(temp);
}

void Game::AddExit(float x, float y, float z)
{
	LevelExit *exit = new LevelExit(x, y, z, models[3], &textures[8]);

	Entities[tEXIT].push_back(exit);
}

void Game::AddCoin(float x, float y, float z)
{
	Coin *coin = new Coin(x, y, z, models[5], &textures[19]);

	Entities[tPOWERUP].push_back(coin);
}

void Game::AddEnemy(float x, float y, float z)
{
	Enemy *enemy = new Enemy(this, models[2], &textures[6], x, y, z);

	Entities[tEnemy].push_back(enemy);
}

void Game::AddProjectile(Actor* owner, Vector3 start, Vector3 dir, int tex, bool isE) {
	Projectile *proj = new Projectile(owner, models[4], &textures[tex], 2 + (!isE * 4), dir, start, isE);
	PlaySoundAt(2);

	Entities[tProjectile].push_back(proj);
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
	minCullBox = actorPosition - (positionOffset);
	maxCullBox = actorPosition + (positionOffset);

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
	Entities[tProjectile].clear();
	Entities[tPOWERUP].clear();
	delete dungeon;
	dungeon = NULL;
	state = LOAD_STATE;
}

void Game::Restart()
{
	pauseScreen = false;
	deathScreen = false;

	currentStage = 1;
	currentLevel = 1;
	gameScore = 0;
	playerCharacter->Initialise();
	menuScreens->SetMenuState(0);
	ClearLevel();

	bgmControl.ResumeMusic();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 1);
	glFlush();
	bgmControl.SetSong(2);
}

int Game::GetGameScore()
{
	return gameScore;
}

void Game::PlaySoundAt(int index)
{
	soundControl.PlaySound(index);
}

void Game::DrawText(int x, int y, std::string text)
{
	glDisable(GL_TEXTURE_2D); //added this
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-32.0, 32.0, -18.0, 18.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3d(1.0, 1.0, 1.0);
	glRasterPos2i(x, y);
	void * font = GLUT_BITMAP_TIMES_ROMAN_24;
	for (string::iterator i = text.begin(); i != text.end(); ++i)
	{
		char c = *i;
		
		glutBitmapCharacter(font, c);
	}
	glMatrixMode(GL_PROJECTION); //swapped this with...
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW); //...this
	glPopMatrix();
	//added this

	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, 1.0 * glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT), 1.0, 400.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

std::vector <Texture>  Game::GetTexture()
{
	return textures;
}

int Game::GetStage()
{
	return currentStage;
}

int Game::GetLevel()
{
	return currentLevel;
}

void Game::DrawHUD()
{
	//Set View mode to orthographic
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-8.0, 8.0, -5.0, 5.0, 1.0, 30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float x1 = -7.5;
	float x2 = -6.5;

	float y1 = 4.5;
	float y2 = 3.5;
	int maxHealth = (int)playerCharacter->GetMaxHealth();
	int currentHealth = (int)playerCharacter->GetCurrentHealth();
	int hbSlot = 0;

	for (int i = 0; i < maxHealth; i++)
	{
		//Choose Texture
		if (i == 0)
		{
			hbSlot = 22;
		}
		else
		{
			if (i == maxHealth - 1)
			{
				hbSlot = 26;
			}
			else
			{
				hbSlot = 24;
			}
		}

		if (i + 1 > currentHealth)
		{
			hbSlot -= 1;
		}

		//Assign Texture
		std::vector<unsigned char> temp = textures[hbSlot].GetTexture();
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textures[hbSlot].GetWidth(), textures[hbSlot].GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, &temp[0]);

		//Draw Healthbar
		glPushMatrix();
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, -1);
		glVertex3f(x1 + i, y1, -1);
		glTexCoord2f(1.0, -1);
		glVertex3f(x2 + i, y1, -1);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(x2 + i, y2, -1);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(x1 + i, y2, -1);
		glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}




	std::vector<unsigned char> box = textures[30].GetTexture();
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textures[30].GetWidth(), textures[30].GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, &box[0]);

	float bx1 = 4.5;
	float bx2 = 7.5;
	float by1 = -2.5;
	float by2 = -3.25;

	//Draw Hud Box
	glPushMatrix();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, -1);
	glVertex3f(bx1, by1, -1);
	glTexCoord2f(1.0, -1);
	glVertex3f(bx2, by1, -1);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(bx2, by2, -1);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(bx1, by2, -1);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	


	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, 1.0 * glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT), 1.0, 400.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


}
