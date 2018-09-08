#include "Shay.h"
#include "Game.h"
#include <iostream>

Shay::Shay(Game* ownerIn)
{
	owner = ownerIn;
}

Shay::~Shay()
{
	delete statBase;
	delete portalMod;
}



void Shay::Init()
{



	portalMod = new ModelShay((char*)"data/portal.obj");
	statBase = new ModelShay((char*)"data/statue_base.obj");

	// settings for glut cylinders
	glu_cylinder = gluNewQuadric();
	gluQuadricTexture(glu_cylinder, GL_TRUE);

	// set the world co-ordinates (used to set quadrants for bounding boxes)
	cam.SetWorldCoordinates(36000.0, 43200.0);
	// turn collision detection on
	cam.SetCollisionDetectionOn(true);
	// set number of bounding boxes required
	cam.SetNoBoundingBoxes(50);
	// set starting position of user
	//cam.Position(32720.0, 9536.0, 4800.0, 180.0);
	//cam.Position(2608.0, 10500.0, 41025.0, 180.0);

	/* 
	cam.Position(32720.0, 9536.0, //original camera position
		4800.0, 180.0);
	/*/
	cam.Position(-1192.0, 10350.0, //camera in 400 corridor
		42060.0, 180.0);
	//*/ //comment toggle

	CreatePlains();

	// creates bounding boxes and places in array
	CreateBoundingBoxes();
	// copies bounding boxes from array to linked lists (one fopr each quadrant)
	cam.InitiateBoundingBoxes();

	// load texture images and create display lists
	CreateTextureList();
	CreateTextures();

}

void Shay::Draw() {
	// check for movement

	std::cout << "X: " << cam.GetLR() << " Y: " << cam.GetUD() << " Z: " << cam.GetFB() << std::endl;
	cam.CheckCamera();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// DISPLAY TEXTURES
	//enable texture mapping
	glEnable (GL_TEXTURE_2D);
	glPushMatrix();	
		// displays the welcome screen
		if (DisplayWelcome) 
			cam.DisplayWelcomeScreen (width, height, 1, tp.GetTexture(WELCOME));	
		// displays the exit screen
		if (DisplayExit) 
			cam.DisplayWelcomeScreen (width, height, 0, tp.GetTexture(EXIT) );
		// displays the map
		if (DisplayMap) 
			cam.DisplayMap(width, height, tp.GetTexture(MAP));
		


		// display no exit sign (position check should really be in an object, but didn't have time)
		if ((cam.GetLR() > 35500.0) && (cam.GetFB() < 25344.0) ||
			(cam.GetLR() > 34100.0) && (cam.GetFB() > 41127.0))
		{
			cam.DisplayNoExit(width, height, tp.GetTexture(NO_EXIT));
		}
		
		// set the movement and rotation speed according to frame count
		IncrementFrameCount();

		cam.SetMoveSpeed (stepIncrement);
		cam.SetRotateSpeed (angleIncrement);
		// display images
		DrawBackdrop();

	glPopMatrix();
	 

	if (rot < 360)
	{
		rot += 0.5;
	}
	else
	{
		rot = 0;
	}
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(234));
	glPushMatrix();
		glTranslatef(-2000, 9800, 31650);
		glScalef(120, 120, 120);
		portalMod->DrawModel(0, 0, 0, tp.GetTexture(234));
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(235));
	glPushMatrix();
		glTranslatef(-5000, 9800, 34000);
		glScalef(150, 150, 150);
		statBase->DrawModel(0, 0, 0, tp.GetTexture(235));
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

	//Take Portal
	if ((cam.GetLR() > -2240.0) && (cam.GetLR() < -1760.0) &&
		(cam.GetFB() < 31700) && (cam.GetFB() > 31500) && (cam.GetUD() <= 10450) && (cam.GetUD() >= 10250))
	{
		if (!hasSwitched)
		{
			std::cout << "State Changed" << std::endl;
			hasSwitched = true;
			owner->SwitchState();
		}
	}

}

void Shay::DownKey(unsigned char key, int x, int y) {
	switch (key)
	{
		case 'f':
		case 'F':
			owner->SwitchState();
			break;

		case 'A':
		case 'a':
			cam.DirectionRotateLR(-1);
			break;
		case 'D':
		case 'd':
			cam.DirectionRotateLR(1);
			break;
		case 'W':
		case 'w':
			cam.DirectionFB(1);
			break;
		case 'S':
		case 's':
			cam.DirectionFB(-1);
			break;
		// step left
		case 'Z':
		case 'z':
			cam.DirectionLR(-1);
			break;
		// step right
		case 'X':
		case 'x':
			cam.DirectionLR(1);
		break;
		// look up
		case 'Q':
		case 'q':
			cam.DirectionLookUD(1);
			break;
		// look down
		case 'E':
		case 'e':
			cam.DirectionLookUD(-1);
		break;
		case 'm':
		case 'M':
		{
			if (DisplayMap)
			{
				DisplayMap = false;
			}
			else
			{
				DisplayMap = true;
			}
		}
		break;
		// exit tour (escape key)
		case 27:
		{
			DisplayExit = true;
		}
		break;
		// display welcome page (space key)
		case ' ':
		{
			if (DisplayWelcome)
			{
				DisplayWelcome = false;
			}
			else
			{
				DisplayWelcome = true;
			}
		}
		break;
		// display light fittings
		case 'l':
		case 'L':
		{
			if (lightsOn)
			{
				lightsOn = false;
			}
			else
			{
				lightsOn = true;
			}
		}
		break;
	}
}

void Shay::UpKey(unsigned char key, int x, int y) {
	switch (key)
	{
		// step left or right
		case 'x' :
		case 'X' :
		case 'z' :
		case 'Z' :
			cam.DirectionLR(0);
		break;
		// look left up or down
		case 'e' :
		case 'E' :
		case 'q' :
		case 'Q' :
			cam.DirectionLookUD(0);
		break;

		// rotate left or right
		case 'A':
		case 'D':
		case 'a':
		case 'd':
			cam.DirectionRotateLR(0);
			break;
			// move backwards or forwards
		case 'W':
		case 'S':
		case 'w':
		case 's':
			cam.DirectionFB(0);
			break;
	}
}

void Shay::SetWidthHeight(int w, int h) {
	width = w;
	height = h;
}

void Shay::MouseClick(int button, int state, int x, int y) {
	// exit tour if clicked on exit splash screen
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
	{
		if ((DisplayExit) && (x <= width/2.0 + 256.0) && (x >= width/2.0 - 256.0)
			&& (y <= height/2.0 + 256.0) && (y >= height/2.0 - 256.0))
		{
			DeleteImageFromMemory(image);
			exit(1);
		}
  	}
}

//--------------------------------------------------------------------------------------
// Set up bounding boxes for collsion detection
//--------------------------------------------------------------------------------------
void Shay::CreateBoundingBoxes()
{
	// chanc block
	cam.SetAABBMaxX(0, 35879.0);
	cam.SetAABBMinX(0, 33808.0);
	cam.SetAABBMaxZ(0, 22096.0);
	cam.SetAABBMinZ(0, 4688.0);

	// between chanc block and phys sci
	cam.SetAABBMaxX(1, 35999.0);
	cam.SetAABBMinX(1, 35730.0);
	cam.SetAABBMaxZ(1, 25344.0);
	cam.SetAABBMinZ(1, 22096.0);

	// phy sci block panel 1
	cam.SetAABBMaxX(2, 35879.0);
	cam.SetAABBMinX(2, 33808.0);
	cam.SetAABBMaxZ(2, 26752.0);
	cam.SetAABBMinZ(2, 25344.0);

	// phy sci block 1st doorway
	cam.SetAABBMaxX(3, 35879.0);
	cam.SetAABBMinX(3, 34256.0);
	cam.SetAABBMaxZ(3, 27559.0);
	cam.SetAABBMinZ(3, 26752.0);

	// phy sci block 2nd panel
	cam.SetAABBMaxX(4, 35879.0);
	cam.SetAABBMinX(4, 33808.0);
	cam.SetAABBMaxZ(4, 36319.0);
	cam.SetAABBMinZ(4, 27559.0);

	// phy sci block 2nd doorway
	cam.SetAABBMaxX(5, 35879.0);
	cam.SetAABBMinX(5, 34260.0);
	cam.SetAABBMaxZ(5, 37855.0);
	cam.SetAABBMinZ(5, 36319.0);

	// phy sci block 3rd panel
	cam.SetAABBMaxX(6, 35879.0);
	cam.SetAABBMinX(6, 33808.0);
	cam.SetAABBMaxZ(6, 41127.0);
	cam.SetAABBMinZ(6, 37855.0);

	// drinks machine
	cam.SetAABBMaxX(7, 35879.0);
	cam.SetAABBMinX(7, 34704.0);
	cam.SetAABBMaxZ(7, 25344.0);
	cam.SetAABBMinZ(7, 24996.0);
		
	// bottom of steps
	cam.SetAABBMaxX(8, 33808.0);
	cam.SetAABBMinX(8, 0.0);
	cam.SetAABBMaxZ(8, 4688.0);
	cam.SetAABBMinZ(8, 0.0);

	// end of phy sci block exit (top of steps)
	cam.SetAABBMaxX(9, 35879.0);
	cam.SetAABBMinX(9, 34320.0);
	cam.SetAABBMaxZ(9, 43056.0);
	cam.SetAABBMinZ(9, 41127.0);

	// library end panel
	cam.SetAABBMaxX(10, 34320.0);
	cam.SetAABBMinX(10, 6514.0);
	cam.SetAABBMaxZ(10, 50000.0);
	cam.SetAABBMinZ(10, 43036.0);

	// KBLT
	cam.SetAABBMaxX(11, 28104.0);
	cam.SetAABBMinX(11, 25608.0);
	cam.SetAABBMaxZ(11, 43046.0);
	cam.SetAABBMinZ(11, 42754.0);

	// Canteen block
	cam.SetAABBMaxX(12, 2608.0);
	cam.SetAABBMinX(12, 2000.0);
	cam.SetAABBMaxZ(12, 41150.0);
	cam.SetAABBMinZ(12, 0.0);

	// Telephones
	cam.SetAABBMaxX(13, 33892.0);
	cam.SetAABBMinX(13, 33872.0);
	cam.SetAABBMaxZ(13, 25344.0);
	cam.SetAABBMinZ(13, 25173.0);

	// Telephones
	cam.SetAABBMaxX(14, 34277.0);
	cam.SetAABBMinX(14, 34157.0);
	cam.SetAABBMaxZ(14, 25344.0);
	cam.SetAABBMinZ(14, 25173.0);

	// Telephones
	cam.SetAABBMaxX(15, 35462.0);
	cam.SetAABBMinX(15, 34541.0);
	cam.SetAABBMaxZ(15, 25344.0);
	cam.SetAABBMinZ(15, 25173.0);

	// Wall by Steps
	cam.SetAABBMaxX(16, 31548.0);
	cam.SetAABBMinX(16, 31444.0);
	cam.SetAABBMaxZ(16, 10395.0);
	cam.SetAABBMinZ(16, 4590.0);

	//440 south wall next to broadwalk
	cam.SetAABBMaxX(17, 2608.0);
	cam.SetAABBMinX(17, -27360.0);
	cam.SetAABBMaxZ(17, 50000.0);
	cam.SetAABBMinZ(17, 42750.0);

	//440 West wall next to broadwalk
	cam.SetAABBMaxX(18, -20952.0);
	cam.SetAABBMinX(18, -24752.0);
	cam.SetAABBMaxZ(18, 39050.0);
	cam.SetAABBMinZ(18, 28525.0);

	//440 East wall next to broadwalk
	cam.SetAABBMaxX(19, 0.0);
	cam.SetAABBMinX(19, -1192.0);
	cam.SetAABBMaxZ(19, 40860.0 - 1140.0);
	cam.SetAABBMinZ(19, 28525.0);

	//440 North wall next to broadwalk
	cam.SetAABBMaxX(20, -1192.0);
	cam.SetAABBMinX(20, -20952.0);
	cam.SetAABBMaxZ(20, 31550.0);
	cam.SetAABBMinZ(20, 21550.0);
}

//--------------------------------------------------------------------------------------
// Set up co-ordinates of different plains
//--------------------------------------------------------------------------------------
void Shay::CreatePlains()
{	
	// grass slope
	cam.SetPlains (ZY_PLAIN, 4848.0 ,31568.0 ,9536.0, 10450.0 ,6200.0, 10000.0);

	// flat land (pavement and grass)
	cam.SetPlains (FLAT_PLAIN, 0.0, 36000.0 , 10450.0, 10450.0, 10000.0, 17000.0);
	cam.SetPlains (FLAT_PLAIN, 0.0, 6500.0 , 10450.0, 10450.0, 17000.0, 40000.0);
	cam.SetPlains (FLAT_PLAIN, 27000.0, 36000.0 , 10450.0, 10450.0, 17000.0, 40000.0);
	cam.SetPlains (FLAT_PLAIN, 0.0, 36000.0 , 10450.0, 10450.0, 40000.0, 50000.0);
	
	// top of lower hill
	cam.SetPlains (FLAT_PLAIN, 9000.0, 22000.0 , 10650.0, 10650.0, 19000.0, 23000.0);
	cam.SetPlains (FLAT_PLAIN, 9000.0, 10000.0 , 10650.0, 10650.0, 28000.0, 33000.0);
	cam.SetPlains (FLAT_PLAIN, 9000.0, 22000.0 , 10650.0, 10650.0, 36000.0, 37000.0);
	// sides of lower hill
	cam.SetPlains (ZY_PLAIN, 6500.0, 27000.0 , 10450.0, 10650.0, 17000.0, 19000.0);
	cam.SetPlains (ZY_PLAIN, 6500.0, 27000.0 , 10650.0, 10450.0, 37000.0, 40000.0);
	cam.SetPlains (XY_PLAIN, 6500.0, 9000.0 , 10450.0, 10650.0, 17000.0, 40000.0);
	cam.SetPlains (XY_PLAIN, 22000.0, 27000.0 , 10650.0, 10450.0, 17000.0, 40000.0);

	// top of higher hill
	cam.SetPlains (FLAT_PLAIN, 14000.0, 18000.0 , 10875.0, 108075.0, 28000.0, 33000.0);
	// sides of higher hill
	cam.SetPlains (ZY_PLAIN, 10000.0, 22000.0 , 10650.0, 10875.0, 23000.0, 28000.0);
	cam.SetPlains (ZY_PLAIN, 10000.0, 22000.0 , 10875.0, 10650.0, 33000.0, 36000.0);
	cam.SetPlains (XY_PLAIN, 10000.0, 14000.0 , 10650.0, 10875.0, 23000.0, 36000.0);
	cam.SetPlains (XY_PLAIN, 18000.0, 22000.0 , 10875.0, 10650.0, 23000.0, 36000.0);

	//entance steps
	step = 10450.0;
	stepLength = 9808.0;
	for (int i = 0; i < 18 ; i ++)
	{
		cam.SetPlains (FLAT_PLAIN, 31582.0, 33835, step, step, stepLength, stepLength + 42.0);		
		step -= 48.0;
		stepLength -= 142.0;
		if ((i+3) % 5 == 0) 
		{
			stepLength -= 500.0;
			step -= 48.0;
		}
	}

	//Broadwalk 44 Building
	//Courtyard floor
	cam.SetPlains(FLAT_PLAIN, 2000, -20952, 10450, 10450, 30000, 43000);
	//Upstairs
	// - East wall

	// - West wall

	// - South wall

	//East stairwell
	// - first flight
	step = 10450;
	stepLength = -1256;
	for (i = 0; i < 10; i++) {
		cam.SetPlains(FLAT_PLAIN, stepLength, stepLength + 64, step, step, 40290, 40860);

		step += 64;
		stepLength += 64;
	}
	// - landing
	cam.SetPlains(FLAT_PLAIN, stepLength, stepLength + 128, step, step, 39720, 40860);
	// - second flight
	step = 11730;
	stepLength = -1256;
	for (i = 0; i < 10; i++) {
		cam.SetPlains(FLAT_PLAIN, stepLength, stepLength + 64, step, step, 39720, 40290);

		step -= 64;
		stepLength += 64;
	}

	//West stairwell
	// - first flight
	step = 11090;
	stepLength = -20952 - 640;
	for (i = 0; i < 10; i++)
	{
		cam.SetPlains(FLAT_PLAIN, stepLength, stepLength + 64, step, step, 40290, 40860);

		step -= 64;
		stepLength += 64;
	}
	// - landing
	step = 11090;
	stepLength = -20952 - 640 - 128;
	cam.SetPlains(FLAT_PLAIN, stepLength, stepLength+128, step, step, 39720, 40860);
	// - second flight
	step = 11090;
	stepLength = -20952 - 640;
	for (i = 0; i < 10; i++)
	{
		cam.SetPlains(FLAT_PLAIN, stepLength, stepLength + 64, step, step, 39720, 40290);

		step += 64;
		stepLength += 64;
	}

	// temp plain to take down to ECL1
	cam.SetPlains (ZY_PLAIN, 3200.0, 4800.0 , 10450.0, 9370.0, 53400.0, 57900.0);
}

//--------------------------------------------------------------------------------------
//  Delete raw image and clear memory
//--------------------------------------------------------------------------------------
void Shay::DeleteImageFromMemory(unsigned char* tempImage)
{
	tempImage = NULL;
		if (tempImage == NULL)
	{
		delete [] tempImage;
	}
}

//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Load and Create Textures
//--------------------------------------------------------------------------------------
void Shay::CreateTextures()
{
	glEnable(GL_DEPTH_TEST);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	// set texture count
	tp.SetTextureCount(250);

	// load and create textures
	image = tp.LoadTexture((char*)"data/abovechanctext.raw", 128, 1024);
	tp.CreateTexture(ABOVE_CHANC_TEXT, image, 128, 1024);

	image = tp.LoadTexture((char*)"data/abovechanctext2.raw", 128, 1024);
	tp.CreateTexture(ABOVE_CHANC_TEXT_2, image, 128, 1024);

	image = tp.LoadTexture((char*)"data/abovechanctext3.raw", 128, 1024);
	tp.CreateTexture(ABOVE_CHANC_TEXT_3, image, 128, 1024);

	image = tp.LoadTexture((char*)"data/aboveLibText.raw", 1024, 256);
	tp.CreateTexture(ABOVE_LIB_TEXT, image, 1024, 256);

	image = tp.LoadTexture((char*)"data/aboveLibraryText2.raw", 1024, 256);
	tp.CreateTexture(ABOVE_LIB_TEXT_2, image, 1024, 256);

	image = tp.LoadTexture((char*)"data/aboveUnder4B.raw",256, 128);
	tp.CreateTexture(ABOVE_UNDER_4B, image, 256, 128);

	image = tp.LoadTexture((char*)"data/aboveWindows.raw", 128, 256);
	tp.CreateTexture(ABOVE_WINDOW_BLOCK, image, 128, 256);

	image = tp.LoadTexture((char*)"data/aboveWindows2.raw", 128, 256);
	tp.CreateTexture(ABOVE_WINDOW_BLOCK_2, image, 128, 256);

	image = tp.LoadTexture((char*)"data/aboveWindowsChanc.raw", 128, 256);
	tp.CreateTexture(ABOVE_WINDOW_BLOCK_CHANC, image, 128, 256);

	image = tp.LoadTexture((char*)"data/aboveWindows2posts.raw", 128, 256);
	tp.CreateTexture(ABOVE_UNDER_POSTS, image, 128, 256);
	
	image = tp.LoadTexture((char*)"data/aboveWindows2posts2.raw", 128, 256);
	tp.CreateTexture(ABOVE_UNDER_POSTS_2, image, 256, 128);

	image = tp.LoadTexture((char*)"data/aboveWindowsLib.raw", 256, 256);
	tp.CreateTexture(ABOVE_LIB, image, 256, 256);

	image = tp.LoadTexture((char*)"data/aboveWindows2lib.raw", 256, 128);
	tp.CreateTexture(ABOVE_WINDOW_UNDER_LIB, image, 256, 128);

	image = tp.LoadTexture((char*)"data/aboveWindows3bricks.raw", 256, 256);
	tp.CreateTexture(ABOVE_WINDOW_BLOCK_3, image, 256, 256);

	image = tp.LoadTexture((char*)"data/abovephysscitext.raw", 256, 1024);
	tp.CreateTexture(ABOVE_PHYS_SCI_TEXT, image, 256, 1024);

	image = tp.LoadTexture((char*)"data/aboveWindows3bricksXY.raw", 256, 256);
	tp.CreateTexture(ABOVE_WINDOW_BLOCK_XY_3, image, 256, 256);

	image = tp.LoadTexture((char*)"data/aboveWindowEdge.raw", 128, 256);
	tp.CreateTexture(ABOVE_WINDOW_EDGE_3B, image, 128, 256);

	image = tp.LoadTexture((char*)"data/aboveWindowEdgeLib.raw", 256, 64);
	tp.CreateTexture(ABOVE_WINDOW_EDGE_3B_LIB, image, 256, 64);

	image = tp.LoadTexture((char*)"data/aboveWindowsLibEdge.raw", 256, 64);
	tp.CreateTexture(ABOVE_WINDOW_EDGE_4B_LIB, image, 256, 64);

	image = tp.LoadTexture((char*)"data/aboveTicketsText.raw", 256, 256);
	tp.CreateTexture(ABOVE_TICKETS_TEXT, image, 256, 256);

	image = tp.LoadTexture((char*)"data/aboveWindowsEdge.raw", 128, 128);
	tp.CreateTexture(ABOVE_CHANC_EDGE, image, 128, 128);

	image = tp.LoadTexture((char*)"data/belowrooffill.raw", 128, 256);
	tp.CreateTexture(BELOW_ROOF_FILL, image, 128, 256);

	image = tp.LoadTexture((char*)"data/bench.raw", 64, 64);
	tp.CreateTexture(BENCH_TOP, image, 64, 64);

	image = tp.LoadTexture((char*)"data/benchedgeside.raw", 64, 64);
	tp.CreateTexture(BENCH_EDGE_SIDE, image, 64, 64);

	image = tp.LoadTexture((char*)"data/benchedge.raw", 64, 64);
	tp.CreateTexture(BENCH_EDGE, image, 64, 64);

	image = tp.LoadTexture((char*)"data/benchedgetop.raw", 64, 64);
	tp.CreateTexture(BENCH_EDGE_TOP, image, 64, 64);

	image = tp.LoadTexture((char*)"data/benchedge2.raw", 64, 64);
	tp.CreateTexture(BENCH_EDGE_2, image, 64, 64);

	image = tp.LoadTexture((char*)"data/benchedge3.raw", 64, 64);
	tp.CreateTexture(BENCH_EDGE_3, image, 64, 64);

	image = tp.LoadTexture((char*)"data/benchedgetop2.raw", 64, 64);
	tp.CreateTexture(BENCH_EDGE_TOP_2, image, 64, 64);

	image = tp.LoadTexture((char*)"data/benchside.raw", 64, 64);
	tp.CreateTexture(BENCH_SIDE, image, 64, 64);

	image = tp.LoadTexture((char*)"data/benchside2.raw", 64, 64);
	tp.CreateTexture(BENCH_SIDE_2, image, 64, 64);

	image = tp.LoadTexture((char*)"data/bricks1.raw", 128, 128);
	tp.CreateTexture(WALL_BRICK_YZ, image, 128, 128);

	image = tp.LoadTexture((char*)"data/bricks2.raw", 128, 128);
	tp.CreateTexture(WALL_BRICK_XY, image, 128, 128);

	image = tp.LoadTexture((char*)"data/bricks2edge.raw", 128, 128);
	tp.CreateTexture(WALL_BRICK_XY_END, image, 128, 128);

	image = tp.LoadTexture((char*)"data/bricks1edge.raw", 128, 128);
	tp.CreateTexture(WALL_BRICK_YZ_END, image, 128, 128);

	image = tp.LoadTexture((char*)"data/bricks075.raw", 128, 128);
	tp.CreateTexture(WALL_BRICK_3_4, image, 128, 128);

	image = tp.LoadTexture((char*)"data/brick87.raw", 128, 128);
	tp.CreateTexture(WALL_BRICK_XY_87WIDTH, image, 128, 128);

	image = tp.LoadTexture((char*)"data/brickgap.raw", 128, 32);
	tp.CreateTexture(WALL_BRICK_GAP_YZ, image, 128, 32);

	image = tp.LoadTexture((char*)"data/brickgap2.raw", 128, 32);
	tp.CreateTexture(WALL_BRICK_GAP2_YZ, image, 128, 32);
	
	image = tp.LoadTexture((char*)"data/bricksecsign.raw", 256, 128);
	tp.CreateTexture(WALL_BRICK_SEC_SIGN, image, 256, 128);

	image = tp.LoadTexture((char*)"data/brickshadow.raw", 128, 128);
	tp.CreateTexture(SHADOW_BRICK, image, 128, 128);

	image = tp.LoadTexture((char*)"data/bricksUSD.raw", 128, 128);
	tp.CreateTexture(WALL_BRICK_USD_YZ, image, 128, 128);

	image = tp.LoadTexture((char*)"data/carpet.raw", 32, 32);
	tp.CreateTexture(CARPET, image, 32, 32);

	image = tp.LoadTexture((char*)"data/coffeeMachine.raw", 128, 256);
	tp.CreateTexture(COFFEE_MACHINE, image, 128, 256);

	image = tp.LoadTexture((char*)"data/cokeMachine.raw", 128, 256);
	tp.CreateTexture(COKE_MACHINE, image, 128, 256);

	image = tp.LoadTexture((char*)"data/COsign.raw", 256, 128);
	tp.CreateTexture(CO_SIGN, image, 256, 128);

	image = tp.LoadTexture((char*)"data/counterside.raw", 4, 16);
	tp.CreateTexture(COUNTER_SIDE, image, 4, 16);

	image = tp.LoadTexture((char*)"data/countertop.raw", 1, 1);
	tp.CreateTexture(COUNTER_TOP, image, 1, 1);

	image = tp.LoadTexture((char*)"data/drainpipe.raw", 32, 2);
	tp.CreateTexture(DRAINPIPE, image, 32, 2);

	image = tp.LoadTexture((char*)"data/drinksEdge.raw", 16, 2);
	tp.CreateTexture(DRINKS_EDGE, image, 16, 2);

	image = tp.LoadTexture((char*)"data/drinksSide.raw", 64, 64);
	tp.CreateTexture(DRINKS_SIDE, image, 64, 64);

	image = tp.LoadTexture((char*)"data/drinksSide2.raw", 64, 64);
	tp.CreateTexture(DRINKS_SIDE_2, image, 64, 64);
	
	image = tp.LoadTexture((char*)"data/drinksSidetop.raw", 64, 64);
	tp.CreateTexture(DRINKS_TOP, image, 64, 64);

	image = tp.LoadTexture((char*)"data/doorpave1.raw",  128, 256);
	tp.CreateTexture(DOORPAVE_1, image, 128, 256);

	image = tp.LoadTexture((char*)"data/doorpost1.raw", 1024, 128);
	tp.CreateTexture(DOOR_POST_CHANC, image, 1024, 128);

	image = tp.LoadTexture((char*)"data/doorpostSec.raw", 1024, 128);
	tp.CreateTexture(DOOR_POST_SECURITY, image, 1024, 128);

	image = tp.LoadTexture((char*)"data/doorpostside1.raw", 64, 1024);
	tp.CreateTexture(DOOR_SIDEPOST_CHANC, image, 64, 1024);

	image = tp.LoadTexture((char*)"data/doorPostLibSide.raw", 512, 64);
	tp.CreateTexture(DOOR_POST_LIB, image, 512, 64);

	image = tp.LoadTexture((char*)"data/glassboard.raw", 512, 256);
	tp.CreateTexture(GLASS_BOARD, image, 512, 256);

	image = tp.LoadTexture((char*)"data/glassboard2.raw", 512, 256);
	tp.CreateTexture(GLASS_BOARD_2, image, 512, 256);

	image = tp.LoadTexture((char*)"data/glassboard3.raw", 512, 256);
	tp.CreateTexture(GLASS_BOARD_3, image, 512, 256);

	image = tp.LoadTexture((char*)"data/glassboardSide.raw", 2, 16);
	tp.CreateTexture(GLASS_B_SIDE, image, 2, 16);

	image = tp.LoadTexture((char*)(char*)"data/grass.raw", 64, 64);
	tp.CreateTexture(GRASS, image, 64, 64);

	image = tp.LoadTexture((char*)"data/grass2.raw", 64, 64);
	tp.CreateTexture(GRASS_2, image, 64, 64);

	image = tp.LoadTexture((char*)"data/grass3.raw", 64, 64);
	tp.CreateTexture(GRASS_HILL, image, 64, 64);

	image = tp.LoadTexture((char*)"data/GSsign.raw", 256, 256);
	tp.CreateTexture(GS_SIGN, image, 256, 256);

	image = tp.LoadTexture((char*)"data/GSsign2.raw", 256, 256);
	tp.CreateTexture(GS_SIGN_2, image, 256, 256);

	image = tp.LoadTexture((char*)"data/GSsignedge.raw", 256, 64);
	tp.CreateTexture(GS_SIGN_EDGE, image, 256, 64);

	image = tp.LoadTexture((char*)"data/kbl.raw", 512, 256);
	tp.CreateTexture(KBLT, image, 512, 256);

	image = tp.LoadTexture((char*)"data/KBLTside1.raw", 2, 128);
	tp.CreateTexture(KBLT_SIDE_1, image, 2, 128);

	image = tp.LoadTexture((char*)"data/KBLTside2.raw", 2, 2);
	tp.CreateTexture(KBLT_SIDE_2, image, 2, 2);
	
	image = tp.LoadTexture((char*)"data/kblCorner.raw", 1, 1);
	tp.CreateTexture(KBLT_EDGE_CORNER, image, 1, 1);

	image = tp.LoadTexture((char*)"data/kbltEdge.raw", 16, 32);
	tp.CreateTexture(KBLT_EDGE, image, 16, 32);

	image = tp.LoadTexture((char*)"data/kbltEdge2.raw", 32, 16);
	tp.CreateTexture(KBLT_EDGE_2, image, 32, 16);

	image = tp.LoadTexture((char*)"data/light.raw", 256, 64);
	tp.CreateTexture(LIGHT, image, 256, 64);

	image = tp.LoadTexture((char*)"data/lightsupport.raw", 8, 2);
	tp.CreateTexture(LIGHT_SUPPORT, image, 8, 2);

	image = tp.LoadTexture((char*)"data/lightsupport2.raw", 2, 8);
	tp.CreateTexture(LIGHT_SUPPORT_2, image, 2, 8);

	image = tp.LoadTexture((char*)"data/machineSides.raw", 1, 1);
	tp.CreateTexture(MACHINE_SIDES, image, 1, 1);

	image = tp.LoadTexture((char*)"data/machineSides2.raw", 1, 1);
	tp.CreateTexture(MACHINE_SIDES_2, image, 1, 1);

	image = tp.LoadTexture((char*)"data/mainPost.raw",  128, 256);
	tp.CreateTexture(MAIN_POST, image, 128, 256);
	
	image = tp.LoadTexture((char*)"data/mainPost2.raw", 256, 128);
	tp.CreateTexture(MAIN_POST_2, image, 256, 128);

	image = tp.LoadTexture((char*)"data/map2.raw", 256, 512);
	tp.CreateTexture(MAP_2, image, 256, 512);

	image = tp.LoadTexture((char*)"data/nexus.raw", 512, 256);
	tp.CreateTexture(NEXUS_SIGN, image, 512, 256);

	image = tp.LoadTexture((char*)"data/nexusSide.raw", 2, 16);
	tp.CreateTexture(NEXUS_SIDE, image, 2, 16);

	image = tp.LoadTexture((char*)"data/noexit.raw", 256, 64);
	tp.CreateTexture(NO_EXIT, image, 256, 64);

	image = tp.LoadTexture((char*)"data/nosmokesign.raw", 256, 128);
	tp.CreateTexture(NO_SMOKE_SIGN, image, 256, 128);

	image = tp.LoadTexture((char*)"data/pavement.raw", 128, 64);
	tp.CreateTexture(PAVEMENT, image, 128, 64);

	image = tp.LoadTexture((char*)"data/pavement16.raw", 32, 64);
	tp.CreateTexture(PAVEMENT_16, image, 32, 64);

	image = tp.LoadTexture((char*)"data/pavementflip.raw", 128, 64);
	tp.CreateTexture(PAVEMENT_FLIP, image, 128, 64);

	image = tp.LoadTexture((char*)"data/pavementcorner1.raw", 128, 128);
	tp.CreateTexture(PAVEMENT_CORNER_1, image, 128, 128);

	image = tp.LoadTexture((char*)"data/pavementcorner2.raw", 128, 128);
	tp.CreateTexture(PAVEMENT_CORNER_2, image, 128, 128);

	image = tp.LoadTexture((char*)"data/pavementtop.raw", 64, 128);
	tp.CreateTexture(PAVEMENT_TOP, image, 64, 128);

	image = tp.LoadTexture((char*)"data/pavementtopflip.raw", 64, 128);
	tp.CreateTexture(PAVEMENT_TOP_FLIP, image, 64, 128);

	image = tp.LoadTexture((char*)"data/pavementSide.raw", 64, 64);
	tp.CreateTexture(PAVEMENTSIDE_LEFT, image, 64, 64);

	image = tp.LoadTexture((char*)"data/pavementSide2.raw", 64, 64);
	tp.CreateTexture(PAVEMENTSIDE_RIGHT, image, 64, 64);

	image = tp.LoadTexture((char*)"data/pavementSide3.raw", 64, 64);
	tp.CreateTexture(PAVEMENTSIDE_TOP, image, 64, 64);

	image = tp.LoadTexture((char*)"data/phonefront.raw", 512, 32);
	tp.CreateTexture(TELEPHONE_FRONT, image, 512, 32);
	
	image = tp.LoadTexture((char*)"data/phoneside1.raw", 32, 256);
	tp.CreateTexture(TELEPHONE_SIDE_1, image, 32, 256);	

	image = tp.LoadTexture((char*)"data/phonefront2.raw", 512, 16);
	tp.CreateTexture(TELEPHONE_FRONT_2, image, 512, 16);	
	
	image = tp.LoadTexture((char*)"data/phonemainside.raw", 512, 256);
	tp.CreateTexture(TELEPHONE_MAIN_SIDE, image, 512, 256);
	
	image = tp.LoadTexture((char*)"data/phonetop1.raw", 512, 128);
	tp.CreateTexture(TELEPHONE_TOP_1, image, 512, 128);

	image = tp.LoadTexture((char*)"data/phoneside2.raw", 16, 256);
	tp.CreateTexture(TELEPHONE_SIDE_2, image, 16, 256);

	image = tp.LoadTexture((char*)"data/phonetop2.raw", 128, 256);
	tp.CreateTexture(TELEPHONE_TOP_2, image, 128, 256);

	image = tp.LoadTexture((char*)"data/phonebottom.raw", 512, 128);
	tp.CreateTexture(TELEPHONE_BOTTOM, image, 512, 128);

	image = tp.LoadTexture((char*)"data/phoneFill.raw", 2, 2);
	tp.CreateTexture(TELEPHONE_FILL, image, 2, 2);

	image = tp.LoadTexture((char*)"data/phonefront3.raw", 16, 512);
	tp.CreateTexture(TELEPHONE_FRONT_3, image, 16, 512);

	image = tp.LoadTexture((char*)"data/PSCsign.raw", 256, 128);
	tp.CreateTexture(PSC_SIGN, image, 256, 128);
	
	image = tp.LoadTexture((char*)"data/PSCsign2.raw", 256, 128);
	tp.CreateTexture(PSC_SIGN_2, image, 256, 128);

	image = tp.LoadTexture((char*)"data/purplepost.raw", 64, 128);
	tp.CreateTexture(PURPLE_POST, image, 64 ,128);
	
	image = tp.LoadTexture((char*)"data/purplepostside.raw", 128, 64);
	tp.CreateTexture(PURPLE_POSTSIDE, image, 128, 64);

	image = tp.LoadTexture((char*)"data/redpost.raw", 64, 128);
	tp.CreateTexture(RED_POST, image, 64 ,128);
	
	image = tp.LoadTexture((char*)"data/redpostside.raw", 64, 64);
	tp.CreateTexture(RED_POSTSIDE, image, 64, 64);

	image = tp.LoadTexture((char*)"data/roofbeam1.raw", 128, 32);
	tp.CreateTexture(ROOF_BEAM_1, image, 128, 32);

	image = tp.LoadTexture((char*)"data/roofbeam2.raw", 32, 128);
	tp.CreateTexture(ROOF_BEAM_2, image, 32, 128);

	image = tp.LoadTexture((char*)"data/roofbeam3.raw", 64, 128);
	tp.CreateTexture(ROOF_BEAM_3, image, 64, 128);

	image = tp.LoadTexture((char*)"data/roofbeam3top.raw", 128, 128);
	tp.CreateTexture(ROOF_BEAM_3_TOP, image, 128, 128);

	image = tp.LoadTexture((char*)"data/roofbeam4.raw", 128, 64);
	tp.CreateTexture(ROOF_BEAM_4, image, 128, 64);

	image = tp.LoadTexture((char*)"data/roofPlanks.raw", 128, 128);
	tp.CreateTexture(ROOF_PLANKS, image, 128, 128);

	image = tp.LoadTexture((char*)"data/roofPlanks2.raw", 128, 128);
	tp.CreateTexture(ROOF_PLANKS_2, image, 128, 128);

	image = tp.LoadTexture((char*)"data/rooftop.raw", 2, 128);
	tp.CreateTexture(ROOF_TOP, image, 2, 128);

	image = tp.LoadTexture((char*)"data/rooftoplib.raw", 128, 2);
	tp.CreateTexture(ROOF_TOP_LIB, image, 128, 2);

	image = tp.LoadTexture((char*)"data/rustyman.raw", 256, 1024);
	tp.CreateTexture(RUSTY_MAN, image, 256, 1024);

	image = tp.LoadTexture((char*)"data/securitysign1.raw", 128, 128);
	tp.CreateTexture(SECURITY_SIGN, image, 128, 128);

	image = tp.LoadTexture((char*)"data/securitysign2.raw", 128, 128);
	tp.CreateTexture(SECURITY_SIGN_2, image, 128, 128);

	image = tp.LoadTexture((char*)"data/sign1.raw", 512, 256);
	tp.CreateTexture(SIGN_1, image, 512, 256);
	
	image = tp.LoadTexture((char*)"data/sign1side1.raw", 16, 512);
	tp.CreateTexture(SIGN_1_SIDE_1, image, 16, 512);

	image = tp.LoadTexture((char*)"data/sign1side2.raw", 16, 512);
	tp.CreateTexture(SIGN_1_SIDE_2, image, 16, 512);

	image = tp.LoadTexture((char*)"data/sign2.raw", 512, 512);
	tp.CreateTexture(SIGN_2, image, 512, 512);

	image = tp.LoadTexture((char*)"data/sign2side.raw", 512, 16);
	tp.CreateTexture(SIGN_2_SIDE, image, 512, 16);

	image = tp.LoadTexture((char*)"data/statravel.raw", 256, 256);
	tp.CreateTexture(STA_TRAVEL, image, 256, 256);

	image = tp.LoadTexture((char*)"data/statraveledge.raw", 256, 64);
	tp.CreateTexture(STA_TRAVEL_EDGE, image, 256, 64);

	image = tp.LoadTexture((char*)"data/statravelbracket.raw", 16, 2);
	tp.CreateTexture(STA_TRAVEL_BRACKET, image, 16, 2);

	image = tp.LoadTexture((char*)"data/statravel2.raw", 256, 256);
	tp.CreateTexture(STA_TRAVEL_2, image, 256, 256);

	image = tp.LoadTexture((char*)"data/statravelbottom.raw", 2, 64);
	tp.CreateTexture(STA_TRAVEL_BOTTOM, image, 2, 64);

	image = tp.LoadTexture((char*)"data/stepbricks.raw", 128, 128);
	tp.CreateTexture(WALL_BRICK_STEPS, image, 128, 128);

	image = tp.LoadTexture((char*)"data/stepbrickscover.raw", 64, 128);
	tp.CreateTexture(WALL_BRICK_STEPS_COVER, image, 64, 128);

	image = tp.LoadTexture((char*)"data/stepbricksedge.raw", 64, 32);
	tp.CreateTexture(WALL_BRICK_STEPS_EDGE, image, 64, 32);
	
	image = tp.LoadTexture((char*)"data/stepbricksedge2.raw", 64, 64);
	tp.CreateTexture(WALL_BRICK_STEPS_EDGE_2, image, 64, 64);

	image = tp.LoadTexture((char*)"data/stepbrickstop.raw", 32, 128);
	tp.CreateTexture(WALL_BRICK_STEPS_TOP, image, 32, 128);

	image = tp.LoadTexture((char*)"data/stepslibrary.raw", 128, 1024);
	tp.CreateTexture(STEPS_LIBRARY, image, 128, 1024);
	
	image = tp.LoadTexture((char*)"data/stepslibrarytop.raw", 256, 1024);
	tp.CreateTexture(STEPS_LIBRARY_TOP, image, 256, 1024);

	image = tp.LoadTexture((char*)"data/steppaving1.raw", 1024, 512);
	tp.CreateTexture(STEP_PAVING_1, image, 1024, 512);

	image = tp.LoadTexture((char*)"data/steppavingedge.raw", 64, 64);
	tp.CreateTexture(STEP_EDGE, image, 64, 64);

	image = tp.LoadTexture((char*)"data/sweetMachine.raw", 256, 256);
	tp.CreateTexture(SWEET_MACHINE, image, 256, 256);

	image = tp.LoadTexture((char*)"data/telephoneback.raw", 512, 512);
	tp.CreateTexture(TELEPHONE_BACK, image, 512, 512);

	image = tp.LoadTexture((char*)"data/ticketcounteredge2.raw", 64, 64);
	tp.CreateTexture(TICKET_COUNTER_EDGE_2, image, 64, 64);

	image = tp.LoadTexture((char*)"data/ticketcounteredge3.raw", 64, 64);
	tp.CreateTexture(TICKET_COUNTER_EDGE_3, image, 64, 64);

	image = tp.LoadTexture((char*)"data/ticketcountertop.raw", 128, 256);
	tp.CreateTexture(TICKET_COUNTER_TOP, image, 128, 256);

	image = tp.LoadTexture((char*)"data/ticketledgeedge.raw", 2, 32);
	tp.CreateTexture(TICKET_LEDGE_EDGE, image, 2, 32);

	image = tp.LoadTexture((char*)"data/ticketledge.raw", 2, 128);
	tp.CreateTexture(TICKET_LEDGE, image, 2, 128);

	image = tp.LoadTexture((char*)"data/ticketledgeedge2.raw", 32, 2);
	tp.CreateTexture(TICKET_LEDGE_EDGE_2, image, 32, 2);

	image = tp.LoadTexture((char*)"data/ticketcounteredge.raw", 128, 32);
	tp.CreateTexture(TICKET_COUNTER_EDGE, image, 128, 32);

	image = tp.LoadTexture((char*)"data/toiletdoortop.raw", 32, 256);
	tp.CreateTexture(TOILET_DOOR_TOP, image, 32, 256);

	image = tp.LoadTexture((char*)"data/toiletmen.raw", 128, 128);
	tp.CreateTexture(TOILET_MEN, image, 128, 128);

	image = tp.LoadTexture((char*)"data/toiletwomen.raw", 128, 128);
	tp.CreateTexture(TOILET_WOMEN, image, 128, 128);

	image = tp.LoadTexture((char*)"data/wallgap1.raw", 8, 128);
	tp.CreateTexture(WALL_GAP_1, image, 8, 128);

	image = tp.LoadTexture((char*)"data/windowledge1.raw", 32, 1024);
	tp.CreateTexture(WINDOWLEDGE_CHANC_FRONT, image, 32, 1024);

	image = tp.LoadTexture((char*)"data/windowledge2.raw", 128, 1024);
	tp.CreateTexture(WINDOWLEDGE_CHANC_TOP, image, 128, 1024);

	image = tp.LoadTexture((char*)"data/windowledgeend.raw", 32, 64);
	tp.CreateTexture(WINDOW_LEDGE_END_1, image, 32, 64);

	image = tp.LoadTexture((char*)"data/windowledgeend2.raw", 64, 64);
	tp.CreateTexture(WINDOW_LEDGE_END_2, image, 64, 64);

	image = tp.LoadTexture((char*)"data/windowledgeLibfa.raw", 1024, 32);
	tp.CreateTexture(WINDOWLEDGE_LIB_A, image, 1024, 32);

	image = tp.LoadTexture((char*)"data/windowledgeLibfb.raw", 1024, 32);
	tp.CreateTexture(WINDOWLEDGE_LIB_B, image, 1024, 32);


	image = tp.LoadTexture((char*)"data/windowledgeLibta.raw", 1024, 128);
	tp.CreateTexture(WINDOWLEDGE_LIB_TOP_A, image, 1024, 128);

	image = tp.LoadTexture((char*)"data/windowledgeLibtb.raw", 1024, 128);
	tp.CreateTexture(WINDOWLEDGE_LIB_TOP_B, image, 1024, 128);

	image = tp.LoadTexture((char*)"data/windowledgeUS1.raw", 32, 1024);
	tp.CreateTexture(WINDOWLEDGE_PS_FRONT, image, 32, 1024);

	image = tp.LoadTexture((char*)"data/windowledgeUS2.raw", 128, 1024);
	tp.CreateTexture(WINDOWLEDGE_PS_TOP, image, 128, 1024);

	image = tp.LoadTexture((char*)"data/windowledgeUS3.raw", 128, 1024);
	tp.CreateTexture(WINDOWLEDGE_PS_BOTT, image, 128, 1024);

	image = tp.LoadTexture((char*)"data/windowpost1.raw", 1024, 128);
	tp.CreateTexture(WINDOWPOST_CHANC_FRONT, image, 1024, 128);

	image = tp.LoadTexture((char*)"data/windowpostsmall.raw", 512, 128);
	tp.CreateTexture(WINDOWPOST_PHYSSCI_FRONT, image, 512, 128);

	image = tp.LoadTexture((char*)"data/windowpostsmallside2.raw", 64, 512);
	tp.CreateTexture(WINDOWPOST_PHYSSCI_RIGHT, image, 64, 512);

	image = tp.LoadTexture((char*)"data/windowpostsmallside.raw", 64, 512);
	tp.CreateTexture(WINDOWPOST_PHYSSCI_LEFT, image, 64, 512);
	
	image = tp.LoadTexture((char*)"data/windowpostLib.raw", 128, 512);
	tp.CreateTexture(WINDOWPOST_LIB_FRONT, image, 128, 512);

	image = tp.LoadTexture((char*)"data/windowpostLibside1.raw", 512, 64);
	tp.CreateTexture(WINDOWPOST_LIB_LEFT, image, 512, 64);

	image = tp.LoadTexture((char*)"data/windowpostLibside2.raw", 512, 64);
	tp.CreateTexture(WINDOWPOST_LIB_RIGHT, image, 512, 64);

	image = tp.LoadTexture((char*)"data/windowposthalf1.raw", 64, 1024);
	tp.CreateTexture(WINDOWPOST_CHANC_RIGHT, image, 64, 1024);
	
	image = tp.LoadTexture((char*)"data/windowposthalf2.raw", 64, 1024);
	tp.CreateTexture(WINDOWPOST_CHANC_LEFT, image, 64, 1024);

	// Larger Textures

	image = tp.LoadTexture((char*)"data/windows/stepwindow.raw", 128, 256);
	tp.CreateTexture(STEP_WINDOW, image, 128, 256);
	
	image = tp.LoadTexture((char*)"data/windows/chancDoor1.raw", 256, 256);
	tp.CreateTexture(CHANC_DOOR_1, image, 256, 256);

	image = tp.LoadTexture((char*)"data/windows/chancDoor2.raw", 256, 256);
	tp.CreateTexture(CHANC_DOOR_2, image, 256, 256);

	image = tp.LoadTexture((char*)"data/windows/entrance.raw", 512, 256);
	tp.CreateTexture(ENTRANCE, image, 512, 256);

	image = tp.LoadTexture((char*)"data/windows/entrance2.raw",512, 512);
	tp.CreateTexture(ENTRANCE_2, image, 512, 512);
	
	image = tp.LoadTexture((char*)"data/windows/exiteast.raw", 512, 512);
	tp.CreateTexture(EXIT_EAST, image, 512, 512);

	image = tp.LoadTexture((char*)"data/windows/exitwest.raw", 256, 512);
	tp.CreateTexture(EXIT_WEST, image, 256, 512);

	image = tp.LoadTexture((char*)"data/windows/window1.raw", 256, 256);
	tp.CreateTexture(WINDOW_1, image, 256, 256);

	image = tp.LoadTexture((char*)"data/windows/window1b.raw", 256, 256);
	tp.CreateTexture(WINDOW_1B, image, 256, 256);

	image = tp.LoadTexture((char*)"data/windows/window2.raw", 256, 256);
	tp.CreateTexture(WINDOW_2, image, 256, 256);

	image = tp.LoadTexture((char*)"data/windows/window2b.raw", 256, 256);
	tp.CreateTexture(WINDOW_2B, image, 256, 256);

	image = tp.LoadTexture((char*)"data/windows/window2c.raw", 256, 256);
	tp.CreateTexture(WINDOW_2C, image, 256, 256);
	
	image = tp.LoadTexture((char*)"data/windows/window2d.raw", 256, 256);
	tp.CreateTexture(WINDOW_2D, image, 256, 256);

	image = tp.LoadTexture((char*)"data/windows/window2e.raw", 256, 256);
	tp.CreateTexture(WINDOW_2E, image, 256, 256);

	image = tp.LoadTexture((char*)"data/windows/window2us.raw", 256, 256);
	tp.CreateTexture(WINDOW_2US, image, 256, 256);

	image = tp.LoadTexture((char*)"data/windows/window2usb.raw", 256, 256);
	tp.CreateTexture(WINDOW_2USB, image, 256, 256);

	image = tp.LoadTexture((char*)"data/windows/window3.raw", 256, 256);
	tp.CreateTexture(WINDOW_3, image, 256, 256);

	image = tp.LoadTexture((char*)"data/windows/window3b.raw", 256, 256);
	tp.CreateTexture(WINDOW_3B, image, 256, 256);
	
	image = tp.LoadTexture((char*)"data/windows/window4.raw", 128, 256);
	tp.CreateTexture(WINDOW_4, image, 128, 256);
	
	image = tp.LoadTexture((char*)"data/windows/window5.raw", 128, 256);
	tp.CreateTexture(WINDOW_5, image, 128, 256);

	image = tp.LoadTexture((char*)"data/windows/window6.raw", 256, 256);
	tp.CreateTexture(WINDOW_6, image, 256, 256);

	image = tp.LoadTexture((char*)"data/windows/window7.raw", 256, 256);
	tp.CreateTexture(WINDOW_7, image, 256, 256);

	image = tp.LoadTexture((char*)"data/windows/window8.raw", 256, 256);
	tp.CreateTexture(WINDOW_8, image, 256, 256);

	image = tp.LoadTexture((char*)"data/windows/window9.raw", 256, 256);
	tp.CreateTexture(WINDOW_9, image, 256, 256);

	image = tp.LoadTexture((char*)"data/windows/window10.raw", 256, 256);
	tp.CreateTexture(WINDOW_10, image, 256, 256);

	image = tp.LoadTexture((char*)"data/windows/window11.raw", 256, 256);
	tp.CreateTexture(WINDOW_11, image, 256, 256);

	image = tp.LoadTexture((char*)"data/windows/window12.raw", 256, 256);
	tp.CreateTexture(WINDOW_12, image, 256, 256);

	image = tp.LoadTexture((char*)"data/windows/window13.raw", 256, 256);
	tp.CreateTexture(WINDOW_13, image, 256, 256);

	image = tp.LoadTexture((char*)"data/windows/window14.raw", 256, 128);
	tp.CreateTexture(WINDOW_14, image, 256, 128);

	image = tp.LoadTexture((char*)"data/windows/window14b.raw", 256, 128);
	tp.CreateTexture(WINDOW_14B, image, 256, 128);

	image = tp.LoadTexture((char*)"data/windows/window15.raw", 256, 256);
	tp.CreateTexture(WINDOW_15, image, 256, 256);

	image = tp.LoadTexture((char*)"data/windows/window16.raw", 128, 256);
	tp.CreateTexture(WINDOW_16, image, 128, 256);

	image = tp.LoadTexture((char*)"data/windows/window17.raw", 128, 256);
	tp.CreateTexture(WINDOW_17, image, 128, 256);

	image = tp.LoadTexture((char*)"data/windows/windowLib1.raw", 256, 128);
	tp.CreateTexture(WINDOW_LIB_1, image, 256, 128);
	
	image = tp.LoadTexture((char*)"data/windows/windowLib1a.raw", 256, 128);
	tp.CreateTexture(WINDOW_LIB_1A, image, 256, 128);

	image = tp.LoadTexture((char*)"data/windows/windowLib1b.raw", 256, 128);
	tp.CreateTexture(WINDOW_LIB_1B, image, 256, 128);

	image = tp.LoadTexture((char*)"data/windows/windowLib1c.raw", 256, 128);
	tp.CreateTexture(WINDOW_LIB_1C, image, 256, 128);

	image = tp.LoadTexture((char*)"data/windows/windowLibUSa.raw", 256, 128);
	tp.CreateTexture(WINDOW_LIB_US_A, image, 256, 128);

	image = tp.LoadTexture((char*)"data/windows/windowLibUSb.raw", 256, 128);
	tp.CreateTexture(WINDOW_LIB_US_B, image, 256, 128);

	image = tp.LoadTexture((char*)"data/windows/windowLibDoor1.raw", 256, 256);
	tp.CreateTexture(WINDOW_LIB_DOOR_1, image, 256, 256);

	image = tp.LoadTexture((char*)"data/windows/windowLibDoor2.raw", 512, 256);
	tp.CreateTexture(WINDOW_LIB_DOOR_2, image, 512, 256);
	
	image = tp.LoadTexture((char*)"data/windows/windowLibLong.raw", 256, 128);
	tp.CreateTexture(WINDOW_LIB_LONG, image, 256, 128);

	image = tp.LoadTexture((char*)"data/map.raw", 256, 256);
	tp.CreateTexture(217, image, 256, 256);
	image = tp.LoadTexture((char*)"data/welcome.raw", 512, 512);
	tp.CreateTexture(218, image, 512, 512);
	image = tp.LoadTexture((char*)"data/thanks.raw", 512, 512);
	tp.CreateTexture(219, image, 512, 512);


	// Tutorial 1 Banner creation
	image = tp.LoadTexture((char*)"data/bannerlossy.raw", 1600, 1066);
	tp.CreateTexture(THE_BANNER, image, 1600, 1066);

	// Boardwalk Step XY
	image = tp.LoadTexture((char*)"data/boardwalk440StepXY.raw", 64, 128);
	tp.CreateTexture(BOARDWALK_440_STEP_XY, image, 64, 128);

	// Boardwalk Step XY
	image = tp.LoadTexture((char*)"data/boardwalk440StepYZ.raw", 128, 64);
	tp.CreateTexture(BOARDWALK_440_STEP_XY, image, 128, 64);

	// Boardwalk Step TopStripe XY
	image = tp.LoadTexture((char*)"data/boardwalk440StepXY_TopStripe.raw", 64, 32);
	tp.CreateTexture(BOARDWALK_440_STEPTOPSTRIPE_XY, image, 64, 32);
	
	// Boardwalk Step TopStripe YZ
	image = tp.LoadTexture((char*)"data/boardwalk440StepYZ_TopStripe.raw", 32, 64);
	tp.CreateTexture(BOARDWALK_440_STEPTOPSTRIPE_XY, image, 32, 64);

	// Boardwalk 1m Door West XY
	image = tp.LoadTexture((char*)"data/boardwalk440DoorWestXY.raw", 320, 640);
	tp.CreateTexture(BOARDWALK_440_1M_DOOR_XY, image, 320, 640);
	
	// Boardwalk 1m Door West YZ
	image = tp.LoadTexture((char*)"data/Boardwalk440DoorWestYZ.raw", 640, 320);
	tp.CreateTexture(BOARDWALK_440_1M_DOOR_YZ, image, 640, 320);

	//440 north windows
	image = tp.LoadTexture((char*)"data/440window.raw", 460, 640);
	tp.CreateTexture(BOARDWALK_440_WINDOW, image, 460, 640);

	//Bookshop door
	image = tp.LoadTexture((char*)"data/BookshopDoor.raw", 320, 320);
	tp.CreateTexture(BOOKSHOP_DOOR, image, 320, 320);
	
	//Bookshop window 1
	image = tp.LoadTexture((char*)"data/BookshopWindow1.raw", 320, 320);
	tp.CreateTexture(BOOKSHOP_WINDOW_1, image, 320, 320);

	//Bookshop window 2
	image = tp.LoadTexture((char*)"data/BookshopWindow2.raw", 320, 320);
	tp.CreateTexture(BOOKSHOP_WINDOW_2, image, 320, 320);

	//Bookshop window 3
	image = tp.LoadTexture((char*)"data/BookshopWindow3.raw", 320, 320);
	tp.CreateTexture(BOOKSHOP_WINDOW_3, image, 320, 320);

	image = tp.LoadTexture((char*)"data/portal.raw", 128, 128);
	tp.CreateTexture(234, image, 128, 128);

	image = tp.LoadTexture((char*)"data/Statue.raw", 1024, 1024);
	tp.CreateTexture(235, image, 1024, 1024);


	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

//--------------------------------------------------------------------------------------
//  Called from the main display function to draw the backdrop (all images)
//--------------------------------------------------------------------------------------
void Shay::DrawBackdrop()
{
	DisplayAboveWindowBlock ();
	DisplayBench ();
	DisplayBricks ();
	DisplayChancPosts ();
	DisplayCylinders ();
	DisplayDoorPaving ();
	DisplayDoorPosts ();
	DisplayEntranceSteps ();
	DisplayExtras ();
	DisplayGrass ();
	DisplayLargerTextures ();
	DisplayLibraryPosts ();
	DisplayMainPosts ();
	DisplayPavement ();
	DisplayPhysSciPosts ();
	DisplayPurplePosts ();
	DisplayRedPosts ();
	DisplayRoof();
	DisplayStepBricks ();

	DisplayBanner();

	DisplayBoardWalkGarden();
	DisplayBoardwalk440WestPaving();
	DisplayBoardwalk440SouthPaving();
	DisplayBoardwalk440EastPaving();
	DisplayBoardwalk440NorthWall();
	DisplayBoardwalk440SouthWall();
	DisplayBoardwalk440EastWall();
	DisplayBoardwalk440WestWall();
	DisplayBoardwalk440SouthPosts();
	DisplayBoardwalk440WestPosts();
	DisplayBoardwalk440EastPosts();
	DisplayBoardwalk440SouthBeams();
	DisplayBoardwalk440WestBeams();
	DisplayBoardwalk440EastBeams();
	DisplayBoardwalk440SouthLintels();
	DisplayBoardwalk440EastLintels();
	DisplayBoardwalk440WestLintels();
	DisplayBoardwalk440SouthCeiling();
	DisplayBoardwalk440WestCeiling();
	DisplayBoardwalk440EastCeiling();
	DisplayBoardwalk440SouthWallFacade();
	DisplayBoardwalk440EastFacade();
	DisplayBoardwalk440WestFacade();
	DisplayBoardwalk440CorridorWallEast();
	DisplayBoardwalk440CorridorWallWest();

	DisplayBoardwalk440WestFacadeLedge();
	DisplayBoardwalk440EastFacadeLedge();

	Display440BoardwalkEastSteps();
	Display440BoardwalkWestSteps();

	DisplayBoardwalk440EastStairwell();
	DisplayBoardwalk440WestStairwell();

	DisplayBWRoofEast();
	DisplayBWRoofWest();
	DisplayBWRoofSouth();

	Display440RoofNorth();
	Display440NorthExterior();
	Display440NorthWindows();

	DisplayBoardwalk440WestDoors();
	DisplayBoardwalk440EastDoors();
	DisplayBroadwalkSouthDoors();

	Display440EastUpperWall();
	Display440WestUpperWall();

	DisplayBoardwalk440WestPavingStairwell();
	DisplayBoardwalk440EastPavingStairwell();

	DisplayBoardwalk440WestLandingStairwell();
	DisplayBoardwalk440EastLandingStairwell();

	if (lightsOn) 
		DisplayLights ();
}

//--------------------------------------------------------------------------------------
// Display the chancellery windoe and door posts
//--------------------------------------------------------------------------------------
void Shay::DisplayChancPosts ()
{
	// Windowposts Chanc (downstairs)
	step = 0.0;
	for (int i = 0; i < 14; i++)
	{
		glPushMatrix();
			glTranslatef(0.0, 0.0, step);
			if ((i != 1) && (i != 2) && (i != 10) && (i != 11))
			{			
				glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_CHANC_FRONT));
				glCallList(11);
			}
			if ((i != 1) && (i != 10))
			{			
				glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_CHANC_RIGHT));
				glCallList(12);
			}
			if ((i != 2) && (i != 11))
			{
				glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_CHANC_LEFT));
				glCallList(13);
			}
				
		glPopMatrix();		
		step += 960.0;
	}

	//  Windowledges Chanc (downstairs)
	step = 0.0;
	for (i = 0; i < 11; i++)
	{
		glPushMatrix();
			glTranslatef(0.0, 0.0, step);
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_CHANC_FRONT));
			glCallList(14);
		
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_CHANC_TOP));
			glCallList(15);		
		glPopMatrix();
		if ((i == 0) || (i == 8)) step += 960.0;
		step += 960.0;
	}

	// Windowposts & Ledges Chanc (upstairs)
	glPushMatrix();
	step = 0.0;
	glTranslatef(0.0, 1023.0, 0.0);
	for (i = 0; i < 14; i++)
	{
		glTranslatef(0.0, 0.0, step);
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_CHANC_FRONT));
		glCallList(11);
			
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_CHANC_RIGHT));
		glCallList(12);
	
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_CHANC_LEFT));
		glCallList(13);
		if (i != 13)
		{
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_CHANC_FRONT));
			glCallList(14);
		
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_CHANC_TOP));
			glCallList(15);
		}
		step =+ 960.0;
	}
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_LEDGE_END_1));
	glCallList(235);
	glPushMatrix();
		glTranslatef(0.0, 320.0, 7447.0);
		glCallList(235);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 1024.0, 0.0);
		glCallList(235); 
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 320.0, 8471);
		glCallList(235);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 1152.0, 19031.0);
		glCallList(235);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_LEDGE_END_2));
	glCallList(236);
	glCallList(237);
	glPushMatrix();
		glTranslatef(0.0, 0.0, -960.0);
		glCallList(237);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 0.0, -8640.0);
		glCallList(237);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 0.0, -9600.0);
		glCallList(237);
	glPopMatrix();

	//glPushMatrix();
		//glTranslatef(0.0, 320.0, -9600.0);
		//glCallList(237);
//	glPopMatrix();

	// angled corner of window ledges
	glPushMatrix();
		glTranslatef(0.0, 1024.0, 0.0);
		glCallList(236);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 320.0, 7383.0);
		glCallList(236);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 320.0, 5463);
		glCallList(236);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 320.0, 6551);
		glCallList(236);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 320.0, 8471);
		glCallList(236);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 1152.0, 19031.0);
		glCallList(236);
	glPopMatrix();
}

void Shay::DrawChancPosts ()
{
	// Front of Window Post Chanc
	tp.CreateDisplayList (YZ, 11, 1024.0, 128.0, 33848.0, 10237.0, 9505.0, 0.586, 0.7344);
	// Right side of Window Post Chanc
	tp.CreateDisplayList (XY,  12, 64.0, 1024.0, 33848.0, 10237.0, 9599, 0.7344, 0.585);
	// Left side of Window Post Chanc
	tp.CreateDisplayList (XY,  13, 64.0, 1024.0, 33848.0, 10237.0, 9505.0, 0.7344, 0.585);

	// Window ledges of Chanc
	tp.CreateDisplayList (YZ, 14, 32.0, 1024.0, 33808.0, 10192.0, 9552.0, 1.0, 0.9375); // front ledge
	glNewList(15, GL_COMPILE); 
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(33808.0, 10224.0, 9552.0);
			glTexCoord2f(0.0, 0.9375);
			glVertex3f(33808.0, 10224.0, 9552.0 + (1024.0 * 0.9375));
			glTexCoord2f(1.0, 0.9375);
			glVertex3f(33928.0, 10268.0, 9552.0 + (1024.0 * 0.9375));
			glTexCoord2f(1.0, 0.0);
			glVertex3f(33928.0, 10268.0, 9552.0);
		glEnd();
	glEndList();
	tp.CreateDisplayList (YZ, 235, 32.0, 64.0, 33808.0, 10192.0, 22032.0, 1.0, 1.0); // front ledge
	tp.CreateDisplayList (XY, 236, 64.0, 64.0, 33808.0, 10192.0, 22096.0, 1.35, 0.5); // front ledge

	// Window Edges
	glNewList(237, GL_COMPILE); 
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(33808.0, 10225.0, 20112.0);
			glTexCoord2f(0.0, 0.5);
			glVertex3f(33808.0, 10192.0, 20112.0);
			glTexCoord2f(0.5, 0.5);
			glVertex3f(33872.0, 10192.0, 20112.0);
			glTexCoord2f(0.5, 0.0);
			glVertex3f(33872.0, 10247.0, 20112.0);
		glEnd();
	glEndList();


}

//--------------------------------------------------------------------------------------
// Display Door Posts
//--------------------------------------------------------------------------------------
void Shay::DisplayDoorPosts ()
{
	// Door Posts Chanc
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DOOR_POST_SECURITY));
	glCallList(199);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DOOR_POST_CHANC));	
	glPushMatrix();
		glTranslatef(0.0, 0.0, 8640.0);
		glCallList(25);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DOOR_POST_CHANC));
	glCallList(26);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 8640.0);				
		glCallList(26);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DOOR_SIDEPOST_CHANC));	
	glCallList(27);
	glPushMatrix();
		glTranslatef(0.0, 0.0, 866.0);
		glCallList(27);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 0.0, 8640.0);
		glCallList(27);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 0.0, 9506.0);
		glCallList(27);
	glPopMatrix();
}

void Shay::DrawDoorPosts ()
{
	// DOORPOSTS_CHANC
	tp.CreateDisplayList (YZ_FLIP, 25, 1024.0, 128.0, 33848.0, 10000.0, 10465.0, 0.83, 0.7344);	// post
	tp.CreateDisplayList (YZ, 26, 1024.0, 128.0, 33848.0, 10000.0, 11425.0, 0.83, 0.7344);
	tp.CreateDisplayList (XY, 27, 64.0, 1024.0, 33848.0, 10000.0, 10559.0, 1.0, 1.0);	// sidepost
	tp.CreateDisplayList (YZ_FLIP, 199, 1024.0, 128.0, 33848.0, 10000.0, 10465.0, 0.83, 0.7344);	// post
}

//--------------------------------------------------------------------------------------
// Display blocks above Windows and Posts
//--------------------------------------------------------------------------------------
void Shay::DisplayAboveWindowBlock ()
{
	// Blocks Above Windows Chanc & Phys Sci
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_WINDOW_BLOCK));
	glCallList(20);
	glCallList(223);
	glCallList(229);
	// Blocks containing text 
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_CHANC_TEXT));
	glCallList(224);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_CHANC_TEXT_2));
	glCallList(225);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_CHANC_TEXT_3));
	glCallList(230);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_PHYS_SCI_TEXT));
	glCallList(226);
	glPushMatrix();	
		glTranslatef(0.0, 0.0, 9728.0);
		glCallList(226);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_WINDOW_BLOCK_2));
	glCallList(44);
	glCallList(46);
	glCallList(96);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_WINDOW_BLOCK_CHANC));
	glCallList(22);
	glPushMatrix();	
		glTranslatef(0.0, 1024.0, 0.0);
		glCallList(22);
	glPopMatrix();
	glCallList(24);
	glPushMatrix();	
		glTranslatef(0.0, 1024.0, 0.0);
		glCallList(24);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_WINDOW_BLOCK_3));
	glCallList(227);
	glCallList(228);
	glCallList(21);
	glCallList(23);
	glCallList(95);
	glPushMatrix();	
		glTranslatef(99.84, 0.0, 0.0);
		glCallList(95);
	glPopMatrix();
	glCallList(231);
	glCallList(43);
	glCallList(45);
	glCallList(53);	// aboves posts
	glPushMatrix();	
		glTranslatef(128.0, 0.0, 0.0);
		glCallList(53);
	glPopMatrix();
	glCallList(68);
	glCallList(71);	// above post between chanc and phys sci

	glCallList(213);
	glPushMatrix();
		glTranslatef(0.0, 1024.0, 0.0);
		glCallList(213);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_WINDOW_EDGE_3B));
	glCallList(49);
	glPushMatrix();	
		glTranslatef(0.0, 1024.0, 0.0);
		glCallList(49);
	glPopMatrix();
	glPushMatrix();	
		glTranslatef(0.0, 1024.0, 15783.0);
		glCallList(49);
	glPopMatrix();
	glPushMatrix();	
		glTranslatef(-2068.0, 310.0, -17244.0);
		glCallList(49);
	glPopMatrix();
	glCallList(425);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_WINDOW_BLOCK_XY_3));
		glCallList(50);
	glPushMatrix();	
		glTranslatef(0.0, 0.0, 807.0);
		glCallList(50);
	glPopMatrix();
	glPushMatrix();	
		glTranslatef(0.0, 0.0, 9567.0);
		glCallList(50);
	glPopMatrix();
	glPushMatrix();	
		glTranslatef(0.0, 0.0, 11103.0);
		glCallList(50);
	glPopMatrix();
	for (int i = 64; i < 67; i++) glCallList(i);
	glPushMatrix();
		glTranslatef(0.0, 0.0, 128.0);
		glCallList(66);
	glPopMatrix();
	glCallList(208);
	glCallList(233);
	glCallList(234);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_UNDER_POSTS));
	glCallList(54);
	glCallList(67);
	glCallList(72);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BELOW_ROOF_FILL));
	glCallList(39);

	// -------------------------------- Above under Mainpost by Library -----------------------
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_UNDER_POSTS_2));
	glCallList(69);
	glCallList(232);

	// -------------------------------- Above Library ------------------------------------
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_LIB));
	for (i = 55; i < 57; i ++) glCallList(i);
	glCallList(238);
	glCallList(415);
	glCallList(417);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_WINDOW_UNDER_LIB));
	for (i = 70; i < 71; i ++) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_WINDOW_EDGE_3B_LIB));
	glCallList(209);
	step = 17536.0;
	for (i = 0; i < 2; i++)
	{
		glPushMatrix();
			glTranslatef(step, 0.0, 0.0);
			glCallList(209);
		glPopMatrix();
		step += 128.0;
	}

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_WINDOW_EDGE_4B_LIB));
	glCallList(210);
	step = 17536.0;
	for (i = 0; i < 2; i++)
	{
		glPushMatrix();
			glTranslatef(step, 0.0, 0.0);
			glCallList(210);
		glPopMatrix();
		step += 128.0;
	}

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_UNDER_4B));
	for (i = 211; i < 213; i++) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_LIB_TEXT));
	glCallList(239);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_LIB_TEXT_2));
	glCallList(416);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_TICKETS_TEXT));
	glCallList(418);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_CHANC_EDGE));
	glCallList(424);

}

void Shay::DrawAboveWindowBlock ()
{
	tp.CreateDisplayList (YZ, 20, 128.0, 256.0, 33808.0, 10832.0, 9552.0, 1.0, 4.0);		// chanc above bottom window
	tp.CreateDisplayList (YZ, 223, 128.0, 256.0, 33808.0, 10832.0, 11600.0, 1.0, 30.0);		// chanc above bottom window
	tp.CreateDisplayList (YZ, 229, 128.0, 256.0, 33808.0, 10832.0, 20304.0, 1.0, 3.0);		// chanc above bottom window
	tp.CreateDisplayList (YZ, 230, 128.0, 1024.0, 33808.0, 10832.0, 19280.0, 1.0, 1.0);		// chanc above bottom window
	tp.CreateDisplayList (YZ, 224, 128.0, 1024.0, 33808.0, 10832.0, 10576.0, 1.0, 1.0);		// chanc above bottom window
	tp.CreateDisplayList (YZ, 225, 128.0, 1024.0, 33808.0, 10832.0, 21072.0, 1.0, 1.0);		// chanc above bottom window
	tp.CreateDisplayList (XY, 424, 128.0, 128.0, 33808.0, 10832.0, 22096.0, 0.68, 1.0);		// chanc end edge downstairs
	tp.CreateDisplayList (XY, 425, 128.0, 256.0, 33808.0, 11856.0, 22096.0, 0.68, 0.5625);	// 3 bricks high to edge


	tp.CreateDisplayList (YZ, 21, 256.0, 256.0, 33808.0, 11856.0, 9552.0, 0.56, 49.0);		// chanc above top window chanc
	tp.CreateDisplayList (XZ, 22, 128.0, 256.0, 33808.0, 10832.0, 9552.0, 0.70, 49.0);		// chanc above under bottom window chanc
	
	tp.CreateDisplayList (YZ, 23, 256.0, 256.0, 33808.0, 10832.0, 25344.0, 0.75, 5.0);		// phys sci above bottom window
	tp.CreateDisplayList (YZ, 231, 256.0, 256.0, 33808.0, 11856.0, 25344.0, 0.75, 61.652);	// phys sci above bottom window

	tp.CreateDisplayList (YZ, 226, 256.0, 1024.0, 33808.0, 10832.0, 26624.0, 0.75, 1.0);	// phys sci text
	tp.CreateDisplayList (YZ, 227, 256.0, 256.0, 33808.0, 10832.0, 27648.0, 0.75, 34.0);	// phys sci above bottom window
	tp.CreateDisplayList (YZ, 228, 256.0, 256.0, 33808.0, 10832.0, 37376.0, 0.75, 14.652);	// phys sci above bottom window
	tp.CreateDisplayList (XZ, 24, 128.0, 256.0, 33808.0, 10832.0, 25344.0, 0.78, 61.652);	// phys sci above under bottom window
	
	tp.CreateDisplayList (YZ, 95, 256.0, 256.0, 33835.0, 11856.0, 41127.0, 1.0, 7.6);		// phys sci above top window
	tp.CreateDisplayList (XZ, 96, 128.0, 256.0, 33835.0, 11856.0, 41127.0, 0.78, 7.6);		// phys sci above under bottom

	tp.CreateDisplayList (YZ, 43, 256.0, 256.0, 34256.0, 10832.0, 26752.0, 0.75, 3.25);		// phys sci above 1st door
	tp.CreateDisplayList (XZ, 44, 128.0, 256.0, 34256.0, 10832.0, 26752.0, 0.70, 2.25);		// phys sci above under 1st door
	tp.CreateDisplayList (YZ, 45, 256.0, 256.0, 34256.0, 10832.0, 36319.0, 0.75, 6.125);	// phys sci above 2nd door
	tp.CreateDisplayList (XZ, 46, 128.0, 256.0, 34256.0, 10832.0, 36319.0, 0.70, 6.125);	// phys sci above under 2nd door

	tp.CreateDisplayList (YZ, 53, 256.0, 256.0, 31740.0, 11142.0, 8100.0, 0.75, 128.955);	// above posts chanc and canteen sides
	tp.CreateDisplayList (XZ, 54, 128.0, 256.0, 31740.0, 11142.0, 8100.0, 1.0, 128.955);	// above under main posts
	tp.CreateDisplayList (XZ, 67, 128.0, 256.0, 35920.0, 10832.0, 41127.0, 1.0, 7.6);		// above under steps at end of phys sci
	tp.CreateDisplayList (YZ, 68, 256.0, 256.0, 35920.0, 10832.0, 41127.0, 0.75, 7.6);		// above steps at end of phys sci
	tp.CreateDisplayList (YZ, 39, 128.0, 256.0, 35990.0, 11002.0, 41127.0, 0.75, 7.6);		// above steps at end of phys sci (darker back bit)
	tp.CreateDisplayList (XZ, 69, 256.0, 128.0, 4580.0, 11142.0, 40985.0, 106.094, 1.0);	// ABOVE_UNDER_POSTS_2 main posts by library
	tp.CreateDisplayList (YZ, 71, 256.0, 256.0, 35748.0, 11142.0, 22096.0, 0.75, 12.69);	// above post between chanc and phys sci
	tp.CreateDisplayList (XZ, 72, 128.0, 256.0, 35748.0, 11142.0, 22096.0, 1.0, 12.69);		// above under post between chanc and phys sci

	glNewList(232, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(31768.0 + 45, 11162, 41011.2 - 45);
			glTexCoord2f(10.54, 0.0);
			glVertex3f(33848+ 45, 11920, 43095.2 -45 );
			glTexCoord2f(10.54, 1.0);
			glVertex3f(33848.0- 45, 11920, 43095.2 +45);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(31768.0- 45, 11162, 41011.2 + 45);
		glEnd();
	glEndList();

	glNewList(233, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(31768.0 - 45, 11162, 41011.2 + 45);
			glTexCoord2f(10.54, 0.0);
			glVertex3f(33848- 45, 11920, 43095.2 +45 );
			glTexCoord2f(10.54, 0.75);
			glVertex3f(33848.0- 45, 11920 +192, 43095.2 +45);
			glTexCoord2f(0.0, 0.75);
			glVertex3f(31768.0- 45, 11162 +192, 41011.2 + 45);
		glEnd();
	glEndList();


	glNewList(234, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(31768.0 + 45, 11162, 41011.2 - 45);
			glTexCoord2f(10.54, 0.0);
			glVertex3f(33848+ 45, 11920, 43095.2 -45 );
			glTexCoord2f(10.54, 0.75);
			glVertex3f(33848.0+ 45, 11920 +192, 43095.2 -45);
			glTexCoord2f(0.0, 0.75);
			glVertex3f(31768.0+ 45, 11162 +192, 41011.2 - 45);
		glEnd();
	glEndList();

	// ABOVE_WINDOW_EDGE_3B
	tp.CreateDisplayList (XY, 49, 128.0, 256.0, 33808.0, 10832.0, 25344.0, 1.0, 0.75);		// 3 bricks high

	// ABOVE_WINDOW_BLOCK_XY_3
	tp.CreateDisplayList (XY, 50, 256.0, 256.0, 33888.0, 10832.0, 26752.0, 1.5, 1.0);
	tp.CreateDisplayList (XY, 64, 256.0, 256.0, 33808.0, 10832.0, 41127.0, 8.5, 0.75);		// above end phys sci
	tp.CreateDisplayList (XY, 65, 256.0, 256.0, 6600.0, 11856.0, 43056.0, 68.5, 0.75);		// top of library
	tp.CreateDisplayList (XY, 208, 256.0, 256.0, 24264.0, 11856.0, 43056.0, 38.5, 0.75);	// top of library
	tp.CreateDisplayList (XY, 66, 256.0, 256.0, 4548.0, 11142.0, 40985.0, 106.72, 0.75);	// above library main posts

	// ABOVE_LIB
	tp.CreateDisplayList (XY, 239, 1024.0, 256.0, 31504.96, 10768.0, 43056.0, 1.0, 1.0);	// (above KBLT)
	tp.CreateDisplayList (XY, 238, 256.0, 256.0, 32528.96, 10768.0, 43056.0, 13.75, 1.0);	// (above KBLT)
	tp.CreateDisplayList (XY, 55, 256.0, 256.0, 24264.0, 10768.0, 43056.0, 28.285, 1.0);	// (above KBLT)
	tp.CreateDisplayList (XY, 416, 1024.0, 256.0, 9416.0, 10768.0, 43056.0, 1.0, 1.0);		// (above library text)	
	tp.CreateDisplayList (XY, 415, 256.0, 256.0, 10440.0, 10768.0, 43056.0, 49.0, 1.0);		// (above library)
	tp.CreateDisplayList (XY, 417, 256.0, 256.0, 23240.0, 10768.0, 43056.0, 3.5, 1.0);		// (above library)
	tp.CreateDisplayList (XY, 418, 256.0, 256.0, 22984.0, 10768.0, 43056.0, 1.0, 1.0);		// (above library ticket text)
	tp.CreateDisplayList (XY, 56, 256.0, 256.0, 6600.0, 10768.0, 43056.0, 11.0, 1.0);		// (above library)
	tp.CreateDisplayList (XZ, 70, 256.0, 128.0, 8189.0, 11856.0, 43056.0, 62.3, 0.75);		// above under upstairs
	tp.CreateDisplayList (YZ, 209, 256.0, 64.0, 6600.0, 11856.0, 43056.0, 1.2, 1.0);
	tp.CreateDisplayList (YZ, 210, 256.0, 64.0, 6600.0, 10768.0, 43056.0, 1.0, 1.0);
	tp.CreateDisplayList (XZ, 211, 256.0, 128.0, 8189.0, 10768.0, 43056.0, 62.3, 0.75);		// above under downstairs
	tp.CreateDisplayList (XZ, 212, 256.0, 128.0, 32720.0, 10768.0, 43056.0, 3.5, 0.75);		// above under gcl1
	
	// ABOVE CANTEEN
	tp.CreateDisplayList (YZ, 213, 256.0, 256.0, 2608.0, 10896.0, 10000.0, 0.78, 139.25);

}

//--------------------------------------------------------------------------------------
// Display Purple Posts by Guild Shop
//--------------------------------------------------------------------------------------
void Shay::DisplayPurplePosts ()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PURPLE_POST));
	glCallList(29);
	glPushMatrix();
		glTranslatef(0.0, 0.0, 4800.0);
		glCallList(29);
	glPopMatrix();
	glCallList(30);
	glPushMatrix();
		glTranslatef(0.0, 0.0, 960.0);
		glCallList(30);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 0.0, 2880.0);
		glCallList(30);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PURPLE_POSTSIDE));
	glCallList(31);
		glPushMatrix();
			glTranslatef(0.0, 0.0, -112.0);
			glCallList(31);
		glPopMatrix();

	step = 865.0;
	for (int i = 0; i < 3; i++)
	{
		glPushMatrix();
			glTranslatef(0.0, 0.0, step);
			glCallList(31);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0, 0.0, step + 78.0);
			glCallList(31);
		glPopMatrix();
		step += 960.0;
		if (i == 1) step += 960.0;
	}
	glPushMatrix();
		glTranslatef(0.0, 0.0, 4688.0);
		glCallList(31);
	glPopMatrix();
		glCallList(32);
}

void Shay::DrawPurplePosts ()
{
	tp.CreateDisplayList (YZ, 29, 64.0, 128.0, 33802.0, 10000.0, 31407.0, 13.0, 0.875);	// front
	tp.CreateDisplayList (YZ, 30, 64.0, 128.0, 33802.0, 10000.0, 32384.0, 13.0, 0.61);	// front
	tp.CreateDisplayList (XY, 31, 128.0, 64.0, 33802.0, 10000.0, 31519.0, 0.75, 13.0);	// side
	tp.CreateDisplayList (XY, 32, 128.0, 64.0, 33802.0, 10000.0, 36319.0, 0.58, 13.0);	// side
}

//--------------------------------------------------------------------------------------
// Display Red Posts by Sta Travel Shop
//--------------------------------------------------------------------------------------
void Shay::DisplayRedPosts ()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(RED_POST));
	glCallList(33);
	glPushMatrix();
		glTranslatef(0.0, 0.0, 1399.0);
		glCallList(33);
	glPopMatrix();
	glCallList(34);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(RED_POSTSIDE));
	glPushMatrix();
		glTranslatef(0.0, 0.0, 240.0);
		glCallList(35);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 0.0, 256.0);
		glCallList(35);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 0.0, 1639.0);
		glCallList(35);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 0.0, 1095.0);
		glCallList(35);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 0.0, 1191.0);
		glCallList(35);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 0.0, 1655.0);
		glCallList(35);
	glPopMatrix();
}

void Shay::DrawRedPosts ()
{
	tp.CreateDisplayList (YZ, 33, 64.0, 128.0, 33802.0, 10000.0, 39200.0, 13.0, 0.125);	// front
	tp.CreateDisplayList (YZ, 34, 64.0, 128.0, 33802.0, 10000.0, 40055.0, 13.0, 0.75);	// front
	tp.CreateDisplayList (XY, 35, 64.0, 64.0, 33802.0, 10000.0, 38960.0, 1.0, 13.0);	// side
}

//--------------------------------------------------------------------------------------
// Display Main Posts
//--------------------------------------------------------------------------------------
void Shay::DisplayMainPosts ()
{
	step = 0.0;
	stepLength = 0.0;
	step2 = 0.0;
	for (int j = 0; j < 2; j++)
	{
		glPushMatrix();	
			glTranslatef(stepLength, 0.0, step2);
			for (int i = 0; i < 17; i++)
			{		
				glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST));
				glPushMatrix();	
					glTranslatef(0.0, 0.0, step);
					glCallList(18);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0.0, 0.0, step + 128.0);
					glCallList(18);
				glPopMatrix();
				if ((i == 7) && (j ==0))	// between chanc and phys sci
				{
					glPushMatrix();	
						glTranslatef(4008.0, 0.0, step);
						glCallList(18);
					glPopMatrix();
					glPushMatrix();
						glTranslatef(4008.0, 0.0, step + 128.0);
						glCallList(18);
					glPopMatrix();
				}
		
				glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST_2));
				glPushMatrix();	
					glTranslatef(0.0, 0.0, step);
					glCallList(19);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(128.0, 0.0, step);
					glCallList(19);
				glPopMatrix();
				if ((i == 7) && (j ==0))	// between chanc and phys sci
				{
					glPushMatrix();	
						glTranslatef(4008.0, 0.0, step);
						glCallList(19);
					glPopMatrix();
				}
				step += 1930.0;
			}
			stepLength -= 27192.0;
			step2 -= 32810.0;
		glPopMatrix();
	}

	// library front
	step = -1940.0;
	for (int i = 0; i < 13; i++)
	{		
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST));
		glPushMatrix();	
			glTranslatef(step, 0.0, 30880.0);
			glCallList(18);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(step, 0.0, 31008.0);
			glCallList(18);
		glPopMatrix();
		
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST_2));
		glPushMatrix();
			glTranslatef(step, 0.0, 30880.0);
			glCallList(19);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(step + 128.0, 0.0, 30880.0);
			glCallList(19);
		glPopMatrix();
		step -= 1940.0;
	}

	// first on chanc steps
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST));
	glCallList(51);
	glPushMatrix();
		glTranslatef(0.0, 0.0, 128.0);
		glCallList(51);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST_2));
	glCallList(52);
	glPushMatrix();
		glTranslatef(128.0, 0.0, 0.0);
		glCallList(52);
	glPopMatrix();

	///=====================================================
	///Tutorial 1 Posts
	///=====================================================
	step = -1940.0;

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST));
	glPushMatrix();
	glTranslatef(step, 0.0, 20880.0);
	glCallList(18);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(step, 0.0, 21008.0);
	glCallList(18);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST_2));
	glPushMatrix();
	glTranslatef(step, 0.0, 20880.0);
	glCallList(19);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(step + 128.0, 0.0, 20880.0);
	glCallList(19);
	glPopMatrix();


	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST));
	glPushMatrix();
	glTranslatef(step-1600, 0.0, 20880.0);
	glCallList(18);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(step-1600, 0.0, 21008.0);
	glCallList(18);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST_2));
	glPushMatrix();
	glTranslatef(step-1600, 0.0, 20880.0);
	glCallList(19);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(step + 128.0-1600, 0.0, 20880.0);
	glCallList(19);
	glPopMatrix();
}

void Shay::DrawMainPosts ()
{
	tp.CreateDisplayList (XY, 18, 128.0, 256.0, 31740.0, 9995.0, 10105.0, 1.0, 4.48);
	tp.CreateDisplayList (YZ, 19, 256.0, 128.0, 31740.0, 9995.0, 10105.0, 4.48, 1.0);
	tp.CreateDisplayList (XY, 51, 128.0, 256.0, 31740.0, 9555.0, 8100.0, 1.0, 6.2);		// 1st by steps
	tp.CreateDisplayList (YZ, 52, 256.0, 128.0, 31740.0, 9555.0, 8100.0, 6.2, 1.0);		// 1st by steps
}

//============================================
// Tutorial on banner
//============================================
void Shay::DisplayBanner()
{
	step = -1940.0;
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(THE_BANNER));
	glPushMatrix();
	glTranslatef(step-1600+128, 0.0, 20080.0);
	glCallList(800);

	glPopMatrix();
}

void Shay::DrawBanner()
{
	//tp.CreateDisplayList(XY, 800, 1600.0, 900, -1940, 9995, 10105, 1.0, 1.0);
	tp.CreateDisplayList(XY, 800, 1600-128, 900-128, 31760.0, 10000.0, 10894.0, 1.0, 1.0);	// Banner
	//tp.CreateDisplayList(XY, 800, 1600, 900, 31760, 10000, 10894, 1, 1);
}

//--------------------------------------------------------------------------------------
//  Display Window and Door Posts on Phys SCi Building
//--------------------------------------------------------------------------------------
void Shay::DisplayPhysSciPosts ()
{
	step = 0.0;
	for (int i = 0; i < 16; i++)
	{
		glPushMatrix();	
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_PHYSSCI_FRONT));
			glTranslatef(0.0, 0.0, step);
			glCallList(36);
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_PHYSSCI_RIGHT));
			glCallList(37);
		glPopMatrix();
		glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_PHYSSCI_LEFT));
			glTranslatef(0.0, 0.0, step + 77);
			glCallList(38);
		glPopMatrix();
		step += 960.0;
	}

	step = 960.0;
	for (i = 0; i < 4; i++)
	{
		glPushMatrix();	
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_PHYSSCI_FRONT));
			glTranslatef(0.0, -1024.0, step);
			glCallList(36);
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_PHYSSCI_RIGHT));
			glCallList(37);
		glPopMatrix();
		glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_PHYSSCI_LEFT));
			glTranslatef(0.0, -1024.0, step + 77);
			glCallList(38);
		glPopMatrix();
		step += 960.0;
	}
		glPushMatrix();	
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_PHYSSCI_FRONT));
			glTranslatef(0.0, -1024.0, 7718.0);
			glCallList(36);
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_PHYSSCI_RIGHT));
			glCallList(37);
		glPopMatrix();
		glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_PHYSSCI_LEFT));
			glTranslatef(0.0, -1024.0, 7718.0 + 77);
			glCallList(38);
		glPopMatrix();

	// WindowLedges Phys Sci (toilets downstairs)
	step = 960.0;
	for (i = 0; i < 2; i++)
	{
		glPushMatrix();
			glTranslatef(0.0, -832.0, step);
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_PS_FRONT));
			glCallList(16);
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_PS_TOP));
			glCallList(17);
		glPopMatrix();
		step += 1920.0;
	}
	
	step = 6758.0;
	stepLength = -832.0;
	for (i = 0; i < 2; i++)
	{
		glPushMatrix();
			glTranslatef(0.0, stepLength, step);
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_PS_FRONT));
			glCallList(16);
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_PS_TOP));
			if (i ==1) glCallList(17);
		glPopMatrix();
		step += 960.0;
		stepLength -= 256.0;
	}
	// shops downstairs phys sci
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_PS_BOTT));
	for (i = 40; i < 42; i++) glCallList(i);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_PS_FRONT));
	glCallList(42);

	// WindowLedges Phys Sci (upstairs)
	step = 0.0;
	for (i = 0; i < 15; i++)
	{
		glPushMatrix();
			glTranslatef(0.0, 0.0, step);
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_PS_FRONT));
			glCallList(16);
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_PS_TOP));
			glCallList(17);
		glPopMatrix();
		step += 960.0;
	}
}

void Shay::DrawPhysSciPosts ()
{
	// WINDOWPOST_PS
	tp.CreateDisplayList (YZ, 36, 512.0, 128.0, 33848.0, 11347.0, 26625.0, 1.0, 0.6016);
	tp.CreateDisplayList (XY, 37, 64.0, 512.0, 33848.0, 11347.0, 26625.0, 1.0, 1.0);
	tp.CreateDisplayList (XY, 38, 64.0, 512.0, 33848.0, 11347.0, 26625.0, 1.0, 1.0);


	// WINDOWLEDGE_PS_FRONT & TOP (shorter phys sci ds)
	// first shop
	glNewList(40, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(33808.0, 10544.0, 33421.0);
			glTexCoord2f(0.0, 0.9375);
			glVertex3f(33808.0, 10544.0, 33421.0 + (1024.0 * 0.9375));
			glTexCoord2f(1.0, 0.9375);
			glVertex3f(33928.0, 10588.0, 33421.0 + (1024.0 * 0.9375));
			glTexCoord2f(1.0, 0.0);
			glVertex3f(33928.0, 10588.0, 33421.0);
		glEnd();
	glEndList();

	// small window
	glNewList(41, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(33808.0, 10288.0, 38239.0);
			glTexCoord2f(0.0, 0.315);
			glVertex3f(33808.0, 10288.0, 38239.0 + (1024.0 * 0.315));
			glTexCoord2f(1.0, 0.315);
			glVertex3f(33928.0, 10332.0, 38239.0 + (1024.0 * 0.315));
			glTexCoord2f(1.0, 0.0);
			glVertex3f(33928.0, 10332.0, 38239.0);
		glEnd();
	glEndList();
	tp.CreateDisplayList (YZ, 42, 32.0, 1024.0, 33808.0, 10256.0, 38239.0, 1.0, 0.315);

	// WINDOWLEDGE_PS_FRONT & TOP
	tp.CreateDisplayList (YZ, 16, 32.0, 1024.0, 33808.0, 11344.0, 26663.0, 1.0, 0.9375);
	glNewList(17, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(33808.0, 11376.0, 26663.0);
			glTexCoord2f(0.0, 0.9375);
			glVertex3f(33808.0, 11376.0, 26663.0 + (1024.0 * 0.9375));
			glTexCoord2f(1.0, 0.9375);
			glVertex3f(33928.0, 11420.0, 26663.0 + (1024.0 * 0.9375));
			glTexCoord2f(1.0, 0.0);
			glVertex3f(33928.0, 11420.0, 26663.0);
		glEnd();
	glEndList();
}

//--------------------------------------------------------------------------------------
//  Display Paving Around Shop Doorway
//--------------------------------------------------------------------------------------
void Shay::DisplayDoorPaving ()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DOORPAVE_1));
	glCallList(47);
	glCallList(48);
}

void Shay::DrawDoorPaving ()
{
	tp.CreateDisplayList (XZ, 47, 128.0, 256.0,  33808.0, 10000.0, 31508.0, 0.75, 7.5);	// phy sci 1st doorway
	tp.CreateDisplayList (XZ, 48, 128.0, 256.0,  33808.0, 10000.0, 35324.0, 0.75, 3.5);	// phy sci 2nd doorway
}

//--------------------------------------------------------------------------------------
// Display window and door posts of library
//--------------------------------------------------------------------------------------
void Shay::DisplayLibraryPosts ()
{
	stepLength = 0.0;
	for (int j = 0; j < 2; j++)
	{
		glPushMatrix();
			glTranslatef(0.0, stepLength, 0.0);
			step = 0.0;
			for (int i = 0; i < 15; i++)
			{
				if (!(i > 12 && j == 0))
				{
					glPushMatrix();
						glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_LIB_FRONT));
						glTranslatef(step, 0.0, 0.0);
						glCallList(57);
						glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_LIB_RIGHT));
						glCallList(58);
					glPopMatrix();
					glPushMatrix();
						glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_LIB_LEFT));
						glTranslatef(step + 77, 0.0, 0.0);
						glCallList(59);
					glPopMatrix();
					step -= 1088.0;
				}
			}
		glPopMatrix();
		stepLength += 1054;
	}		
	stepLength = 0.0;
	for (j = 0; j < 2; j++)
	{
		glPushMatrix();
			glTranslatef(0.0, stepLength, 0.0);
			// WINDOWLEDGE_LIB
			step = 0.0;
			for (int i = 0; i < 13; i++)
			{
				if (!(i > 10 && j == 0))
				{
					glPushMatrix();
						glTranslatef(step, 0.0, 0.0);
						glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_LIB_A));
						glCallList(60);
						glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_LIB_B));
						glCallList(61);
						glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_LIB_TOP_A));
						glCallList(62);
						glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_LIB_TOP_B));
						glCallList(63);
					glPopMatrix();
				}
				step -= 1088.0;
			}
		glPopMatrix();
		stepLength += 1024;
	}
	// first ledge upstairs
	glPushMatrix();
		glTranslatef(1088.0, 1024.0, 0.0);
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_LIB_A));
		glCallList(60);
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_LIB_B));
		glCallList(61);
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_LIB_TOP_A));
		glCallList(62);
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_LIB_TOP_B));
		glCallList(63);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TICKET_COUNTER_TOP));
	glCallList(442);
	glCallList(444);
	glCallList(446);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TICKET_COUNTER_EDGE));
	glCallList(445);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TICKET_COUNTER_EDGE_2));
	glCallList(443);
	glPushMatrix();
		glTranslatef(1152.0, 0.0, 0.0);
		glCallList(443);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TICKET_COUNTER_EDGE_3));
	glCallList(447);
	glPushMatrix();
		glTranslatef(1152.0, 0.0, 0.0);
		glCallList(447);
	glPopMatrix();
}

void Shay::DrawLibraryPosts ()
{
	// WINDOWPOST_LIB_FRONT
	tp.CreateDisplayList (XY, 57, 128.0, 512.0, 24035.0, 10304.0, 43096.0, 0.6016, 1.0);
	tp.CreateDisplayList (YZ, 58, 512.0, 64.0, 24035.0, 10304.0, 43096.0, 1.0, 1.0);
	tp.CreateDisplayList (YZ, 59, 512.0, 64.0, 24035.0, 10304.0, 43096.0, 1.0, 1.0);

	// WINDOWLEDGE_LIB
	tp.CreateDisplayList (XY, 61, 1024.0, 32.0, 21896.0, 10320.0, 43056.0, 0.5313, 1.0);
	tp.CreateDisplayList (XY, 60, 1024.0, 32.0, 22440.0, 10320.0, 43056.0, 0.5313, 1.0);
	glNewList(62, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(21896.0, 10352.0, 43056.0);
			glTexCoord2f(0.5313, 0.0);
			glVertex3f(21896.0 + (1024.0 * 0.5313), 10352.0, 43056.0);
			glTexCoord2f(0.5313, 1.0);
			glVertex3f(21896.0 + (1024.0 * 0.5313), 10396.0, 43176.0);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(21896.0 , 10396.0, 43176.0);
		glEnd();
	glEndList();
	glNewList(63, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(22440.0, 10352.0, 43056.0);
			glTexCoord2f(0.5313, 0.0);
			glVertex3f(22440.0 + (1024.0 * 0.5313), 10352.0, 43056.0);
			glTexCoord2f(0.5313, 1.0);
			glVertex3f(22440.0 + (1024.0 * 0.5313), 10396.0, 43176.0);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(22440.0 , 10396.0, 43176.0);
		glEnd();
	glEndList();
	
	// Ticket Counter
	tp.CreateDisplayList (XZ, 442, 128.0, 256.0, 22984.0, 10305.0, 42992.0, 9.0, 0.625);
	tp.CreateDisplayList (YZ, 443, 64.0, 64.0, 22984.0, 10256.0, 43056.0, 0.766, 1.0);
	tp.CreateDisplayList (XY, 444, 128.0, 256.0, 22984.0, 10256.0, 43056.0, 9.0, 0.1914);

	tp.CreateDisplayList (XY, 445, 128.0, 32.0, 22984.0, 10286.0, 42992.0, 9.0, 0.59);

	tp.CreateAngledPolygon(446, 128.0, 256.0,  22984.0,  24136.0,  24136.0,  22984.0,
	                                          10286.0, 10286.0, 10276.0, 10276.0,
											  42992.0, 42992.0, 43088.0, 43088.0, 5, 1);
	
	tp.CreateAngledPolygon(447, 64.0, 64.0,  22984.0,  22984.0,  22984.0,  22984.0,
	                                          10286.0, 10276.0, 10305.0, 10305.0,
											  42992.0, 43056.0, 43056.0, 42992.0, 6, 1);	
}

//--------------------------------------------------------------------------------------
//  Display Pavement
//--------------------------------------------------------------------------------------
void Shay::DisplayPavement ()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENT_TOP));
	for (int i = 72; i < 74; i ++) glCallList(i);
	glCallList(28);
	for (i = 81; i < 89; i ++) glCallList(i);
	glPushMatrix();
		glTranslatef(0.0, 0.0, 1920.0);
		glCallList(86);
	glPopMatrix();

	for (i = 247; i < 250; i ++) glCallList(i);
	glPushMatrix();
		glTranslatef(0.0, 0.0, 8640.0);
		glCallList(248);
	glPopMatrix();
	glCallList(241);
	glCallList(428);
	
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENT_TOP));
	for (i = 91; i < 93; i ++) glCallList(i);
	glCallList(246);
	glCallList(243);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENT_TOP_FLIP));
	glCallList(74);
	glCallList(245);
	glCallList(244);
	glCallList(242);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENTSIDE_LEFT));
	glCallList(75);
	glCallList(436);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENTSIDE_RIGHT));
	glCallList(76);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENTSIDE_TOP));
	glCallList(77);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENT_16));
	glCallList(78);
	glCallList(79);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENT_16));
	glCallList(80);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENT_CORNER_1));
	glCallList(93);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENT_CORNER_2));
	glCallList(94);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENT_FLIP));
	for (i = 89; i < 91; i ++) glCallList(i);
	glCallList(240);
	glPushMatrix();
		glTranslatef(-26848.0, 0.0, 0.0);
		glCallList(240);
	glPopMatrix();
}

void Shay::DrawPavement ()
{
	// PAVEMENT
	tp.CreateDisplayList (XZ, 87, 128.0, 64.0,  2608.0, 10000.0, 10000.0, 17.0, 482.5);
	tp.CreateDisplayList (XZ, 73,  128.0, 64.0, 31632.0, 10000.0, 10000.0, 17.0, 482.5);
	tp.CreateDisplayList (XZ, 88, 128.0, 64.0,  33744.0, 10000.0, 41104.0, 4.75, 30.5);	// by steps between phys sci and library
	tp.CreateDisplayList (XZ, 428, 128.0, 64.0,  34256.0, 10000.0, 26704.0, 1.0, 9.5); // phys sci doorway (behind carpet)
	//

	// PAVEMENT_TOP
	tp.CreateDisplayList (XZ, 74, 64.0, 128.0, 4912.0, 10000.0, 40880.0, 416.5, 17.0);
	tp.CreateDisplayList (XZ, 246, 64.0, 128.0, 32656.0, 10000.0, 42928.0, 15.0, 2.0); // gcl1 door way
	tp.CreateDisplayList (XZ, 245, 64.0, 128.0, 24080.0, 10000.0, 42928.0, 3.0, 1.5); // gcl1 door way
	tp.CreateDisplayList (XZ, 244, 64.0, 128.0, 8189.0, 10000.0, 42928.0, 44.8, 1.80); // library door way
	tp.CreateDisplayList (XZ, 243, 64.0, 128.0, 2576.0, 10000.0, 42928.0, 36.0, 21.0);	// entrance to IT block
	tp.CreateDisplayList (XZ, 242, 64.0, 128.0, 4848.0, 10000.0, 42928.0, 27.5, 21.0);	// entrance to IT block
	tp.CreateDisplayList (XZ, 241, 128.0, 64.0, 2096.0, 10000.0, 41168.0, 4.5, 29.0);	// entance to psch block
	tp.CreateDisplayList (XZ, 240, 128.0, 64.0, 31568.0, 10000.0, 40816.0, 1.0, 1.0);	// corner space filler

	// PAVEMENT_JOINS
	glNewList(89, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(31568.0, 10000.0, 40816.0);
			glTexCoord2f(17.5, 0.0);
			glVertex3f(33808.0, 10000.0, 40816.0);
			glTexCoord2f(17.5, 35.0);
			glVertex3f(33808.0, 10000.0, 43056.0);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(31568.0, 10000.0, 40816.0);
		glEnd();
	glEndList();
	glNewList(91, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(31504.0, 10000.0, 40880.0);
			glTexCoord2f(34.0, 17.0);
			glVertex3f(33680.0, 10000.0, 43056.0);
			glTexCoord2f(34.0, 17.0);
			glVertex3f(33680.0, 10000.0, 43056.0);
			glTexCoord2f(0.0, 17.0);
			glVertex3f(31504.0, 10000.0, 43056.0);
		glEnd();
	glEndList();
	glNewList(93, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(31504.0, 10000.0, 40880.0);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(31632.0, 10000.0, 40880.0);
			glTexCoord2f(18.0, 17.0);
			glVertex3f(33808.0, 10000.0, 43056.0);
			glTexCoord2f(17.0, 17.0);
			glVertex3f(33680.0, 10000.0, 43056.0);
		glEnd();
	glEndList();

	glNewList(90, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(2608.0, 10000.0, 40816.0);
			glTexCoord2f(17.5, 0.0);
			glVertex3f(4848.0, 10000.0, 40816.0);
			glTexCoord2f(17.5, 0.0);
			glVertex3f(4848.0, 10000.0, 40816.0);
			glTexCoord2f(0.0, 35.0);
			glVertex3f(2608.0, 10000.0, 43056.0);
		glEnd();
	glEndList();

	glNewList(92, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(4912.0, 10000.0, 40880.0);
			glTexCoord2f(34.0, 17.0);
			glVertex3f(2736.0, 10000.0, 43056.0);
			glTexCoord2f(34.0, 17.0);
			glVertex3f(2736.0, 10000.0, 43056.0);
			glTexCoord2f(0.0, 17.0);
			glVertex3f(4912.0, 10000.0, 43056.0);
		glEnd();
	glEndList();

	glNewList(94, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(17.0, 0.0);
			glVertex3f(4784.0, 10000.0, 40880.0);
			glTexCoord2f(18.0, 0.0);
			glVertex3f(4912.0, 10000.0, 40880.0);
			glTexCoord2f(1.0, 17.0);
			glVertex3f(2736.0, 10000.0, 43056.0);
			glTexCoord2f(0.0, 17.0);
			glVertex3f(2608.0, 10000.0, 43056.0);
		glEnd();
	glEndList();

	// PAVEMENTSIDE_LEFT
	tp.CreateDisplayList (XZ, 75,  64.0, 64.0, 31568.0, 10000.0, 10096.0, 1.0, 480.0);
	tp.CreateDisplayList (XZ, 436,  64.0, 64.0, 31568.0, 9086.0, 3408.0, 1.0, 45.0);	// Side paving at entrance
	// PAVEMENTSIDE_RIGHT
	tp.CreateDisplayList (XZ, 76,  64.0, 64.0, 4784.0, 10000.0, 10000.0, 1.0, 481.5);
	// PAVEMENTSIDE_TOP
	tp.CreateDisplayList (XZ, 77,  64.0, 64.0, 4848.0, 10000.0, 40816.0, 417.5, 1.0);
	// PAVEMENT_STEPS_CORNER
	tp.CreateDisplayList (XZ, 78,  128.0, 64.0, 31568.0, 10000.0, 10000.0, 1.0, 1.5);   // corner above chanc steps
	tp.CreateDisplayList (XZ, 80,  32.0, 64.0, 31568.0, 10000.0, 9950.0, 70.0, 0.797);  // strip along top of chanc steps
	tp.CreateDisplayList (XZ, 28, 128.0, 64.0,  33744.0, 10000.0, 22096.0, 17.2, 52.0); // between chanc and phy sci
	tp.CreateDisplayList (XZ, 248, 128.0, 64.0,  33744.0, 10000.0, 10449.0, 1.5, 16.0); // doorway to chanc
	tp.CreateDisplayList (XZ, 247, 128.0, 64.0,  33744.0, 10000.0, 39185.0, 1.5, 23.0); // doorway to red posts
	tp.CreateDisplayList (XZ, 249, 128.0, 64.0, 31632.0, 9086.0, 3408.0, 18.0, 45.0);	//entry (bottom of steps)
	tp.CreateDisplayList (XZ, 81, 128.0, 64.0,  33744.0, 10000.0, 26704.0, 2.5, 11.0);	//phys sci doorway 1
	tp.CreateDisplayList (XZ, 82, 128.0, 64.0,  33744.0, 10000.0, 27344.0, 4.5, 3.5);	//phys sci doorway 1
	tp.CreateDisplayList (XZ, 83, 128.0, 64.0,  33744.0, 10000.0, 36304.0, 5.0, 5.3);	//phys sci doorway 2
	tp.CreateDisplayList (XZ, 84, 128.0, 64.0,  33744.0, 10000.0, 36624.0, 2.5, 9.0);	//phys sci doorway 2
	tp.CreateDisplayList (XZ, 85, 128.0, 64.0,  33744.0, 10000.0, 37200.0, 5.0, 10.5);	//phys sci doorway 2
	tp.CreateDisplayList (XZ, 86, 128.0, 64.0,  33744.0, 10000.0, 28624.0, 2.5, 13.5);	//phys sci toilet doorways
}

//--------------------------------------------------------------------------------------
// Display Wall Bricks
//--------------------------------------------------------------------------------------
void Shay::DisplayBricks ()
{
	// WALL_BRICK_YZ
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_YZ));
	for (int i = 101; i < 111; i ++) glCallList(i);
	for (i = 112; i < 126; i ++) glCallList(i);
	for (i = 191; i < 195; i ++) glCallList(i);
	glPushMatrix();
		glTranslatef(0.0, 0.0, 1920.0);
		glCallList(109);
		glCallList(110);
		glCallList(394);
	glPopMatrix();
	glCallList(222);
	glCallList(394);
	glCallList(396);
	glCallList(397);
	
	// bricks with security sign
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_SEC_SIGN));
	glCallList(398);
	
	// WALL_BRICK_USD_YZ
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_USD_YZ));
	for (i = 200; i < 202; i ++) glCallList(i);
	glCallList(188);


	// WALL_BRICK_XY
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_XY));
	for (i = 135; i < 165; i++) glCallList(i);
	for (i = 217; i < 222; i++) glCallList(i);
	glPushMatrix();
		glTranslatef(0.0, 0.0, -1792.0);
		glCallList(136);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 1024.0, 0.0);
		glCallList(152);
	glPopMatrix();
	for (i = 195; i < 198; i++) glCallList(i);
	glCallList(392);
	for (i = 430; i < 434; i++) glCallList(i);
	// Brick with map on
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAP_2));
	glCallList(434);


	// WALL_BRICK_GAP_YZ
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_GAP_YZ));
	for (i = 180; i < 182; i++) glCallList(i);
	glPushMatrix();
		glTranslatef(0.0, 1024.0, 0.0);
		glCallList(180);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 0.0, -1920.0);
		glCallList(181);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_GAP2_YZ));
	glCallList(182);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_GAP_1));
	for (i = 183; i < 185; i++) glCallList(i);

	// WALL_BRICK_XY_END
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_XY_END));
	for (i = 165; i < 168; i++) glCallList(i);
	glCallList(134);
	glCallList(185);
	glCallList(187);
	glCallList(399);
	glPushMatrix();
		glTranslatef(-32.0, 0.0, 640.0);
		glCallList(399);
	glPopMatrix();
	step = -832.0;
	for (i = 0; i < 2; i++)
	{
		glPushMatrix();
			glTranslatef(0.0, 0.0, step);
			glCallList(166);
		glPopMatrix();
		step += 1920;
	}
	glPushMatrix();
		glTranslatef(0.0, 0.0, 321.0);
		glCallList(167);
	glPopMatrix();
	for (i = 131; i < 132; i++) glCallList(i);
	glCallList(132);
	glPushMatrix();
		glTranslatef(0.0, 0.0, 960.0);
		glCallList(132);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 0.0, 8640.0);
		glCallList(132);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 0.0, 9600.0);
		glCallList(132);
	glPopMatrix();
	glCallList(133);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_XY_87WIDTH));
	glCallList(130);
	glCallList(186);

	// WALL_BRICK_YZ_END
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_YZ_END));
	for (i = 126; i < 130; i ++) glCallList(i);
		glPushMatrix();
		glTranslatef(-896.0, 0.0, 0.0);
		glCallList(128);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 1088.0, 0.0);
		glCallList(129);
		glCallList(168);
	glPopMatrix();
	for (i = 168; i < 170; i ++) glCallList(i);
	glCallList(390);
	glCallList(391);
	glCallList(393);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_3_4));
	glCallList(189);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SHADOW_BRICK));
	glCallList(190);
}

void Shay::DrawBricks ()
{
	// WALL_BRICK_YZ
	// --------  (Face of Cancerllary Building) --------
	tp.CreateDisplayList (YZ, 101, 128.0, 128.0, 33808.0, 9872.0, 9552.0, 2.5, 7.5);		// panel 1 (above steps)
	tp.CreateDisplayList (YZ, 222, 128.0, 128.0, 33840.0, 8976.0, 5840.0, 23.625, 5.0);		// panel 1 (before steps)
	tp.CreateDisplayList (YZ, 102, 128.0, 128.0, 33808.0, 8976.0, 6480.0, 23.625, 24.0);	// panel 2 (below steps)
	tp.CreateDisplayList (YZ, 103, 128.0, 128.0, 33808.0, 10000.0, 11472.0, 1.5, 60.0);		// panel 3 (below window 1)
	tp.CreateDisplayList (YZ, 104, 128.0, 128.0, 33808.0, 10000.0, 20112.0, 1.5, 15.5);		// panel 4 (below window 2)	
	tp.CreateDisplayList (YZ_FLIP, 105, 128.0, 128.0, 33808.0, 10960.0, 9552.0, 2.0, 97.5);	// us panel 4
	tp.CreateDisplayList (YZ, 120, 128.0, 128.0, 33808.0, 10960.0, 22032.0, 2.0, 0.5);		// us panel 4 (last 1/2 brick)
	
	// -------- (Face of Physical Science/Shops Block) --------
	tp.CreateDisplayList (YZ, 106, 128.0, 128.0, 33808.0, 10000.0, 25344.0, 4.525, 11.0);	// panel 1 (around rusty man)
	tp.CreateDisplayList (YZ, 107, 128.0, 128.0, 33808.0, 11024.0, 25344.0, 6.5, 10.0);		// us panel 1
	tp.CreateDisplayList (YZ, 108, 128.0, 128.0, 33808.0, 11024.0, 26624.0, 2.5, 113.305);	// us panel 2
	tp.CreateDisplayList (YZ, 109, 128.0, 128.0, 33808.0, 10000.0, 27559.0, 3.5, 8.5);		// panel 3 (toilets window)
	tp.CreateDisplayList (YZ, 394, 128.0, 128.0, 33808.0, 10384.0, 27559.0, 1.0, 7.5);		// panel 3 (toilets window)
	tp.CreateDisplayList (YZ, 110, 128.0, 128.0, 33872.0, 9936.0, 28967.0, 6.5, 4.5);		// panel 4 (toilets door)
	tp.CreateDisplayList (YZ, 112, 128.0, 128.0, 33808.0, 10000.0, 33422.0, 2.0, 14.4);		// panel 5 (booth)
	tp.CreateDisplayList (YZ, 113, 128.0, 128.0, 33808.0, 10128.0, 33422.0, 3.0, 5.5);		// panel 5 (booth below window)
	tp.CreateDisplayList (YZ, 188, 128.0, 128.0, 33808.0, 10128.0, 34254.0, 3.0, 1.0);		// panel 5 (booth below window)
	tp.CreateDisplayList (YZ, 115, 128.0, 128.0, 34260.0, 10000.0, 36319.0, 2.5, 2.5);		// panel 6 (phys sci doorway)
	tp.CreateDisplayList (YZ, 191, 128.0, 128.0, 34260.0, 10256.0, 36319.0, 4.5, 1.5);		// panel 6 (phys sci doorway)
	tp.CreateDisplayList (YZ, 192, 128.0, 128.0, 34260.0, 10576.0, 36383.0, 2.0, 2.0);		// panel 6 (phys sci doorway)
	tp.CreateDisplayList (YZ, 114, 128.0, 128.0, 33808.0, 10000.0, 37855.0, 2.05, 10.51);	// panel 7 (with window)
	tp.CreateDisplayList (YZ, 116, 128.0, 128.0, 33808.0, 10128.0, 37855.0, 5.5, 1.05);		// panel 7 (with window)
	tp.CreateDisplayList (YZ, 396, 128.0, 128.0, 33808.0, 10128.0, 38111.0, 5.5, 1.0);		// panel 7 (with window)
	tp.CreateDisplayList (YZ, 397, 128.0, 128.0, 33808.0, 10512.0, 37855.0, 2.5, 3.0);		// panel 7 (with window)
	tp.CreateDisplayList (YZ, 398, 256.0, 128.0, 33808.0, 10256.0, 37983.0, 1.05, 1.1);		// panel 7 (with sign)
	tp.CreateDisplayList (YZ_FLIP, 117, 128.0, 128.0, 33808.0, 10128.0, 38560.0, 5.5, 0.5);	// panel 7 (with window)
	tp.CreateDisplayList (YZ, 118, 128.0, 128.0, 33808.0, 10128.0, 38624.0, 5.5, 4.5);		// panel 7 (with window)
	tp.CreateDisplayList (YZ, 119, 128.0, 128.0, 33808.0, 10000.0, 40615.0, 6.5, 4.0);		// panel 8 (end panel)
	tp.CreateDisplayList (YZ, 121, 128.0, 128.0, 34256.0, 9936.0, 27303.0, 3.0, 2.0);		// first doorway panel
	tp.CreateDisplayList (YZ, 193, 128.0, 128.0, 34256.0, 10576.0, 27303.0, 2.0, 2.0);		// first doorway panel
	tp.CreateDisplayList (YZ, 194, 128.0, 128.0, 34256.0, 10192.0, 27431.0, 3.5, 1.0);		// first doorway panel
	
	// -------- (Face of Canteen Block) --------
	tp.CreateDisplayList (YZ, 122, 128.0, 128.0, 2608.0, 10000.0, 10000.0, 7.0, 243.5);		// long downstairs panel
	tp.CreateDisplayList (YZ, 123, 128.0, 128.0, 2608.0, 10000.0, 42960.0, 7.0, 21.0);		// end downstairs panel
	tp.CreateDisplayList (YZ, 124, 128.0, 128.0, 2608.0, 11088.0, 10000.0, 7.0, 278.5);		// long upstairs panel
	tp.CreateDisplayList (XY, 136, 128.0, 128.0, 2096.0, 10000.0, 42960.0, 4.0, 7.0);		// corner exit to psc block from canteen

	// WALL_BRICK_USD_YZ
	tp.CreateDisplayList (YZ, 200, 128.0, 128.0, 33808.0, 10576.0, 25344.0, 2.0, 1.0);		// panel 1 (around rusty man)
	tp.CreateDisplayList (YZ, 201, 128.0, 128.0, 33808.0, 10576.0, 26496.0, 2.0, 2.0);		// panel 1 (around rusty man)

	// WALL_BRICK_XY
	// --------  (Cancerllary Building) --------
	tp.CreateDisplayList (XY,  399, 128.0, 128.0, 33840.0, 8976.0, 5840.0, 0.5, 23.625);	// first corner edge (bottom of steps)
	tp.CreateDisplayList (XY,  130, 128.0, 128.0, 33808.0, 10960.0, 22096.0, 0.68, 2.0);	// below us window (end wall)
	tp.CreateDisplayList (XY,  131, 128.0, 128.0, 33808.0, 10192.0, 9552.0, 0.68, 15.5);	// above steps
	tp.CreateDisplayList (XY,  132, 128.0, 128.0, 33808.0, 10000.0, 10512.0, 0.68, 1.5);	// first door (others)
	tp.CreateDisplayList (XY,  133, 128.0, 128.0, 33808.0, 11344.0, 26624.0, 0.68, 4.0);	// next us window phys sci
	tp.CreateDisplayList (XY,  143, 128.0, 128.0, 33895.0, 10000.0, 22096.0, 15.5, 16.0);	// end wall
	tp.CreateDisplayList (XY,  186, 128.0, 128.0, 33808.0, 10000.0, 22096.0, 0.68, 1.5);	// end wall
	// --------  (Phys Science Block) -------
	tp.CreateDisplayList (XY,  197, 128.0, 128.0, 33808.0, 10640.0, 25344.0, 1.5, 1.5);		// end wall above telephones
	tp.CreateDisplayList (XY,  196, 128.0, 128.0, 33936.0, 10640.0, 25344.0, 6.0, 1.505);	// end wall above telephones
	tp.CreateDisplayList (XY,  195, 128.0, 128.0, 34576.0, 10128.0, 25344.0, 1.0, 6.5);		// next to telephones
	tp.CreateDisplayList (XY,  190, 128.0, 128.0, 34704.0, 10000.0, 25344.0, 9.5, 5.75);	// end wall behind drinks machine
	tp.CreateDisplayList (XY,  189, 128.0, 128.0, 34704.0, 10736.0, 25344.0, 9.5, 0.75);	// end wall above drinks machine
	tp.CreateDisplayList (XY,  144, 128.0, 128.0, 33808.0, 10000.0, 25344.0, 7.0, 1.6);		// end wall
	tp.CreateDisplayList (XY,  145, 128.0, 128.0, 33876.0, 9936.0, 36319.0, 3.0, 7.0);		// ps 2nd door(leftside entrance)
	tp.CreateDisplayList (XY,  146, 128.0, 128.0, 33808.0, 9936.0, 37855.0, 4.25, 7.0);		// ps 2nd door(rightside entrance)
	tp.CreateDisplayList (XY,  147, 128.0, 128.0, 33808.0, 9936.0, 26752, 4.0, 7.0);		// ps first door (left bottom)
	tp.CreateDisplayList (XY,  148, 128.0, 128.0, 33808.0, 9936.0, 27559.0, 3.5, 4.5);		// ps first door (right bottom)
	tp.CreateDisplayList (XY,  149, 128.0, 128.0, 33872.0, 10384.0, 27559.0, 3.0, 3.5);		// ps first door (right top)
	tp.CreateDisplayList (XY,  185, 128.0, 128.0, 34256.0, 10000.0, 27303.0, 0.5, 6.5);		// ps first door (1/2 inner brick)
	tp.CreateDisplayList (XY,  166, 128.0, 128.0, 33808.0, 10000.0, 29479.0, 0.5, 4.0);		// side of toilet doors phys sci
	tp.CreateDisplayList (XY,  167, 128.0, 128.0, 33808.0, 10256.0, 38239.0, 0.75, 4.5);	// side of small window phys sci
	tp.CreateDisplayList (XY_FLIP,  152, 128.0, 128.0, 33936.0, 10832.0, 25344.0, 15.5, 2.5);	// end wall panel 2 phys sci
	tp.CreateDisplayList (XY,  153, 128.0, 128.0, 33808.0, 11024.0, 25344.0, 17.5, 6.5);	// end wall panel 3 phys sci
	tp.CreateDisplayList (XY,  165, 128.0, 128.0, 34260.0, 10000.0, 36639.0, 0.7, 6.5);		// ps 2nd door(inner 1/2 brick)
	tp.CreateDisplayList (XY,  187, 128.0, 128.0, 33808.0, 10256.0, 34382.0, 0.5, 2.0);		// side of toilet doors phys sci

	// --------  (Library Block) --------
	tp.CreateDisplayList (XY,  154, 128.0, 128.0, 33616.0, 10000.0, 43056.0, 19.0, 6.0);	// first panel
	tp.CreateDisplayList (XY,  155, 128.0, 128.0, 30800.0, 10000.0, 43056.0, 15.0, 6.0);	// 2nd panel
	tp.CreateDisplayList (XY,  156, 128.0, 128.0, 27976.0, 9936.0, 43056.0, 12.0, 3.0);		// 3rd panel (next to KBLT)
	tp.CreateDisplayList (XY,  217, 128.0, 128.0, 29512.0, 9936.0, 43056.0, 10.0, 2.75);	// 3rd panel (below nexus sign)
	tp.CreateDisplayList (XY,  157, 128.0, 128.0, 24264.0, 10256.0, 43056.0, 1.5, 4.0);		// 4th panel (next to KBLT)
	tp.CreateDisplayList (XY,  218, 128.0, 128.0, 24264.0, 10000.0, 43056.0, 11.5, 2.5);	// around glass boards
	tp.CreateDisplayList (XY,  219, 128.0, 128.0, 25352.0, 10192.0, 43056.0, 3.0, 4.5);		// around glass boards
	tp.CreateDisplayList (XY,  220, 128.0, 128.0, 27976.0, 10192.0, 43056.0, 3.0, 4.5);		// around glass boards
	tp.CreateDisplayList (XY,  221, 128.0, 128.0, 29256.0, 10192.0, 43056.0, 2.0, 4.5);		// around glass boards
	tp.CreateDisplayList (XY,  158, 128.0, 128.0, 30800.0, 11024.0, 43056.0, 41.0, 6.5);	// US 1st panel
	tp.CreateDisplayList (XY,  159, 128.0, 128.0, 24264.0, 11024.0, 43056.0, 51.0, 6.5);	// US 2nd panel
	tp.CreateDisplayList (XY,  160, 128.0, 128.0, 22984.0, 10000.0, 43056.0, 9.0, 2.0);		// US 3rd panel (start of ds library)
	tp.CreateDisplayList (XY,  161, 128.0, 128.0, 10952.0, 10000.0, 43056.0, 94.0, 2.5);	// US 4th panel (under of ds library)
	tp.CreateDisplayList (XY,  162, 128.0, 128.0, 6600.0, 11024.0, 43056.0, 137.0, 2.5);	// US 4th panel (under of ds library)
	tp.CreateXtoYWindowList (434, 43056.0, 6856.0, 256.0, 10256.0, 512.0, 1.0, 1.0);		// End of DS (Map)
	tp.CreateDisplayList (XY, 433, 128.0, 128.0, 7112.0, 10640.0, 43056.0, 8.0, 1.0);		// End DS
	tp.CreateDisplayList (XY, 432, 128.0, 128.0, 7112.0, 10128.0, 43056.0, 1.5, 5.0);		// End DS
	tp.CreateDisplayList (XY, 431, 128.0, 128.0, 8072.0, 10064.0, 43056.0, 0.914, 5.5);		// End DS
	tp.CreateDisplayList (XY, 430, 128.0, 128.0, 6600.0, 10128.0, 43056.0, 2.0, 5.0);		// End DS
	tp.CreateDisplayList (XY, 163, 128.0, 128.0, 6600.0, 10000.0, 43056.0, 12.414, 2.0);	// End DS
	tp.CreateDisplayList (XY, 164, 128.0, 128.0, 6600.0, 11024.0, 43056.0, 17.29, 6.5);		// End US
	tp.CreateDisplayList (YZ, 126, 128.0, 128.0, 6600.0, 10000.0, 43056.0, 6.0, 0.5);		// end panel corner
	tp.CreateDisplayList (YZ, 125, 128.0, 128.0, 6514.0, 10000.0, 43120.0, 14.5, 20.5);		// end panel
	tp.CreateDisplayList (YZ, 127, 128.0, 128.0, 6600.0, 11024.0, 43056.0, 6.5, 0.5);		// end panel top
	tp.CreateDisplayList (YZ, 128, 128.0, 128.0, 33616.0, 9936.0, 43056.0, 6.5, 0.75);		// cgl1 side panel
	tp.CreateDisplayList (YZ, 129, 128.0, 128.0, 24264.0, 9936.0, 43056.0, 6.5, 0.5);		// gap in middle of library
	tp.CreateDisplayList (YZ, 168, 128.0, 128.0, 24136.0, 9936.0, 43056.0, 2.5, 0.5);		// gap in middle of library
	tp.CreateDisplayList (YZ, 169, 128.0, 128.0, 8813.12, 11344.0, 43056.0, 4.0, 0.5);		// edge of first us window post
	tp.CreateDisplayList (XY, 135, 128.0, 128.0, 24072.0, 10000.0, 43120.0, 1.5, 17.0);		// middle of gap
	tp.CreateDisplayList (XY, 134, 128.0, 128.0, 6514.0, 10000.0, 43120.0, 0.75, 14.5);		// end corner
	tp.CreateDisplayList (XY, 141, 128.0, 128.0, 33104.0, 10000.0, 43152.0, 1.0, 6.0);		// brick between gcl1 doors
	tp.CreateDisplayList (XY, 140, 128.0, 128.0, 34448.0, 9424.0, 43056.0, 12.5, 4.5);		// end below stairs
	tp.CreateDisplayList (YZ, 390, 128.0, 128.0, 10952.0, 10000.0, 43056.0, 2.5, 0.75);		// side of library door
	tp.CreateDisplayList (YZ, 391, 128.0, 128.0, 8189.0, 10000.0, 43056.0, 6.0, 0.5);		// side of library door
	tp.CreateDisplayList (XY, 392, 128.0, 128.0, 10952.0, 10320.0, 43152.0, 0.25, 3.5);		// side edge of library door
	
	// --------  (Phys Sci Building very end wall by steps) --------
	tp.CreateDisplayList (XY,  142, 128.0, 128.0, 33808.0, 10000.0, 41127.0, 11.5, 6.5);
	tp.CreateDisplayList (XY,  150, 128.0, 128.0, 33808.0, 11024.0, 41127.0, 16.5, 2.5);
	tp.CreateDisplayList (XY,  151, 128.0, 128.0, 34448.0, 9360.0, 41127.0, 6.5, 5.5);		// below window
	tp.CreateDisplayList (XY,  137, 128.0, 128.0, 35280.0, 9296.0, 41127.0, 6.0, 6.5);		// below window
	tp.CreateDisplayList (XY,  138, 128.0, 128.0, 35600.0, 10000.0, 41127.0, 3.5, 6.5);
	tp.CreateDisplayList (XY,  139, 128.0, 128.0, 33872.0, 11216.0, 41127.0, 12.5, 6.0);
	tp.CreateDisplayList (YZ_FLIP, 393, 128.0, 128.0, 33872.0, 11344.0, 41063.0, 4.0, 0.5);	// upstairs edge of window
	
	// WALL_BRICK_GAP_YZ
	tp.CreateDisplayList (YZ, 180, 128.0, 32.0, 33895.0, 10192.0, 22079.0, 5.0, 0.530);	// end chanc
	tp.CreateDisplayList (YZ, 181, 128.0, 32.0, 33872.0, 10512.0, 30542.0, 2.5, 0.80);	// toilets phys sci
	// WALL_BRICK_GAP2_YZ
	tp.CreateDisplayList (YZ, 182, 128.0, 32.0, 33872.0, 10512.0, 27559.0, 2.5, 0.80);	// toilets phys sci
	// WALL_GAP_1
	tp.CreateDisplayList (XY, 183, 8.0, 128.0, 30792.0, 10000.0, 43056.0, 1.0, 6.0);	// near KBLT
	tp.CreateDisplayList (XY, 184, 8.0, 128.0, 30792.0, 11024.0, 43056.0, 1.0, 6.5);	// as above but upstairs
}

//--------------------------------------------------------------------------------------
// Display Roof
//--------------------------------------------------------------------------------------
void Shay::DisplayRoof()
{
	// main roof planks
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_PLANKS));
	for (int i = 250; i < 253; i++) glCallList(i);
	
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_BEAM_1));
	// corner beams
	for (i = 1; i < 6; i ++) glCallList(i);
	step = -1689.0;
	for (i = 0; i < 85; i++)
	{
		glPushMatrix();
			glTranslatef(0.0, 0.0, step);
			glCallList(253);
		glPopMatrix();
		step += 386.0;
	}
	glPushMatrix();
		glTranslatef(0.0, 0.0, -2005.0);
		glCallList(253);
	glPopMatrix();
	glCallList(254);

	step = 214.0;
	for (i = 0; i < 8; i++)
	{
		glPushMatrix();
			glTranslatef(0.0, 0.0, step);
			glCallList(254);
		glPopMatrix();
		step += 386.0;
	}

	glPushMatrix();
		glTranslatef(0.0, 0.0, 3216.0);
		glCallList(254);
	glPopMatrix();

	// Beams between library and phys sci
	step = 0.0;
	for (i = 0; i < 5; i++)
	{
		glPushMatrix();
			glTranslatef(0.0, 0.0, step);
			glCallList(298);
		glPopMatrix();
		step += 386.0;
	}

	glPushMatrix();
		glTranslatef(0.0, 0.0, -99.0);
		glCallList(298);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 0.0, 1798.0);
		glCallList(298);
	glPopMatrix();

	// Library Roof
	step = 281.0;
	for (i = 0; i < 70; i++)
	{
		glPushMatrix();
			glTranslatef(step, 0.0, 0.0);
			glCallList(296);		
		glPopMatrix();
		step += 388.0;
	}

	// spacers
	for (i = 202; i < 204; i ++) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_BEAM_4));
	for (i = 6; i < 11; i ++) 
	{
		glCallList(i);
		glPushMatrix();
			glTranslatef(0.0, 0.0, 32.0);
			glCallList(i);
		glPopMatrix();
	}

	step = -1689.0;
	for (i = 0; i < 85; i++)
	{
		glPushMatrix();
			glTranslatef(0.0, 0.0, step);
			glCallList(255);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0, 0.0, step + 32.0);
			glCallList(255);
		glPopMatrix();
		step += 386.0;
	}

	glPushMatrix();
		glTranslatef(0.0, 0.0, -2005.0);
		glCallList(255);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 0.0, -1973.0);
		glCallList(255);
	glPopMatrix();

	step = 214.0;
	for (i = 0; i < 8; i++)
	{
		glPushMatrix();
			glTranslatef(0.0, 0.0, step);
			glCallList(256);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0, 0.0, step + 32.0);
			glCallList(256);
		glPopMatrix();
		step += 386.0;
	}

	glPushMatrix();
		glTranslatef(0.0, 0.0, 3216.0);
		glCallList(256);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 0.0, 32.0);
		glCallList(256);
	glPopMatrix();

	// Beams between library and phys sci
	step = 0.0;
	for (i = 0; i < 5; i++)
	{
		glPushMatrix();
			glTranslatef(0.0, 0.0, step);
			glCallList(299);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0, 0.0, step + 32.0);
			glCallList(299);
		glPopMatrix();
		step += 386.0;
	}

	glPushMatrix();
		glTranslatef(0.0, 0.0, -67.0);
		glCallList(299);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 0.0, 1798.0);
		glCallList(299);
	glPopMatrix();	

	// Library Roof
	step = 281.0;
	for (i = 0; i < 70; i++)
	{
		glPushMatrix();
			glTranslatef(step, 0.0, 0.0);
			glCallList(297);		
		glPopMatrix();
		glPushMatrix();
			glTranslatef(step + 32.0, 0.0, 0.0);
			glCallList(297);
		glPopMatrix();
			
		step += 388.0;
	}
	
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_PLANKS_2));
	glCallList(257);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_BEAM_3));
	// corner beams
	for (i = 170; i < 175; i ++) 
	{
		glCallList(i + 5);
		glPushMatrix();
			glTranslatef(32.0, 0.0, 0.0);
			glCallList(i + 5);
		glPopMatrix();
	}
	glCallList(426);
	glCallList(427);
	glPushMatrix();
		glTranslatef(0.0, 49.0, 3248.0);
		glCallList(427);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 49.0, 19031.0);
		glCallList(427);
	glPopMatrix();

	// spacer top of chanc
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_BEAM_3_TOP));
	glCallList(204);
	glCallList(205);
	glPushMatrix();
		glTranslatef(64.0, 0.0, 0.0);
		glCallList(205);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_BEAM_2));
	// spacers
	for (i = 97; i < 101; i ++) glCallList(i);
	// corner beams
	for (i = 170; i < 175; i ++) glCallList(i);
	

	// Top of Roof
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_TOP));
	for (i = 214; i < 216; i ++) glCallList(i);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_TOP_LIB));
		glCallList(216);
}

void Shay::DrawRoof()
{
	// Chanc Top of Roof
	glNewList(214, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(31740.0, 11364.0, 8100.0);
			glTexCoord2f(0.0, 257.9);
			glVertex3f(31740.0, 11364.0, 8100.0 + (128.0 * 257.9));
			glTexCoord2f(2.0, 273.4);
			glVertex3f(33848.0, 12140.72, 8100.0 + (128.0 * 273.4));
			glTexCoord2f(2.0, 0.0);
			glVertex3f(33848.0, 12140.72, 8100.0);
		glEnd();
	glEndList();
	// Canteen Top of Roof
	glNewList(215, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(2608.0, 12140.72, 8100.0);
			glTexCoord2f(0.0, 273.4);
			glVertex3f(2608.0, 12140.72, 8100.0 + (128.0 * 273.4));
			glTexCoord2f(2.0, 257.9);
			glVertex3f(4716.0, 11364.0, 8100.0 + (128.0 * 257.9));
			glTexCoord2f(2.0, 0.0);
			glVertex3f(4716.0, 11364.0, 8100.0);
		glEnd();
	glEndList();
	// Library Top of Roof
	glNewList(216, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(4716.0, 11364.0, 40983.2);
			glTexCoord2f(211.125, 0.0);
			glVertex3f(4716.0 + (128.0 * 211.125), 11364.0, 40983.2);
			glTexCoord2f(227.59, 16.15);
			glVertex3f(4716.0 + (128.0 * 227.59), 12140.72, 43095.2);
			glTexCoord2f(-16.47, 16.15);
			glVertex3f(2608.0, 12140.72, 43095.2);
		glEnd();
	glEndList();
	// Chanc Side Planks
	glNewList(250, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(31868.0, 11366.0, 8100.0);
			glTexCoord2f(0.0, 257.9);
			glVertex3f(31868.0, 11366.0, 8100.0 + (128.0 * 257.9));
			glTexCoord2f(16.48, 273.4);
			glVertex3f(33848.0, 12094.72, 8100.0 + (128.0 * 273.4));
			glTexCoord2f(16.48, 0.0);
			glVertex3f(33848.0, 12094.72, 8100.0);
		glEnd();
	glEndList();
	// Chanc Side Beams Bottom
	glNewList(253, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(31868.0, 11284.0, 10105.0);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(31868.0, 11284.0, 10137.0);
			glTexCoord2f(16.48, 1.0);
			glVertex3f(33848.0, 12012.72, 10137.0);
			glTexCoord2f(16.48, 0.0);
			glVertex3f(33848.0, 12012.72, 10105.0);
		glEnd();
	glEndList();
	// Chanc Side Beams Side
	glNewList(255, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(31868.0, 11284.0, 10105.0);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(31868.0, 11284.0 + 82.0, 10105.0);
			glTexCoord2f(16.48, 1.0);
			glVertex3f(33848.0, 12012.72 + 82.0, 10105.0);
			glTexCoord2f(16.48, 0.0);
			glVertex3f(33848.0, 12012.72, 10105.0);
		glEnd();
	glEndList();
	// Chanc Side Planks (between chanc and phys sci)
	glNewList(251, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(35748.0, 11366.0, 22046.0);
			glTexCoord2f(0.0, 25.79);
			glVertex3f(35748.0, 11366.0, 22046.0 + (128.0 * 25.79));
			glTexCoord2f(15.82, 25.79);
			glVertex3f(33848.0, 12065.28, 22046.0 + (128.0 * 25.79));
			glTexCoord2f(15.82, 0.0);
			glVertex3f(33848.0, 12065.28, 22046.0);
		glEnd();
	glEndList();
	// Chanc Side Beams Bottom (between phys sci and chanc)
	glNewList(254, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(35748.0, 11284.0, 22096.0);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(35748.0, 11284.0, 22096.0 + 32.0);
			glTexCoord2f(15.82, 1.0);
			glVertex3f(33848.0, 11983.28, 22096.0 + 32.0);
			glTexCoord2f(15.82, 0.0);
			glVertex3f(33848.0, 11983.28, 22096.0);
		glEnd();
	glEndList();
	// Chanc Side Beams Side (between phys sci and chanc)
	glNewList(256, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(35748.0, 11284.0, 22096.0);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(35748.0, 11284.0 + 82.0, 22096.0);
			glTexCoord2f(15.82, 1.0);
			glVertex3f(33848.0, 11983.28 + 82.0, 22096.0);
			glTexCoord2f(15.82, 0.0);
			glVertex3f(33848.0, 11983.28, 22096.0);
		glEnd();
	glEndList();
	// Chanc Side Planks (between phys sci and library)
	glNewList(252, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(36108.0, 11019.68, 41127.0);
			glTexCoord2f(0.0, 15.1);
			glVertex3f(36108.0, 11019.68, 41127.0 + (128.0 * 15.1));
			glTexCoord2f(19.44, 15.1);
			glVertex3f(33848.0, 12061.55, 41127.0 + (128.0 * 15.1));
			glTexCoord2f(19.44, 0.0);
			glVertex3f(33848.0, 12061.55, 41127.0);
		glEnd();
	glEndList();
	// Chanc Side Beams Bottom (between phys sci and library)
	glNewList(298, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(36108.0, 10937.68, 41226.0);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(36108.0, 10937.68, 41226.0 + 32.0);
			glTexCoord2f(19.44, 1.0);
			glVertex3f(33848.0, 11979.55, 41226.0 + 32.0);
			glTexCoord2f(19.44, 0.0);
			glVertex3f(33848.0, 11979.55, 41226.0);
		glEnd();
	glEndList();
	// Chanc Side Beams Side (between phys sci and library)
	glNewList(299, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(36108.0, 10937.68, 41226.0);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(36108.0, 10937.68 + 82.0, 41226.0);
			glTexCoord2f(19.44, 1.0);
			glVertex3f(33848.0, 11979.55 + 82.0, 41226.0);
			glTexCoord2f(19.44, 0.0);
			glVertex3f(33848.0, 11979.55, 41226.0);
		glEnd();
	glEndList();
	// Library Side Planks
	glNewList(257, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(4541.0, 11366.0, 43056.0 - 1942.0);
			glTexCoord2f(213.45, 0.0);
			glVertex3f(4541.0 + (128.0 * 213.45), 11366.0, 43056.0 - 1942.0);
			glTexCoord2f(228.6, 16.15);
			glVertex3f(4541.0 + (128.0 * 213.45) + 1940.0, 12080.0, 43056.0);
			glTexCoord2f(-15.1, 16.15);
			glVertex3f(2608.0, 12080.0, 43056.0);
		glEnd();
	glEndList();
	// Library Side Beams Bottom
	glNewList(296, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(4541.0, 11283.0, 41114.0);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(4573.0, 11283.0, 41114.0);
			glTexCoord2f(16.15, 1.0);
			glVertex3f(4573.0, 11997.0, 43056.0);
			glTexCoord2f(16.15, 0.0);
			glVertex3f(4541.0, 11997.0, 43056.0);
		glEnd();
	glEndList();
	// Library Side Beams
	glNewList(297, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(4541.0, 11283.0, 41114.0);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(4541.0, 11365.0, 41114.0);
			glTexCoord2f(16.15, 1.0);
			glVertex3f(4541.0, 12079.0, 43056.0);
			glTexCoord2f(16.15, 0.0);
			glVertex3f(4541.0, 11997.0, 43056.0);
		glEnd();
	glEndList();

	// spacer between phys sci
	tp.CreateDisplayList (YZ, 97, 32.0, 128.0, 33808.0, 12048.0, 25344.0, 1.0, 123.3);
	// spacer between phys sci amd chanc blocks
	tp.CreateDisplayList (YZ, 98, 32.0, 128.0, 35748.0, 11334.0, 22096.0, 1.0, 25.38);
	// spacer above main posts (chanc side)
	tp.CreateDisplayList (YZ, 99, 32.0, 128.0, 31868.0, 11334.0, 8100.0, 1.0, 257.9);
	// spacer above library
	tp.CreateDisplayList (XY, 202, 128.0, 32.0, 4541.0, 12048.0, 43056.0, 230.0, 1.0);
	// spacer above main posts (library side)
	tp.CreateDisplayList (XY, 203, 128.0, 32.0, 4541.0, 11332.0, 41114.0, 213.5, 1.08);
	// spacer above chanc
	tp.CreateDisplayList (YZ, 204, 128.0, 128.0, 33808.0, 11999.0, 8100.0, 0.64, 109.35);
	tp.CreateYtoZWindowList (205, 33848.0, 11954.0, 144.0, 22096.0, 3248.0, 0.64, 25.375);
	// centre beam between chanc and phys sci
	tp.CreateDisplayList (XZ, 426, 64.0, 128.0, 33848.0, 11954.0, 22096.0, 1.0, 25.375);
	// top corner spacer
	tp.CreateDisplayList (XY, 427, 64.0, 128.0, 33808.0, 11999.0, 22096.0, 0.75, 0.75);
	
	// Joins where roof slants
	DrawAngledRoofBeam(1, 33848.0 - 1867.0, 12012.72 - 687.13, 41226.0, 15.21);
	DrawAngledRoofBeam(2, 33848.0 - 1481.0, 12012.72 - 545.07, 41612.0, 12.0);
	DrawAngledRoofBeam(3, 33848.0 - 1095.0, 12012.72 - 403.01, 41998.0, 8.78);
	DrawAngledRoofBeam(4, 33848.0 - 709.0,	12012.72 - 260.94, 42384.0, 5.57);
	DrawAngledRoofBeam(5, 33848.0 - 323.0,	12012.72 - 118.88, 42770.0, 2.36);
	DrawAngledRoofBeam2(170, 31980.0, 11998.0 - 672.41, 43056.0 - 1827.0, 15.21);
	DrawAngledRoofBeam2(171, 32366.0, 11998.0 - 530.35, 43056.0 - 1441.0, 12.0);
	DrawAngledRoofBeam2(172, 32752.0, 11998.0 - 388.28, 43056.0 - 1055.0, 8.78);
	DrawAngledRoofBeam2(173, 33138.0, 11998.0 - 246.22, 43056.0 - 669.0,  5.57);
	DrawAngledRoofBeam2(174, 33524.0, 11998.0 - 104.16, 43056.0 - 283.0,  2.36);
}

// --------------------------------------------------------------------------------------
//  Creates Angled Roof Beams
// --------------------------------------------------------------------------------------
void Shay::DrawAngledRoofBeam (int listNo, GLdouble x, GLdouble y, GLdouble z, GLdouble beamSize)
{
	glNewList(listNo, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(x, y, z + 32.0);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(x, y, z);
			glTexCoord2f(beamSize, 1.0);
			glVertex3f(33848.0, 12012.72, z);
			glTexCoord2f(beamSize, 0.0);
			glVertex3f(33848.0, 12012.72, z + 32.0);
		glEnd();
	glEndList();
	glNewList(listNo + 5, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(x, y, z);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(x, y + 82.0, z);
			glTexCoord2f(beamSize, 1.0);
			glVertex3f(33848.0, 12012.72 + 82.0, z);
			glTexCoord2f(beamSize, 0.0);
			glVertex3f(33848.0, 12012.72, z);
		glEnd();
	glEndList();
}

void Shay::DrawAngledRoofBeam2 (int listNo, GLdouble x, GLdouble y, GLdouble z, GLdouble beamSize)
{
	glNewList(listNo, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(x, y, z);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(x + 32.0, y, z);
			glTexCoord2f(1.0, beamSize);
			glVertex3f(x + 32.0, 11998.0, 43056);
			glTexCoord2f(0.0, beamSize);
			glVertex3f(x, 11998.0, 43056);
		glEnd();
	glEndList();
	glNewList(listNo + 5, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(x, y, z);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(x, y + 82.0, z);
			glTexCoord2f(1.0, beamSize);
			glVertex3f(x, 11998.0 + 82.0, 43056);
			glTexCoord2f(0.0, beamSize);
			glVertex3f(x, 11998.0, 43056);
		glEnd();
	glEndList();
}

//--------------------------------------------------------------------------------------
// Display Steps
//--------------------------------------------------------------------------------------
void Shay::DisplayEntranceSteps ()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(STEP_PAVING_1));
	for (int i = 258; i < 274 ; i ++) glCallList(i);
	
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(STEP_EDGE));
	for (i = 274; i < 290 ; i ++) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(STEP_PAVING_1));
	for (i = 290; i < 293 ; i ++) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(STEP_EDGE));
	for (i = 293; i < 296 ; i ++) glCallList(i);


	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(STEPS_LIBRARY));
	step = 0.0;
	step2 = -51.0;
	for (i = 0; i < 10; i++)
	{
		glPushMatrix();
			glTranslatef(step, step2, 0.0);
			glCallList(206);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(step, step2, 965.0);
			glCallList(206);
		glPopMatrix();
		step += 128.0;
		step2 += -51.0;
	}
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(STEPS_LIBRARY_TOP));
	glCallList(207);
		glPushMatrix();
			glTranslatef(0.0, 0.0, 965.0);
			glCallList(207);
		glPopMatrix();
}

void Shay::DrawEntranceSteps ()
{
	step = 10000.0;
	stepLength = 9808.0;
	for (int i = 258; i < 274 ; i ++)
	{
		tp.CreateDisplayList (XZ, i, 1024.0, 512.0, 31582.0, step, stepLength, 2.2, 0.277);
		tp.CreateDisplayList (XY,  i + 16, 64.0, 64.0, 31582.0, step - 64.0, stepLength, 35.0, 1.0);
		step -= 48.0;
		stepLength -= 142.0;
		if ((i+3) % 4 == 0) 
		{
			stepLength -= 500.0;
			step -= 48.0;
		}
	}
	step = 9808.0;
	stepLength = 8882.0;
	for (i = 290; i < 293 ; i ++)
	{
		tp.CreateDisplayList (XZ, i, 1024.0, 512.0, 31582.0, step, stepLength, 2.2, 1.0);
		tp.CreateDisplayList (XY,  i + 3, 64.0, 64.0, 31582.0, step - 64.0, stepLength, 35.0, 1.0);
		step -= 239.0;
		stepLength -= 1068.0;
	}

	// steps next to GCL1
	tp.CreateDisplayList (XZ, 206, 128.0, 1024.0, 34508.0, 10000.0, 41127, 1.0, 0.942);
	tp.CreateDisplayList (XZ, 207, 256.0, 1024.0, 34352.0, 10000.0, 41127, 0.609, 0.942);
	
}

//--------------------------------------------------------------------------------------
// Display Bench
//--------------------------------------------------------------------------------------
void Shay::DisplayBench ()
{
	step2 = 3860.0;
	for (int j = 0; j < 11; j++)
	{	
		glPushMatrix();
			glTranslatef(0.0, 0.0, step2);

			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_TOP));
			glCallList(400);
	
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_SIDE));
			glCallList(401);
			glPushMatrix();
				glTranslatef(0.0, 0.0, 480.0);
				glCallList(401);
			glPopMatrix();

			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_SIDE_2));
			glPushMatrix();
				glTranslatef(0.0, 0.0, 50.0);
				glCallList(402);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0, 0.0, 430.0);
				glCallList(402);
			glPopMatrix();

			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_EDGE_TOP));
			step = 0.0;
			for (int i = 0; i < 2; i++)
			{
				glPushMatrix();
					glTranslatef(0.0, 0.0, step);	
					glCallList(403);
					glPushMatrix();
						glTranslatef(192.0, 0.0, 0.0);
						glCallList(403);
					glPopMatrix();
				glPopMatrix();
				step += 430;
			}
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_EDGE_SIDE));
			step = 0.0;
			for (i = 0; i < 2; i++)
			{
				glPushMatrix();
					glTranslatef(step, 0.0, 0.0);
					glCallList(404);
				glPopMatrix();;
				step += 192;
			}

			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_EDGE));
			glCallList(405);
				glPushMatrix();
					glTranslatef(192.0, 0.0, 0.0);
					glCallList(405);
				glPopMatrix();
			glCallList(406);
				glPushMatrix();
					glTranslatef(192.0, 0.0, 0.0);
					glCallList(406);
				glPopMatrix();
	
		glPopMatrix();
		step2 += 1930.0;
		if (j == 4) step2 += 5790.0;
	}

	step2 = 1940.0;
	GLdouble vertStep = 0.0;
	for (j = 0; j < 8; j++)
	{	
		glPushMatrix();
			glTranslatef(step2, 0.0, vertStep);

			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_TOP));
			glCallList(407);
	
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_SIDE));
			glCallList(408);
			glPushMatrix();
				glTranslatef(480.0, 0.0, 0.0);
				glCallList(408);
			glPopMatrix();

			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_SIDE_2));
			glPushMatrix();
				glTranslatef(50.0, 0.0, 0.0);
				glCallList(409);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(430.0, 0.0, 0.0);
				glCallList(409);
			glPopMatrix();

			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_EDGE_TOP_2));
			step = 0.0;
			for (int i = 0; i < 2; i++)
			{
				glPushMatrix();
					glTranslatef(step, 0.0, 0.0);	
					glCallList(410);
					glPushMatrix();
						glTranslatef(0.0, 0.0, 192.0);
						glCallList(410);
					glPopMatrix();
				glPopMatrix();
				step += 430;
			}
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_EDGE_3));
			step = 0.0;
			for (i = 0; i < 2; i++)
			{
				glPushMatrix();
					glTranslatef(0.0, 0.0, step);
					glCallList(411);
				glPopMatrix();;
				step += 192;
			}

			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_EDGE_2));
			glCallList(412);
				glPushMatrix();
					glTranslatef(0.0, 0.0, 192.0);
					glCallList(412);
				glPopMatrix();
			glCallList(413);
				glPushMatrix();
					glTranslatef(0.0, 0.0, 192.0);
					glCallList(413);
				glPopMatrix();
	
		glPopMatrix();
		step2 += 1940.0;
		if (j == 1) step2 += 1940.0;
		if (j == 5) step2 += 9700.0;
		if (j== 6)
		{
			vertStep += 1848.0;
			step2 = 5926.0;
		}
	}
}

void Shay::DrawBench ()
{
	tp.CreateDisplayList (XZ, 400, 64.0, 64.0, 31760.0, 10147.0, 10894.0, 3.0, 7.5);
	tp.CreateDisplayList (XY, 401, 64.0, 64.0, 31760.0, 10000.0, 10894.0, 3.0, 2.3);
	tp.CreateDisplayList (XY, 402, 64.0, 64.0, 31760.0, 10000.0, 10894.0, 3.0, 1.72);
	tp.CreateDisplayList (YZ, 403, 64.0, 64.0, 31760.0, 10000.0, 10894.0, 1.72, 0.78);
	tp.CreateDisplayList (YZ, 404, 64.0, 64.0, 31760.0, 10107.0, 10944.0, 0.625, 5.938);
	tp.CreateDisplayList (YZ, 405, 64.0, 64.0, 31760.0, 10107.0, 10894.0, 0.625, 0.78);
	tp.CreateDisplayList (YZ_FLIP, 406, 64.0, 64.0, 31760.0, 10107.0, 11324.0, 0.625, 0.78);

	tp.CreateDisplayList (XZ, 407, 64.0, 64.0, 5410.0, 10147.0, 41008.0, 7.5, 3.0);
	tp.CreateDisplayList (YZ, 408, 64.0, 64.0, 5410.0, 10000.0, 41008.0, 2.3, 3.0);
	tp.CreateDisplayList (YZ, 409, 64.0, 64.0, 5410.0, 10000.0, 41008.0, 1.72, 3.0);
	tp.CreateDisplayList (XY, 410, 64.0, 64.0, 5410.0, 10000.0, 41008.0, 0.78, 1.72);
	tp.CreateDisplayList (XY, 411, 64.0, 64.0, 5460.0, 10107.0, 41008.0, 5.938, 0.625);
	tp.CreateDisplayList (XY, 412, 64.0, 64.0, 5410.0, 10107.0, 41008.0, 0.78, 0.625);
	tp.CreateDisplayList (XY_FLIP, 413, 64.0, 64.0, 5410.0 + 430.0, 10107.0, 41008.0, 0.78, 0.625);
}

//--------------------------------------------------------------------------------------
// Display Extras (signs etc)
//--------------------------------------------------------------------------------------
void Shay::DisplayExtras ()
{
	// Rusty Man like Sculpture
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(RUSTY_MAN));
	glCallList(300);

	// Directions sign next to Sta Travel Shop
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SIGN_1));
	glCallList(301);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SIGN_1_SIDE_1));
	glCallList(302);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SIGN_1_SIDE_2));
	glCallList(303);

	// GCL1 Sign
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SIGN_2));
	glCallList(304);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SIGN_2_SIDE));
	glCallList(305);
	glPushMatrix();
		glTranslatef(384.0, 0.0, 0.0);
		glCallList(305);
	glPopMatrix();

	// KBLT
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(KBLT_EDGE));
	glCallList(306);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(KBLT_EDGE_2));
	glCallList(307);
	glCallList(308);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(KBLT_EDGE_CORNER));
	glCallList(309);
	glPushMatrix();
		glTranslatef(2471.0, 0.0, 0.0);
		glCallList(309);
	glPopMatrix();

	// Nexus Sign
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(NEXUS_SIDE));
	glCallList(310);
	glPushMatrix();
		glTranslatef(1280.0, 0.0, 0.0);
		glCallList(310);
	glPopMatrix();

	// Glass Notice Board next to KBLT
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(GLASS_B_SIDE));
	glCallList(311);
	glPushMatrix();
		glTranslatef(896.0, 0.0, 0.0);
		glCallList(311);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(3904.0, 0.0, 0.0);
		glCallList(311);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(4800.0, 0.0, 0.0);
		glCallList(311);
	glPopMatrix();
	glCallList(435);
	glPushMatrix();
		glTranslatef(768.0, 0.0, 0.0);
		glCallList(435);
	glPopMatrix();

	// Security Sign on Chanc Doorway
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SECURITY_SIGN));
	glCallList(312);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SECURITY_SIGN_2));
	glCallList(313);

	//  Prospective Student Sign
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PSC_SIGN));
	glCallList(314);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PSC_SIGN_2));
	glCallList(315);

	// Staff Sign
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CO_SIGN));
	glCallList(316);

	// DRINKS MACINE
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DRINKS_SIDE_2));
	for (int i = 317; i < 319; i++) glCallList(i);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DRINKS_SIDE));
	glPushMatrix();
		glTranslatef(-1152.0, 0.0, 0.0);
		glCallList(317);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DRINKS_TOP));
	glCallList(319);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DRINKS_EDGE));
	glCallList(320);
	glPushMatrix();
		glTranslatef(-1136.0, 0.0, 0.0);
		glCallList(320);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MACHINE_SIDES));
	for (i = 321; i < 323; i++) glCallList(i);
	glCallList(320);
	glPushMatrix();
		glTranslatef(317.12, 0.0, 0.0);
		glCallList(321);
	glPopMatrix();
	glCallList(320);
	glPushMatrix();
		glTranslatef(255.0, 0.0, 0.0);
		glCallList(322);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MACHINE_SIDES_2));
	glCallList(323);
	glPushMatrix();
		glTranslatef(350.0, 0.0, 0.0);
		glCallList(323);
	glPopMatrix();

	// Doorway Carpet
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CARPET));
	glCallList(324);
	glCallList(429);

	// No Smoking Sign
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(NO_SMOKE_SIGN));
	glCallList(326);
	glCallList(327);

	// Star Travel Sign
	step = 0.0;
	int sign = STA_TRAVEL;
	int signBack = STA_TRAVEL_2;
	int signEdge = STA_TRAVEL_EDGE;
	for (i = 0; i < 2; i++)
	{
		glPushMatrix();
			glTranslatef(0.0, 0.0, step);
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(sign));
			glCallList(328);

			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(signEdge));
			glCallList(329);

			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(STA_TRAVEL_BRACKET));
			glCallList(330);
			glPushMatrix();
				glTranslatef(0.0, 0.0, 64.0);
				glCallList(330);
			glPopMatrix();

			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(signBack));
			glCallList(331);

			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(STA_TRAVEL_BOTTOM));
			glCallList(332);
		glPopMatrix();
		step -= 3840.0;
		sign = GS_SIGN;
		signBack = GS_SIGN_2;
		signEdge = GS_SIGN_EDGE;
	}

	// Telephone Boxes
	step = 0.0;
	for (i= 0; i < 2; i++)
	{
		glPushMatrix();
			glTranslatef(step, 0.0, 0.0);

			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TELEPHONE_BACK));
			glCallList(333);
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TELEPHONE_FRONT));
			glCallList(334);
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TELEPHONE_SIDE_1));
			glCallList(335);
			glPushMatrix();
				glTranslatef(285.0, 0.0, 0.0);
				glCallList(335);
			glPopMatrix();
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TELEPHONE_FRONT_2));
			glCallList(336);
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TELEPHONE_MAIN_SIDE));
			glCallList(337);
			glPushMatrix();
				glTranslatef(285.0, 0.0, 0.0);
				glCallList(337);
			glPopMatrix();

			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TELEPHONE_TOP_1));
			glCallList(338);
			glCallList(340);

			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TELEPHONE_SIDE_2));
			glCallList(339);
			glPushMatrix();
				glTranslatef(285.0, 0.0, 0.0);
				glCallList(339);
			glPopMatrix();

			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TELEPHONE_TOP_2));
			glCallList(341);
			glCallList(342);

			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TELEPHONE_BOTTOM));
			glCallList(343);

			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TELEPHONE_FILL));
			glCallList(348);
			glCallList(349);
			glPushMatrix();
				glTranslatef(0.0, 0.0, 168.2);
				glCallList(349);
			glPopMatrix();
			glCallList(388);
			glPushMatrix();
				glTranslatef(275.2, 0.0, 0.0);
				glCallList(388);
			glPopMatrix();

			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TELEPHONE_FRONT_3));
			glCallList(395);
			glPushMatrix();
				glTranslatef(269.0, 0.0, 0.0);
				glCallList(395);
			glPopMatrix();
		
		glPopMatrix();
		step += 384.0;
	}

	// Sides of KBLT
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(KBLT_SIDE_1));
	glCallList(345);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(KBLT_SIDE_2));
	glCallList(346);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(KBLT_SIDE_1));
	glPushMatrix();
		glTranslatef(-2496.0, 0.0, 0.0);
		glCallList(345);
	glPopMatrix();	

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(KBLT_SIDE_2));
	glPushMatrix();
		glTranslatef(-2316.0, 0.0, 0.0);			
		glCallList(346);
	glPopMatrix();

	// Toilet Signs
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TOILET_WOMEN));
	glCallList(347);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TOILET_MEN));
	glPushMatrix();
		glTranslatef(0.0, 0.0, 1920.0);			
		glCallList(347);
	glPopMatrix();

	// Ledge of Ticket Office
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TICKET_LEDGE));
	glCallList(419);
	glPushMatrix();
		glTranslatef(0.0, 32.0, 0.0);			
		glCallList(419);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TICKET_LEDGE_EDGE));
	glCallList(420);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TICKET_LEDGE_EDGE_2));
	glCallList(421);
	glPushMatrix();
		glTranslatef(1208.0, 0.0, 0.0);			
		glCallList(421);
	glPopMatrix();
}

void Shay::DrawExtras ()
{
	tp.CreateDisplayList (YZ, 300, 256.0, 1024.0, 33808.0, 10576.0, 25472.0, 1.0, 1.0);		// Rusty Man

	tp.CreateDisplayList (YZ, 301, 512.0, 256.0, 33792.0, 10320.0, 40794.0, 0.75, 0.609);	// Sign 1 (end of phys sci)
	tp.CreateDisplayList (XY, 302, 16.0, 512.0, 33792.0, 10320.0, 40794.0, 1.0, 0.75);		// side of sign 1
	tp.CreateDisplayList (XY, 303, 16.0, 512.0, 33792.0, 10320.0, 40950.0, 1.0, 0.75);		// side of sign 1
	tp.CreateDisplayList (XY, 304, 512.0, 512.0, 33637.0, 10410.0, 43040.0, 0.75, 0.574);	// Sign 2 (GCL1)

	tp.CreateDisplayList (YZ, 305, 512.0, 16.0, 33637.0, 10410.0, 43040.0, 0.574, 1.0);		// side of sign 2

	tp.CreateDisplayList (XY, 306, 16.0, 32.0, 25633.0, 10902.0, 42756.0, 152.88, 1.0);		// KBLT edge top
	tp.CreateDisplayList (XY, 307, 32.0, 16.0, 25608.0, 10000.0, 42756.0, 1.0, 56.375);		// KBLT edge left
	tp.CreateDisplayList (XY_FLIP, 308, 32.0, 16.0, 28072.0, 10000.0, 42756.0, 1.0, 56.375);// KBLT right
	tp.CreateDisplayList (XY, 309, 1.0, 1.0, 25608.0, 10902.0, 42756.0, 25.0, 32.0);		// KBLT corner
	tp.CreateDisplayList (YZ, 310, 2.0, 16.0, 29512.0, 10288.0, 43040.0, 240.0, 1.0);		// Side of Nexus

	tp.CreateDisplayList (YZ, 311, 2.0, 16.0, 24456.0, 10320.0, 43040.0, 224.0, 1.0);		// Side of Glassboards
	tp.CreateDisplayList (YZ, 435, 2.0, 16.0, 7304.0, 10256.0, 43040.0, 192.0, 1.0);		// Side of Glassboards

	tp.CreateDisplayList (XY, 312, 128.0, 128.0, 33752.0, 10659.0, 10511.0, 0.75, 0.75);	// security sign
	tp.CreateDisplayList (XY, 313, 128.0, 128.0, 33752.0, 10659.0, 10513.0, 0.75, 0.75);	// security sign

	tp.CreateDisplayList (XY, 314, 256.0, 128.0, 33660.0, 10836.0, 20111.0, 0.578, 0.561);	// PSC sign
	tp.CreateDisplayList (XY, 315, 256.0, 128.0, 33660.0, 10836.0, 20113.0, 0.578, 0.561);	// PSC sign

	tp.CreateDisplayList (YZ, 316, 256.0, 128.0, 33808.0, 10256.0, 34126.0, 1.0, 1.0);		// CO sign

	tp.CreateDisplayList (YZ, 317, 64.0, 64.0, 35856.0, 10000.0, 24996.0, 11.5, 5.47);		// Drinks Machine
	tp.CreateDisplayList (XY, 319, 64.0, 64.0, 34704.0, 10672.0, 24996.0, 18.0, 1.0);		// Drinks Machine
	tp.CreateDisplayList (XZ, 318, 64.0, 64.0, 34704.0, 10736.0, 24996.0, 18.0, 5.5);		// Drinks Machine
	tp.CreateDisplayList (XY, 320, 16.0, 2.0, 35840.0, 10000.0, 24996.0, 1.0, 336.0);		// Drinks Machine
	tp.CreateDisplayList (YZ, 321, 1.0, 1.0, 35458.0, 10000.0, 25016.0, 660.0, 300.0);		// Drinks Machine Sides
	tp.CreateDisplayList (YZ, 322, 1.0, 1.0, 35163.0, 10000.0, 25016.0, 586.2, 300.0);		// Drinks Machine Sides
	tp.CreateDisplayList (YZ, 323, 1.0, 1.0, 34778.0, 10000.0, 25016.0, 593.22, 300.0);		// Drinks Machine Sides
	
	tp.CreateDisplayList (XZ, 324, 32.0, 32.0, 34064.0, 10000.0, 26704.0, 6.0, 20.0);		// Carpet 1st doorway
	tp.CreateDisplayList (XZ, 429, 32.0, 32.0, 34064.0, 10000.0, 36643.2, 9.0, 17.4);		// Carpet 2nd doorway

	tp.CreateDisplayList (YZ, 326, 256.0, 128.0, 34260.0, 10320.0, 36511.0, 1.1, 1.0);		// No smoke sign doorway 2
	tp.CreateDisplayList (YZ, 327, 256.0, 128.0, 34256.0, 10320.0, 27303.0, 1.1, 1.1);		// No smoke sign doorway 1

	tp.CreateDisplayList (XY, 328, 256.0, 256.0, 33595.0, 10828.0, 40071.0, 0.773, 0.855);	// Sta Travel sign
	tp.CreateDisplayList (YZ, 329, 256.0, 64.0, 33595.0, 10828.0, 40071.0, 0.855, 1.0);		// Sta Travel sign edge
	tp.CreateDisplayList (XY, 330, 16.0, 2.0, 33792.0, 10854.0, 40071.0, 1.0, 76.0);		// Sta Travel sign bracket
	tp.CreateDisplayList (XY, 331, 256.0, 256.0, 33595.0, 10828.0, 40135.0, 0.773, 0.855);	// Sta Travel sign 2
	tp.CreateDisplayList (XZ, 332, 2.0, 64.0, 33595.0, 10828.0, 40071.0, 99.0, 1.0);		// Sta Travel bottom

	tp.CreateDisplayList (XY,  333, 512.0, 512.0, 33808.0, 10192.0, 25344.0, 0.752, 1.05);	// Telephone Back
	tp.CreateDisplayList (XY,  334, 512.0, 32.0, 33882.0, 10598.0, 25173.0, 0.557, 0.719);	// Telephone front
	tp.CreateDisplayList (YZ,  335, 32.0, 256.0, 33882.0, 10598.0, 25173.0, 0.719, 0.7);	// Telephone side top
	tp.CreateDisplayList (XY,  336, 512.0, 16.0, 33882.0, 10621.0, 25173.0, 0.557, 0.75);	// Telephone front
	tp.CreateDisplayList (YZ,  339, 16.0, 256.0, 33882.0, 10621.0, 25173.0, 0.75, 0.7);		// Telephone side
	tp.CreateDisplayList (XZ,  343, 512.0, 128.0, 33882.0, 10268.0, 25250.0, 0.558, 0.75);	// Telephone bottom
	tp.CreateDisplayList (XZ, 348, 2.0, 2.0, 33918.0, 10697.84, 25201.6, 107.0, 56.9);		// telephone roof
	tp.CreateDisplayList (XZ, 349, 2.0, 2.0, 33882.0, 10633.0, 25173.0, 142.6, 2.5);		// telephone roof
	tp.CreateDisplayList (XZ, 388, 2.0, 2.0, 33882.0, 10633.0, 25173.0, 5.0, 89.6);			// telephone roof
	
	tp.CreateDisplayList (YZ,  345, 2.0, 128.0, 28104.0, 10000.0, 42756.0, 467.0, 1.0); // KBLT side
	tp.CreateDisplayList (YZ,  346, 2.0, 2.0, 28014.0, 10000.0, 42866.0, 416.0, 98.0); // KBLT side


	// TELEPHONE ROOF
	tp.CreateAngledPolygon(337, 512.0, 256.0,  33882.0,  33882.0,  33882.0,  33882.0,
	                                          10268.0, 10268.0, 10598.24, 10598.24,
											  25250.0, 25345.34, 25345.34, 25173.0, 6, 4);
	glNewList(338, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(33890.0, 10633.0, 25178.0);
			glTexCoord2f(0.527, 0.0);
			glVertex3f(34160.0, 10633.0, 25178.0);
			glTexCoord2f(0.473, 0.54);
			glVertex3f(34132.0, 10697.84, 25201.6);
			glTexCoord2f(0.055, 0.54);
			glVertex3f(33918.0, 10697.84, 25201.6);
		glEnd();
	glEndList();
	glNewList(341, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(33891.0, 10633.0, 25178.0);
			glTexCoord2f(0.0, 0.637);
			glVertex3f(33891.0, 10633.0, 25341.0);
			glTexCoord2f(0.54, 0.538);
			glVertex3f(33918.5, 10697.84, 25315.6);
			glTexCoord2f(0.54, 0.1);
			glVertex3f(33918.5, 10697.84, 25201.6);
		glEnd();
	glEndList();
	glNewList(342, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(34159.5, 10633.0, 25178.0);
			glTexCoord2f(0.0, 0.637);
			glVertex3f(34159.5, 10633.0, 25341.0);
			glTexCoord2f(0.54, 0.538);
			glVertex3f(34132.0, 10697.84, 25315.6);
			glTexCoord2f(0.54, 0.1);
			glVertex3f(34132.0, 10697.84, 25201.6);
		glEnd();
	glEndList();
	glNewList(340, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(33890.0, 10631.0, 25341.0);
			glTexCoord2f(0.527, 0.0);
			glVertex3f(34160.0, 10631.0, 25341.0);
			glTexCoord2f(0.473, 0.535);
			glVertex3f(34132.0, 10697.84, 25315.4);
			glTexCoord2f(0.055, 0.535);
			glVertex3f(33918.0, 10697.84, 25315.4);
		glEnd();
	glEndList();
	glNewList(395, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(33882.0, 10268.0, 25250.0);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(33898.0, 10268.0, 25250.0);
			glTexCoord2f(1.0, 0.729);
			glVertex3f(33898.0, 10598.24, 25173.0);
			glTexCoord2f(0.0, 0.729);
			glVertex3f(33882.0, 10598.24, 25173.0);
		glEnd();
	glEndList();

	tp.CreateDisplayList (YZ, 347, 128.0, 128.0, 33808.0, 10384.0, 28519.0, 1.0, 1.0);	// toilets sign

	tp.CreateDisplayList (XZ, 419, 2.0, 128.0, 22928.0, 10870.0, 42960.0, 604.0, 0.78);	// ticket box ledge
	tp.CreateDisplayList (XY, 420, 2.0, 32.0, 22928.0, 10870.0, 42960.0, 604.0, 1.0);	// ticket box ledge edge
	tp.CreateDisplayList (YZ, 421, 32.0, 2.0, 22928.0, 10870.0, 42960.0, 1.0, 49);		// ticket box ledge edge side



}

// --------------------------------------------------------------------------------------
// Display larger textures such as windows and doors
// --------------------------------------------------------------------------------------
void Shay::DisplayLargerTextures ()
{
	//Gap betweem chanc and phys sci
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_1));
	glCallList(350);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_1B));
	glCallList(351);

	// Chanc Windows Downstairrs
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_2));
	step = 1920.0;
	for (int i = 0; i < 2; i ++) 
	{
		glPushMatrix();
			glTranslatef(0.0, 0.0, step);
			glCallList(352);
		glPopMatrix();
		step += 2880;
	}

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_2B));
	step = 2880.0;
	for (i = 0; i < 3; i ++) 
	{
		glPushMatrix();
			glTranslatef(0.0, 0.0, step);
			glCallList(352);
		glPopMatrix();
		step += 2880;
		if (i == 2) step -= 960.0;
	}

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_2C));
	step = 6720.0;
	for (i = 1; i < 3; i ++) 
	{
		glPushMatrix();
			glTranslatef(0.0, 0.0, step);
			glCallList(352);
		glPopMatrix();
		step += 2880;
		if (i == 1) step += 1920.0;
	}

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_2D));
	glPushMatrix();
		glTranslatef(0.0, 0.0, 3840.0);
		glCallList(352);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 0.0, 10560.0);
		glCallList(352);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_2E));
	glCallList(352);
	glPushMatrix();
		glTranslatef(0.0, 0.0, 7680.0);
		glCallList(352);
	glPopMatrix();
		
	//Chanc Windows Upstairs
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_2US));
	glPushMatrix();
		glTranslatef(0.0, 1023.0, 0.0);
		glCallList(352);
	glPopMatrix();
	step = 9600.0;
	for (i = 0; i < 3; i ++) 
	{
		glPushMatrix();
			glTranslatef(0.0, 1023.0, step);
			glCallList(352);
		glPopMatrix();
		step += 960;
	}

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_2USB));
	step = 960;
	for (i = 0; i < 9; i ++) 
	{
		glPushMatrix();
			glTranslatef(0.0, 1023.0, step);
			glCallList(352);
		glPopMatrix();
		step += 960;
	}
	
	// Physical Science upstairs
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_3));	
	step = 3840.0;
	for (i = 4; i < 14; i ++) 
	{
		glPushMatrix();
			glTranslatef(0.0, 0.0, step);
			glCallList(353);
		glPopMatrix();
		step += 960;
	}
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_3B));
	step = 0.0;
	for (i = 0; i < 6; i ++) 
	{
		glPushMatrix();
			glTranslatef(0.0, 0.0, step);
			glCallList(353);
		glPopMatrix();
		step += 960.0;
		if (i==4) step = 13440.0;
	}//--------------------------------------------------------------

	// toilets
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_4));
	step = 0.0;
	for (i = 0; i < 2; i ++) 
	{
		glPushMatrix();
			glTranslatef(0.0, 0.0, step);
			glCallList(354);
		glPopMatrix();
		step += 1920;
	}
	// See draw function for details of below
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_5));
	glCallList(355);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_6));
	glCallList(356);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_7));
	glCallList(357);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_8));
	glCallList(358);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_9));
	glCallList(359);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_10));
	glCallList(360);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_11));
	glCallList(361);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_12));
	glCallList(362);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(NEXUS_SIGN));
	glCallList(363);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(GLASS_BOARD));
	glCallList(364);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(GLASS_BOARD_2));
	glCallList(365);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(GLASS_BOARD_3));
	glCallList(366);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(KBLT));
	glCallList(367);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ENTRANCE));
	glCallList(368);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ENTRANCE_2));
	glCallList(369);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(COKE_MACHINE));
	glCallList(370);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(COFFEE_MACHINE));
	glCallList(371);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SWEET_MACHINE));
	glCallList(372);

	// Phys sci door 1
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_13));
	glCallList(373);
	// Phys sci toilets
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_14));
	glCallList(374);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_14B));
	glPushMatrix();
		glTranslatef(0.0, 0.0, 1920.0);
		glCallList(374);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_15));
	glCallList(375);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_16));
	glCallList(379);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_17));
	glCallList(380);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(EXIT_EAST));
	glCallList(381);

	// Chanc Doorways
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CHANC_DOOR_1));
	glCallList(382);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CHANC_DOOR_2));
	glPushMatrix();
		glTranslatef(0.0, 0.0, 8640.0);
		glCallList(382);
	glPopMatrix();

	// Library windows downstairs
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_LIB_1A));
	glCallList(383);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_LIB_1));
	step = 1088.0;
	for (i =0; i<4; i++)
	{
		glPushMatrix();
			glTranslatef(step, 0.0, 0.0);
			glCallList(383);
		glPopMatrix();
		step += 3264;
	}

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_LIB_1B));
	step = 2176.0;
	for (i =0; i<3; i++)
	{
		glPushMatrix();
			glTranslatef(step, 0.0, 0.0);
			glCallList(383);
		glPopMatrix();
		step += 3264;
	}

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_LIB_1C));
	step = 3264.0;
	for (i =0; i<3; i++)
	{
		glPushMatrix();
			glTranslatef(step, 0.0, 0.0);
			glCallList(383);
		glPopMatrix();
		step += 3264.0;
	}

	// library windows upstairs
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_LIB_US_B));
	step = 2176.0;
	for (i =0; i<9; i++)
	{
		glPushMatrix();
			glTranslatef(step, 0.0, 0.0);
			glCallList(384);
		glPopMatrix();
		step += 1088.0;
	}

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_LIB_US_A));
	step = 0.0;
	glCallList(384);
	glPushMatrix();
		glTranslatef(1088.0, 0.0, 0.0);
		glCallList(384);
	glPopMatrix();

	step = 11968.0;
	for (i =0; i<3; i++)
	{
		glPushMatrix();
			glTranslatef(step, 0.0, 0.0);
			glCallList(384);
		glPopMatrix();
		step += 1088;
	}

	// library doorways
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_LIB_DOOR_1));
	glCallList(385);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_LIB_DOOR_2));
	glCallList(386);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_LIB_LONG));
	glCallList(387);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_LIB_FRONT));
	glCallList(389);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DOOR_POST_LIB));
	glCallList(414);
	glPushMatrix();
		glTranslatef(77.0, 0.0, 0.0);
		glCallList(414);
	glPopMatrix();

	// top of toilet door
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TOILET_DOOR_TOP));
	glCallList(422);
	glCallList(423);

	// West Exit
	//glBindTexture(GL_TEXTURE_2D, tp.GetTexture(EXIT_WEST));
	//glCallList(450);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_WINDOW_BLOCK_CHANC));
	glCallList(451);
	// window next to steps
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(STEP_WINDOW));
	glCallList(452);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CARPET));
	glCallList(453);

}

void Shay::DrawLargerTextures ()
{
	// CHANC
	// Gap between chanc and phy sci y1142 z3248
	tp.CreateYtoZWindowList (350, 35879.0, 10000.0, 1147.0, 22096, 1540.0, 0.714, 0.95);	// w190.63  245
	tp.CreateYtoZWindowList (351, 35879.0, 10000.0, 1147.0, 23740, 1605.0, 0.714, 0.98);	// w183
	// chanc windows
	tp.CreateYtoZWindowList (352, 33895.0, 10256.0, 576.0, 9599.0, 867.0, 0.664, 1.0);		// w170
	// chanc doors
	tp.CreateYtoZWindowList (382, 33895.0, 10000.0, 832.0, 10559.0, 867.0, 0.96, 1.0);		// w246

	// PHYS SCI
	// phys sci upstairs
	tp.CreateYtoZWindowList (353, 33895.0, 11411.0, 445.0, 26702.0, 883.0, 0.504, 1.0);		// 129x256
	// phys sci toilets
	tp.CreateYtoZWindowList (354, 33895.0, 10576.0, 255.0, 27662.0, 883.0, 0.578, 1.0);		// 73.93x256
	// phys sci toilets 3rd
	tp.CreateYtoZWindowList (355, 33895.0, 10576.0, 255.0, 33422.0, 919.0, 0.57, 1.0);		// 71.04x256
	// serving window
	tp.CreateYtoZWindowList (356, 33895.0, 10320.0, 511.0, 34419.0, 845.0, 0.605, 1.0);		// 155x256
	// last window
	tp.CreateYtoZWindowList (357, 33895.0, 10320.0, 511.0, 38239.0, 320.0, 1.0, 0.626);		// 256x160.3
	// first purple post window
	tp.CreateYtoZWindowList (358, 33895.0, 10000.0, 832.0, 31519.0, 865.0, 0.96, 1.0);		// 246.2x256
	// second purple post window
	tp.CreateYtoZWindowList (359, 33895.0, 10000.0, 832.0, 32461.0, 883.0, 0.94, 1.0);		// 241.2x256
	// third purple post window
	tp.CreateYtoZWindowList (360, 33895.0, 10000.0, 832.0, 35341.0, 867.0, 0.96, 1.0);		// 246.2x256
	// first red window
	tp.CreateYtoZWindowList (361, 33865.0, 10000.0, 832.0, 39216.0, 839.0, 0.992, 1.0);		// 254.5x256
	// second red window
	tp.CreateYtoZWindowList (362, 33865.0, 10000.0, 832.0, 40151.0, 448.0, 1.0, 0.54);		// 256x138
	
	tp.CreateXtoYWindowList (363, 43040.0, 29512.0, 1280.0, 10288.0, 480.0, 1.0, 0.745);	// NEXUS
	tp.CreateXtoYWindowList (364, 43040.0, 28360.0, 896.0, 10320.0, 448.0, 1.0, 1.0);		// Glassboard 1
	tp.CreateXtoYWindowList (365, 43040.0, 24456.0, 896.0, 10320.0, 448.0, 1.0, 1.0);		// Glassboard 2
	tp.CreateXtoYWindowList (366, 43040.0, 7304.0, 768.0, 10256.0, 384.0, 1.0, 1.0);		// Glassboard 2
	tp.CreateXtoYWindowList (367, 42756.0, 25640.0, 2432.0, 10000.0, 902.0, 1.0, 0.742);	// KBLT
	
	tp.CreateYtoZWindowList (368, 33840.0, 9086.0, 2200.0, 4688.0, 1100.0, 1.0, 1.0);		
	tp.CreateXtoYWindowList (369, 4688.0, 31632.0, 2208.0, 9086.0, 2208.0, 1.0, 1.0);

	tp.CreateXtoYWindowList (370, 25016.0, 35458.0, 317.12, 10000.0, 660.0, 0.96, 1.0);		// Coke Machine
	tp.CreateXtoYWindowList (371, 25016.0, 35163.0, 255.0, 10000.0, 586.2, 0.867, 1.0);		// Coffee Machine
	tp.CreateXtoYWindowList (372, 25016.0, 34778.0, 350.0, 10000.0, 593.22, 0.59, 1.0);		// Sweet Machine
	// phys sci door 1
	tp.CreateYtoZWindowList (373, 34320.0, 10000.0, 832.0, 26752.0, 552.0, 1.0, 0.66);		// 256x169.85
	// phys sci toilets
	tp.CreateYtoZWindowList (374, 33872.0, 10000.0, 768.0, 28646.0, 322.0, 1.0, 0.833);		// 256x106.67 toilet doors
	// phys sci door 2
	tp.CreateYtoZWindowList (375, 34342.0, 10000.0, 832.0, 36639.0, 1216, 0.68, 1.0);		// 256x175.16

	tp.CreateXtoYWindowList (379, 43152.0, 33232.0, 384.0, 10000.0, 768.0, 1.0, 1.0);		// GCL1 doorway	
	tp.CreateXtoYWindowList (380, 43152.0, 32720.0, 384.0, 10000.0, 768.0, 1.0, 1.0);		// GCL1 doorway

	tp.CreateYtoZWindowList (381, 36047, 9422.0, 1410.0, 41127.0, 1929.0, 0.725, 1.0);	// Exit East  375x512

	tp.CreateXtoYWindowList (383, 43152.0, 11055.0, 1014.0, 10388.0, 380.0, 1.0, 0.75);	// 256x96 Library Window downstairs
	tp.CreateXtoYWindowList (384, 43152.0, 8879.0, 1014.0, 11412.0, 444.0, 1.0, 0.876);	// 256x112 Library Window upstairs
	tp.CreateXtoYWindowList (385, 43120.0, 8189.0, 614.0, 10000.0, 768.0, 0.781, 1.0);	// library door 1
	tp.CreateXtoYWindowList (386, 43152.0, 8880.0, 2072.0, 9998.0, 770.0, 1.0, 0.742);	// 256x136 library door 2
	tp.CreateXtoYWindowList (387, 43152.0, 23023.0, 1014.0, 10305.0, 464.0, 1.0, 0.914);// silver long library window
	tp.CreateXtoYWindowList (389, 43096.0, 8803.0, 77.0, 9998.0, 775.0, 0.6, 1.0);		// library post
	tp.CreateYtoZWindowList (414, 8803.0, 9998.0, 775.0, 43096.0, 77.0, 1.0, 0.5625);	// library post
	tp.CreateYtoZWindowList (422, 33872.0, 10768.0, 64.0, 28646.0, 856.0, 1.0, 1.0);	// top of toilet door female
	tp.CreateYtoZWindowList (423, 33872.0, 10768.0, 64.0, 30566.0, 840.0, 1.0, 1.0);	// top of toilet door male
	//tp.CreateYtoZWindowList (450, 2352.0, 10000.0, 896.0, 41168.0, 1792.0, 1.0, 1.0);	// west exit
	tp.CreateDisplayList (XZ, 451, 400.0, 256.0, 2352.0, 10896.0, 41168.0, 0.64, 7.0);  // above west exit
	tp.CreateXtoYWindowList (452, 41127.0, 35280.0, 320.0, 10128.0, 704.0, 0.91, 1.0);	// w 233 window by steps (end of phys sci)
	tp.CreateDisplayList (XZ, 453, 2.0, 2.0, 35856.0, 9400.0, 40500.0, 180.0, 1380.0);  // block at bottom of steps
}

// --------------------------------------------------------------------------------------
// Display grass and slopes
// --------------------------------------------------------------------------------------
void Shay::DisplayGrass ()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(GRASS));
	glCallList(79);
	glCallList(111);
	glCallList(460);
	glCallList(477);
	for (int i = 461; i < 477; i++) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(GRASS_2));
	glCallList(198);
	
	// USED IF REQUIRED DARKER HILL
	//glBindTexture(GL_TEXTURE_2D, tp.GetTexture(GRASS_HILL));
	//for (int i = 461; i < 477; i++) glCallList(i);
}

void Shay::DrawGrass ()
{
	tp.CreateDisplayList (XZ, 79, 64.0, 64.0, 4848.0, 9086.0, 3408.0, 417.5, 45.0);
	tp.CreateDisplayList (XZ, 111, 64.0, 64.0, 4848.0, 10000.0, 10000.0, 417.5, 481.5);

	// Slope ate the entrance
	tp.CreateAngledPolygon(198, 64.0, 64.0,  4848.0, 31568.0,  31568.0,  4848.0,
	                                         9086.0,  9086.0,  10000.0, 10000.0,
											 6200.0,  6200.0,  10000.0, 10000.0, 1, 1);
	// Lower hill in the centre
	tp.CreateDisplayList (XZ, 460, 64.0, 64.0, 9000.0, 10200.0, 19000.0,  203.125, 281.25);
	tp.CreateAngledPolygon(461, 64.0, 64.0,    9000.0, 22000.0, 22000.0,  9000.0,
	                                          10000.0, 10000.0, 10200.0, 10200.0,
											  17000.0, 17000.0, 19000.0, 19000.0, 1, 1);

	tp.CreateAngledPolygon(462, 64.0, 64.0, 9000.0, 22000.0, 22000.0,  9000.0,
	                                       10200.0, 10200.0, 10000.0, 10000.0,
										   37000.0, 37000.0, 40000.0, 40000.0, 1, 1);

	tp.CreateAngledPolygon(463, 64.0, 64.0,  22000.0, 27000.0, 27000.0, 22000.0,
	                                         10200.0, 10000.0, 10000.0, 10200.0,
											 19000.0, 19000.0, 37000.0, 37000.0, 1, 1);

	tp.CreateAngledPolygon(464, 64.0, 64.0,  6500.0,  9000.0,  9000.0,  6500.0,
	                                        10000.0, 10200.0, 10200.0, 10000.0,
										    19000.0, 19000.0, 37000.0, 37000.0, 1, 1);

	tp.CreateAngledPolygon(465, 64.0, 64.0,  9000.0,  9000.0,  9000.0,  6500.0,
	                                        10000.0, 10000.0, 10200.0, 10000.0,
											17000.0, 17000.0, 19000.0, 19000.0, 4, 1);
	
	tp.CreateAngledPolygon(466, 64.0, 64.0,  22000.0, 22000.0, 27000.0, 22000.0,
	                                         10000.0, 10000.0, 10000.0, 10200.0,
											 17000.0, 17000.0, 19000.0, 19000.0, 1, 1);

	tp.CreateAngledPolygon(467, 64.0, 64.0,  22000.0, 27000.0, 22000.0, 22000.0,
	                                         10200.0, 10000.0, 10000.0, 10000.0,
											 37000.0, 37000.0, 40000.0, 40000.0, 4, 1);

	tp.CreateAngledPolygon(468, 64.0, 64.0,  6500.0,  9000.0,  9000.0,  9000.0,
	                                        10000.0, 10200.0, 10000.0, 10000.0,
											37000.0, 37000.0, 40000.0, 40000.0, 1, 1);

	// higher hilltop
	tp.CreateDisplayList (XZ, 477, 64.0, 64.0, 14000.0, 10425.0, 28000.0, 62.5, 78.125);
	
	tp.CreateAngledPolygon(469, 64.0, 64.0,  14000.0, 18000.0, 18000.0, 14000.0,
	                                         10200.0, 10200.0, 10425.0, 10425.0,
											 23000.0, 23000.0, 28000.0, 28000.0, 1, 1);

	tp.CreateAngledPolygon(470, 64.0, 64.0,  14000.0, 18000.0, 18000.0, 14000.0,
	                                         10425.0, 10425.0, 10200.0, 10200.0,
											 33000.0, 33000.0, 36000.0, 36000.0, 1, 1);

	tp.CreateAngledPolygon(471, 64.0, 64.0,  10000.0, 14000.0, 14000.0, 10000.0,
	                                         10200.0, 10425.0, 10425.0, 10200.0,
											 28000.0, 28000.0, 33000.0, 33000.0, 1, 1);

	tp.CreateAngledPolygon(472, 64.0, 64.0,  18000.0, 22000.0, 22000.0, 18000.0,
	                                         10425.0, 10200.0, 10200.0, 10425.0,
											 28000.0, 28000.0, 33000.0, 33000.0, 1, 1);

	tp.CreateAngledPolygon(473, 64.0, 64.0,  14000.0, 14000.0, 14000.0, 10000.0,
	                                         10200.0, 10200.0, 10425.0, 10200.0,
											 23000.0, 23000.0, 28000.0, 28000.0, 4, 1);

	tp.CreateAngledPolygon(474, 64.0, 64.0,  18000.0, 18000.0, 22000.0, 18000.0,
	                                         10200.0, 10200.0, 10200.0, 10425.0,
											 23000.0, 23000.0, 28000.0, 28000.0, 1, 1);

	tp.CreateAngledPolygon(475, 64.0, 64.0,  18000.0, 22000.0, 18000.0, 18000.0,
	                                         10425.0, 10200.0, 10200.0, 10200.0,
											 33000.0, 33000.0, 36000.0, 36000.0, 1, 1);

	tp.CreateAngledPolygon(476, 64.0, 64.0,  10000.0, 14000.0, 14000.0, 14000.0,
	                                         10200.0, 10425.0, 10200.0, 10200.0,
											 33000.0, 33000.0, 36000.0, 36000.0, 1, 1);	
}

// --------------------------------------------------------------------------------------
// Display Light Fittings
// --------------------------------------------------------------------------------------
void Shay::DisplayLights ()
{
	// Light Fitting
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(LIGHT));
	GLdouble beamstep = 0.0;
	for (int i = 0; i < 4; i++)
	{
		glPushMatrix();
			glTranslatef(32905.0, 11200.0, 11134.0 + beamstep);
			glRotatef( 90.0, 1.0f, 0.0f, 0.0f );
			glRotatef( -90.0, 0.0f, 0.0f, 1.0f );
			glCallList(376);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(32905.0, 11265.0, 11134.0 + beamstep);
			glRotatef( 90.0, 1.0f, 0.0f, 0.0f );
			glRotatef( -90.0, 0.0f, 0.0f, 1.0f );
			glCallList(376);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(32905.0, 11330.0, 11134.0 + beamstep);
			 glRotatef( 90.0, 1.0f, 0.0f, 0.0f );
			 glRotatef( -90.0, 0.0f, 0.0f, 1.0f );
			glCallList(376);
		glPopMatrix();
		beamstep += 8492.0;
	}
	
	// Light Supports
	beamstep = 0.0;
	for (i = 0; i < 4; i++)
	{
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(LIGHT_SUPPORT_2));
		step = -40.0;
		for (int k = 0; k < 2; k++)
		{
			for (int j = 0; j < 2; j++)
			{
				glPushMatrix();
					glTranslatef(step, 0.0, 0.0 + beamstep);
					glCallList(377);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(step, 0.0, -40.0 + beamstep);
					glCallList(377);
				glPopMatrix();
				step += 8.0;
			}
			step += 64.0;
		}

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(LIGHT_SUPPORT));
		step = -40.0;
		for (k = 0; k < 2; k++)
		{
			step2 = 0.0;
			for (int j = 0; j < 2; j++)
			{
				glPushMatrix();
					glTranslatef(step, 0.0, 0.0 + step2 + beamstep);
					glCallList(378);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(step, 0.0, -40.0 + step2 + beamstep);
					glCallList(378);
				glPopMatrix();
				step2 += 8.0;
			}
			step += 80.0;
		}
		beamstep += 8492.0;
	}	
	
}

void Shay::DrawLights ()
{
	// Fittings
	glNewList(376, GL_COMPILE);
		glBegin(GL_QUADS);
			gluQuadricDrawStyle(glu_cylinder, GLU_LINE);
			gluCylinder(glu_cylinder, 75.0, 75.0, 60.0, 15, 100);
		glEnd();
	glEndList();	

	tp.CreateDisplayList (YZ, 377, 2.0, 8.0, 32900.0, 11330.0, 11150.0, 220.0, 1.0);	// supports
	tp.CreateDisplayList (XY, 378, 8.0, 2.0, 32900.0, 11330.0, 11150.0, 1.0, 220.0);	// supports
}

// --------------------------------------------------------------------------------------
// Display drainpipe and tuckshop serving counter
// --------------------------------------------------------------------------------------
void Shay::DisplayCylinders ()
{
	// drainpipe
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DRAINPIPE));
	glPushMatrix();
		glTranslatef(24200.0, 9850.0, 43090.0);
		glRotatef( 90.0, 1.0f, 0.0f, 0.0f );
		glRotatef( -90.0, 0.0f, 0.0f, 1.0f );
		glRotatef( -180.0, 0.0f, 1.0f, 0.0f );
		glScalef( 1.0, 1.0f, 1125.0f);
		glCallList(437);
	glPopMatrix();

	// serving counter
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(COUNTER_TOP));
	glCallList(439);
	glPushMatrix();
		glTranslatef(33800.0, 10340.0, 34848.0);
		glRotatef( 90.0, 1.0f, 0.0f, 0.0f );
		glRotatef( -90.0, 0.0f, 0.0f, 1.0f );
		glCallList(441);
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(COUNTER_SIDE));
		glCallList(438);
		glTranslatef(0.0, 0.0, 10.0);
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(COUNTER_TOP));
		glCallList(441);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(COUNTER_SIDE));
	glCallList(440);
	glPushMatrix();
		glTranslatef(0.0, 0.0, 276.0);
		glCallList(440);
	glPopMatrix();
	
}

void Shay::DrawCylinders ()
{
	// Drainpipe
	glNewList(437, GL_COMPILE);
		glBegin(GL_QUADS);
			gluQuadricDrawStyle(glu_cylinder, GLU_FILL);
			gluCylinder(glu_cylinder, 10.0, 10.0, 2.0, 15, 15);
		glEnd();
	glEndList();

	// Serving Counter
	glNewList(438, GL_COMPILE);
		glBegin(GL_QUADS);
			gluQuadricDrawStyle(glu_cylinder, GLU_FILL);
			gluCylinder(glu_cylinder, 138.0, 138.0, 16.0, 20, 50);
		glEnd();
	glEndList();
	glNewList(441, GL_COMPILE);
		glBegin(GL_QUADS);
			gluQuadricDrawStyle(glu_cylinder, GLU_FILL);
			gluDisk(glu_cylinder, 0.0, 138.0, 20, 50);
		glEnd();
	glEndList();
	
	tp.CreateDisplayList (XZ, 439, 1.0, 1.0, 33800.0, 10340.0, 34710.0, 120.0, 276.0);
	tp.CreateDisplayList (XY, 440, 4.0, 16.0, 33800.0, 10324.0, 34710.0, 30.0, 1.0);

}

// --------------------------------------------------------------------------------------
// Display Wall by Entrance
// --------------------------------------------------------------------------------------
void Shay::DisplayStepBricks ()
{
	step = 0.0;

	for (int j = 0; j < 2; j++)
	{
		glPushMatrix();
			glTranslatef(step, 0.0, 0.0);
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_STEPS));
			for (int i = 478; i < 487; i ++) glCallList(i);
	
			glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_STEPS_TOP));
			for (i = 488; i < 493; i ++) glCallList(i);

			glPushMatrix();
				glTranslatef(31572.0, 9222.0, 6126.0);
				glRotatef( -18.69, 1.0f, 0.0f, 0.0f );
				glTranslatef(-31572.0, -9222.0, -6126.0);
				glCallList(493);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(31572.0, 9461.0, 7213.0);
				glRotatef( -20.31, 1.0f, 0.0f, 0.0f );
				glTranslatef(-31572.0, -9462.0, -7213.0);
				glCallList(494);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(31572.0, 9722.0, 8302.0);
				glRotatef( -17.35, 1.0f, 0.0f, 0.0f );
				glTranslatef(-31572.0, -9722.0, -8302.0);
				glCallList(495);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(31572.0, 9939.0, 9332.4);
				glRotatef( -19.83, 1.0f, 0.0f, 0.0f );
				glTranslatef(-31572.0, -9942.0, -9332.4);
				glCallList(496);
			glPopMatrix();
		glPopMatrix();
		step += -64.0;
	}
	
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_STEPS_COVER));
	for (int i = 497; i < 502; i ++) glCallList(i);
	glPushMatrix();
		glTranslatef(31572.0, 9222.0, 6126.0);
		glRotatef( -18.69, 1.0f, 0.0f, 0.0f );
		glTranslatef(-31572.0, -9222.0, -6126.0);
		glCallList(502);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(31572.0, 9462.0, 7213.0);
		glRotatef( -20.21, 1.0f, 0.0f, 0.0f );
		glTranslatef(-31572.0, -9462.0, -7213.0);
		glCallList(503);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(31572.0, 9722.0, 8302.0);
		glRotatef( -17.35, 1.0f, 0.0f, 0.0f );
		glTranslatef(-31572.0, -9722.0, -8302.0);
		glCallList(504);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(31572.0, 9939.0, 9332.4);
		glRotatef( -19.83, 1.0f, 0.0f, 0.0f );
		glTranslatef(-31572.0, -9942.0, -9332.4);
		glCallList(505);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_STEPS_EDGE));
	glCallList(506);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_STEPS_EDGE_2));
	glCallList(507);
}

void Shay::DrawStepBricks ()
{
	tp.CreateDisplayList (YZ,  478.0, 128.0, 128.0, 31582.0, 9914.0, 9872.0, 1.7188, 1.75);
	tp.CreateDisplayList (YZ,  488.0, 32.0, 128.0, 31582.0, 10134.0, 9868.0, 1.0, 1.78);

	tp.CreateDisplayList (YZ,  479.0, 128.0, 128.0, 31582.0, 9530.0, 9006.0, 3.21875, 6.0);	
	tp.CreateDisplayList (YZ,  489.0, 32.0, 128.0, 31582.0, 9942.0, 9004.0, 1.0, 2.55);
	
	tp.CreateDisplayList (YZ,  480.0, 128.0, 128.0, 31582.0, 9350.0, 7918.0, 2.90625, 6.0);
	tp.CreateDisplayList (YZ,  490.0, 32.0, 128.0, 31582.0, 9722.0, 7916.0, 1.0, 3.0);
	
	tp.CreateDisplayList (YZ,  481.0, 128.0, 128.0, 31582.0, 9158.0, 6830.0, 2.375, 6.0);
	tp.CreateDisplayList (YZ,  491.0, 32.0, 128.0, 31582.0, 9462.0, 6830.0, 1.0, 2.99);

	tp.CreateDisplayList (YZ,  482.0, 128.0, 128.0, 31582.0, 8966.0, 4590.0, 2.0, 15.0);
	tp.CreateDisplayList (YZ,  492.0, 32.0, 128.0, 31582.0, 9222.0, 4590.0, 1.0, 12.0);

	tp.CreateAngledPolygon(483, 128.0, 128.0,  31582.0,  31582.0,  31582.0,  31582.0,
	                                          9094.0, 9094.0, 9462.0, 9094.0,
											  5742.0, 6830.0, 6830.0, 5742.0, 5, 1);
	tp.CreateDisplayList (YZ, 493.0, 32.0, 128.0, 31582.0, 9222.0, 6126.0, 1.0, 5.92);

	tp.CreateAngledPolygon(484, 128.0, 128.0,  31582.0,  31582.0,  31582.0,  31582.0,
	                                          9414.0, 9414.0, 9722.0, 9414.0,
											  7086.0, 7918.0, 7918.0, 7086.0, 5, 1);
	tp.CreateDisplayList (YZ, 494.0, 32.0, 128.0, 31582.0, 9462.0, 7213.0, 1.0, 5.93);

	tp.CreateAngledPolygon(485, 128.0, 128.0,  31582.0,  31582.0,  31582.0,  31582.0,
	                                          9594.0, 9594.0, 9942.0, 9722.0,
											  8302.0, 9006.0, 9006.0, 8302.0, 5, 1);
	tp.CreateDisplayList (YZ, 495.0, 32.0, 128.0, 31582.0, 9722.0, 8302.0, 1.0, 5.82);


	tp.CreateAngledPolygon(486, 128.0, 128.0,  31582.0,  31582.0,  31582.0,  31582.0,
	                                          9914.0, 9914.0, 10134.0, 9914.0,
											  9262.0, 9872.0, 9872.0, 9262.0, 5, 1);
	tp.CreateDisplayList (YZ, 496.0, 32.0, 128.0, 31582.0, 9942.0, 9332.4, 1.0, 4.545);

	tp.CreateDisplayList (XZ,  497.0, 64.0, 128.0, 31518.0, 10166.0, 9868.0, 1.0, 1.78);
	tp.CreateDisplayList (XZ,  498.0, 64.0, 128.0, 31518.0, 9974.0, 9004.0, 1.0, 2.55);
	tp.CreateDisplayList (XZ,  499.0, 64.0, 128.0, 31518.0, 9754.0, 7916.0, 1.0, 3.0);
	tp.CreateDisplayList (XZ,  500.0, 64.0, 128.0, 31518.0, 9494.0, 6830.0, 1.0, 2.99);
	tp.CreateDisplayList (XZ,  501.0, 64.0, 128.0, 31518.0, 9254.0, 4590.0, 1.0, 12.0);
	tp.CreateDisplayList (XZ, 502.0, 64.0, 128.0, 31518.0, 9254.0, 6126.0, 1.0, 5.92);
	tp.CreateDisplayList (XZ, 503.0, 64.0, 128.0, 31518.0, 9494.0, 7213.0, 1.0, 5.95);
	tp.CreateDisplayList (XZ, 504.0, 64.0, 128.0, 31518.0, 9754.0, 8302.0, 1.0, 5.82);
	tp.CreateDisplayList (XZ, 505.0, 64.0, 128.0, 31518.0, 9974.0, 9332.4, 1.0, 4.545);
	tp.CreateDisplayList (XY,  506.0, 64.0, 32.0, 31518.0, 10134.0, 10095.84, 1.0, 1.0);
	tp.CreateDisplayList (XY,  507.0, 64.0, 64.0, 31518.0, 9914.0, 10095.84, 1.0, 3.4376);
}

//--------------------------------------------------------------------------------------
//  Map and Welcome screens
//--------------------------------------------------------------------------------------
void Shay::DrawMapExit ()
{
	tp.CreateDisplayList (0, 448, 256.0, 256.0, 10.0, 10.0, 0.0, 0.855, 1.0); // map
	tp.CreateDisplayList (0, 449, 512.0, 512.0, 0.0, 0.0, 0.0, 1.0, 1.0);	  // welcome screen
	tp.CreateDisplayList (0, 454, 256.0, 64.0, 0.0, 0.0, 0.0, 1.0, 1.0);	  // welcome screen
}

//--------------------------------------------------------------------------------------
//  Create display lists
//	Numbers indicate list numbers
//--------------------------------------------------------------------------------------
void Shay::CreateTextureList()
{
	DrawGrass ();				// 79, 111, 198, 460-477
	DrawChancPosts ();			// 11-15, 235-237
	DrawDoorPosts ();			// 25-27, 199
	DrawAboveWindowBlock ();	// 20-24, 39, 43-46, 49-50, 53-56, 64-72, 95-96 208-213, 223-234, 238-239, 415, 424-425
	DrawPurplePosts ();			// 29-32
	DrawRedPosts ();			// 33-35
	DrawPhysSciPosts ();		// 16-17, 36-38, 40-42
	DrawDoorPaving ();			// 47-48
	DrawLibraryPosts ();		// 57-63, 442-447
	DrawMainPosts ();			// 18-19, 51-52
	DrawPavement ();			// 28, 73-94, 240-249, 428, 436
	DrawBricks ();				// 101-110, 112-169, 180-197, 200-201, 390-399, 430-434
	DrawRoof();					// 1-10, 97-100, 170-179, 202-205, 214-222, 250-257, 296-299, 426-427, 2046
	DrawEntranceSteps ();		// 258-295, 206-207
	DrawExtras ();				// 300-349, 388, 395, 419-421, 429, 435
	DrawLargerTextures ();		// 350-375, 379-387, 389, 414-418, 422-423, 450-453
	DrawLights ();				// 376-378
	DrawBench ();				// 400-413
	DrawStepBricks ();			// 478-507
	DrawCylinders ();			// 437-441
	DrawMapExit ();				// 448-449, 454
	// 455-459
	DrawBanner();

	DrawBoardWalkGarden();
	DrawBoardwalk440WestPaving();
	DrawBoardwalk440SouthPaving();
	DrawBoardwalk440EastPaving();
	DrawBoardwalk440NorthWall();
	DrawBoardwalk440SouthWall();
	DrawBoardwalk440EastWall();
	DrawBoardwalk440WestWall();
	DrawBoardwalk440SouthPosts();
	DrawBoardwalk440WestPosts();
	DrawBoardwalk440EastPosts();
	DrawBoardwalk440SouthBeams();
	DrawBoardwalk440WestBeams();
	DrawBoardwalk440EastBeams();
	DrawBoardwalk440SouthLintels();
	DrawBoardwalk440EastLintels();
	DrawBoardwalk440WestLintels();
	DrawBoardwalk440SouthCeiling();
	DrawBoardwalk440WestCeiling();
	DrawBoardwalk440EastCeiling();
	DrawBoardwalk440SouthWallFacade();
	DrawBoardwalk440EastFacade();
	DrawBoardwalk440WestFacade();

	DrawBoardwalk440WestFacadeLedge();
	DrawBoardwalk440EastFacadeLedge();
	DrawBoardwalk440CorridorWallEast();
	DrawBoardwalk440CorridorWallWest();

	Draw440BoardwalkEastSteps();
	Draw440BoardwalkWestSteps();

	DrawBoardwalk440EastStairwell();
	DrawBoardwalk440WestStairwell();

	Draw440RoofNorth();
	Draw440NorthExterior();
	Draw440NorthWindows();

	DrawBoardwalk440WestDoors();
	DrawBoardwalk440EastDoors();
	DrawBroadwalkSouthDoors();

	Draw440EastRoof();
	Draw440WestRoof();
	Draw440EastUpperWall();
	Draw440WestUpperWall();

	DrawBoardwalk440WestPavingStairwell();
	DrawBoardwalk440EastPavingStairwell();

	DrawBoardwalk440WestLandingStairwell();
	DrawBoardwalk440EastLandingStairwell();


}

//--------------------------------------------------------------------------------------
//  Increments frame count used for setting movement speed
//--------------------------------------------------------------------------------------
void Shay::IncrementFrameCount()
{
	double t = ((GLdouble)(clock()-lastClock))/(GLdouble)CLOCKS_PER_SEC;  
	frameCount ++;
	
	// reset after t
	if (t > 0.1)
	{
		stepIncrement = t/frameCount * 1400;
		angleIncrement = t/frameCount;
		frameCount = 0;
		lastClock = clock();
	}
}

//============================================
// BoardwalkGarden
//============================================
void Shay::DisplayBoardWalkGarden()
{

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(GRASS));
	//glTranslatef(step-1600.00+128.00, 0.00, 10080.00);
	glCallList(2001);
	glPopMatrix();

}

void Shay::DrawBoardWalkGarden()
{
	//tp.CreateDisplayList(XY, 460, 64.0, 64.0, 0.0, 11000.0, 50000.0, 50.0, 50.0);
	tp.CreateDisplayList(XZ, 2001, 64.0, 64.0, -19049.0, 10000.0, 31550.0, 251.0, 148.0);
}

//============================================
// Boardwalk Roof
//============================================
void Shay::DisplayBWRoofSouth()
{


	// Library Roof 2
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_BEAM_1));
	step = -35000;
	for (i = 0; i < 70; i++)
	{
		glPushMatrix();
		glTranslatef(step, 1300.0, -200);
		glCallList(296);
		glPopMatrix();
		step += 388.0;
	}

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_TOP_LIB));
	glPushMatrix();
	glTranslatef(-35000, 1300, -200);
	glCallList(216);
	glPopMatrix();

	//New Roof
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_BEAM_1));
	step = -35000.0;
	for (i = 0; i < 70; i++)
	{
		glPushMatrix();
		glTranslatef(step, 1300.0, -200);
		glCallList(297);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(step + 32.0, 1300.0, -200);
		glCallList(297);
		glPopMatrix();

		step += 388.0;
	}

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_PLANKS_2));
	glPushMatrix();
	glTranslatef(-35000, 1300, -200);
	glCallList(257);
	glPopMatrix();
}

void Shay::DisplayBWRoofEast()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_TOP));
	glCallList(2310);
}

void Shay::DisplayBWRoofWest()
{
	step = -23000;
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_TOP));
	glCallList(2311);
}

void Shay::Display440RoofNorth()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_TOP));
	glCallList(2320);
	glCallList(2321);
}

void Shay::Draw440RoofNorth()
{
	// south side
	glNewList(2320, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(-20952.0 - 128*3, 14392.96 - 141.5, 31550.0 + 128*3);
			glTexCoord2f(0.0, 257.9);
			glVertex3f(-20952.0 + 128*155.0 + 128*3, 14392.96 - 141.5, 31550.0 + 128*3);
			glTexCoord2f(2.0, 273.4);
			glVertex3f(-20952.0 + 128*155.0 + 128*3, 14392.96+776.72, 31550.0-2108.0);
			glTexCoord2f(2.0, 0.0);
			glVertex3f(-20952.0 - 128*3, 14392.96+776.72, 31550.0-2108.0);
		glEnd();
	glEndList();
	// north side
	glNewList(2321, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(-20952.0 - 128 * 3, 14392.96 - 141.5, 27334.0 - 128*3);
			glTexCoord2f(0.0, 257.9);
			glVertex3f(-20952.0 + 128*155.0 + 128 * 3, 14392.96 - 141.5, 27334.0 - 128*3);
			glTexCoord2f(2.0, 273.4);
			glVertex3f(-20952.0 + 128*155.0 + 128 * 3, 14392.96+776.72, 27334.0+2108.0);
			glTexCoord2f(2.0, 0.0);
			glVertex3f(-20952.0 - 128 * 3, 14392.96+776.72, 27334.0+2108.0);
		glEnd();
	glEndList();
}

//--------------------------------------------------------------------------------------
//  Boardwalk Paving 
//--------------------------------------------------------------------------------------
void Shay::DisplayBoardwalk440WestPaving()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENT));
	glCallList(2002);

}

void Shay::DrawBoardwalk440WestPaving()
{
	tp.CreateDisplayList(XZ, 2002, 128.0, 256.0, -20952.0, 10000.0, 31550.0, 15.0, 37.0);	// 440 west paving closest wall to canteen
}

//--------------------------------------------------------------------------------------
//  Boardwalk Paving 
//--------------------------------------------------------------------------------------
void Shay::DisplayBoardwalk440SouthPaving()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENT));
	glCallList(2003);
}

void Shay::DrawBoardwalk440SouthPaving()
{
	tp.CreateDisplayList(XZ, 2003, 128.0, 256.0, -25030.0, 10000.0, 41025.0, 216.0, 8.0);	// the boardwalk

}

//--------------------------------------------------------------------------------------
//  Boardwalk Paving 
//--------------------------------------------------------------------------------------
void Shay::DisplayBoardwalk440EastPaving()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENT));
	glCallList(2004);

}

void Shay::DrawBoardwalk440EastPaving()
{
	tp.CreateDisplayList(XZ, 2004, 128.0, 256.0, -2982.0, 10000.0, 31550.0, 14.0, 37.0);	// 440 east paving closest wall to canteen
}

//--------------------------------------------------------------------------------------
//  Boardwalk Wall
//--------------------------------------------------------------------------------------
void Shay::DisplayBoardwalk440NorthWall()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_XY));
	glCallList(2005);
}

void Shay::DrawBoardwalk440NorthWall()
{
	tp.CreateDisplayList(XY, 2005, 128.0, 128.0, -20952.0, 10000.0, 31550.0, 155.0, 34.32);	// 440 North wall
}

//--------------------------------------------------------------------------------------
//  Boardwalk Wall
//--------------------------------------------------------------------------------------
void Shay::DisplayBoardwalk440SouthWall()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_XY));
	glCallList(2006);

}

void Shay::DrawBoardwalk440SouthWall()
{
	tp.CreateDisplayList(XY, 2006, 128.0, 128.0, -25030.0, 10000.0, 43000.0, 214.0, 18.0);	// 440 South wall
}

//--------------------------------------------------------------------------------------
//  Boardwalk Wall
//--------------------------------------------------------------------------------------
void Shay::DisplayBoardwalk440EastWall()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_YZ));
	glCallList(2007);

}

void Shay::DrawBoardwalk440EastWall()
{
	tp.CreateDisplayList(YZ, 2007, 128.0, 128.0, -1192.0, 10000.0, 31550.0, 20.71, 63.82);	// 440 East wall

}

//--------------------------------------------------------------------------------------
//  Boardwalk Wall
//--------------------------------------------------------------------------------------
void Shay::DisplayBoardwalk440WestWall()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_YZ));
	glCallList(2008);

}

void Shay::DrawBoardwalk440WestWall()
{
	tp.CreateDisplayList(YZ, 2008, 128.0, 128.0, -20952.0, 10000.0, 31550.0, 20.71, 63.82);	// 440 West wall

}

void Shay::DisplayBoardwalk440SouthPosts()
{
	GLfloat intraPost;

	intraPost = 0;
	for (int ii = 0; ii < 8; ii++)
	{
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST_2));
		glPushMatrix();
		glTranslatef(intraPost, 0.00, 0.00);
		glCallList(2009);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(intraPost, 0.00, 128.0);
		glCallList(2009);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST_2));
		glPushMatrix();
		glTranslatef(intraPost, 0.0, 0.0);
		glCallList(2010);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(intraPost + 128.0, 0.0, 0.0);
		glCallList(2010);
		glPopMatrix();

		intraPost += 2280;
	}

}

void Shay::DrawBoardwalk440SouthPosts()
{
	tp.CreateDisplayList(XY, 2009, 128.0, 256.0, -19052.0, 10000.0, 41025.0, 1.0, 4.48);
	tp.CreateDisplayList(YZ, 2010, 256.0, 128.0, -19052.0, 10000.0, 41025.0, 4.48, 1.0);


	//tp.CreateDisplayList(XY, 2011, 128.0, 256.0, -19052.0, 13000.0, 41050.0, 1.0, 6.2);		
	//tp.CreateDisplayList(YZ, 2012, 256.0, 128.0, -19052.0, 13000.0, 41050.0, 6.2, 1.0);		
}

void Shay::DisplayBoardwalk440WestPosts()
{
	GLfloat intraPost;

	intraPost = 0;
	for (int ii = 0; ii < 5; ii++)
	{
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST));
		glPushMatrix();
		glTranslatef(0.0, 0.00, intraPost);
		glCallList(2011);
		glCallList(2011);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 0.00, 128.0 + intraPost);
		glCallList(2011);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST));
		glPushMatrix();
		glTranslatef(0.0, 0.0, intraPost);
		glCallList(2012);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(128.00, 0.0, intraPost);
		glCallList(2012);
		glPopMatrix();

		intraPost -= 1900;
	}

}

void Shay::DrawBoardwalk440WestPosts()
{
	tp.CreateDisplayList(XY, 2011, 128.0, 256.0, -19052.0 - 128.0, 10000.0, 41025.0 - 128.0, 1.0, 10.35);
	tp.CreateDisplayList(YZ, 2012, 256.0, 128.0, -19052.0 - 128.0, 10000.0, 41025.0 - 128.0, 10.35, 1.0);


	//tp.CreateDisplayList(XY, 2011, 128.0, 256.0, -19052.0, 13000.0, 41050.0, 1.0, 6.2);		
	//tp.CreateDisplayList(YZ, 2012, 256.0, 128.0, -19052.0, 13000.0, 41050.0, 6.2, 1.0);		
}

void Shay::DisplayBoardwalk440EastPosts()
{
	GLfloat intraPost;

	intraPost = 0;
	for (int ii = 0; ii < 5; ii++)
	{
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST));
		glPushMatrix();
		glTranslatef(0.0, 0.00, intraPost);
		glCallList(2013);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 0.00, 128.0 + intraPost);
		glCallList(2013);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST));
		glPushMatrix();
		glTranslatef(0.0, 0.0, intraPost);
		glCallList(2014);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(128.00, 0.0, intraPost);
		glCallList(2014);
		glPopMatrix();

		intraPost -= 1900;
	}

}

void Shay::DrawBoardwalk440EastPosts()
{
	tp.CreateDisplayList(XY, 2013, 128.0, 256.0, -3092.0 + 128.0, 10000.0, 41025.0 - 128.0, 1.0, 10.35);
	tp.CreateDisplayList(YZ, 2014, 256.0, 128.0, -3092.0 + 128.0, 10000.0, 41025.0 - 128.0, 10.35, 1.0);


	//tp.CreateDisplayList(XY, 2011, 128.0, 256.0, -19052.0, 13000.0, 41050.0, 1.0, 6.2);		
	//tp.CreateDisplayList(YZ, 2012, 256.0, 128.0, -19052.0, 13000.0, 41050.0, 6.2, 1.0);		
}

void Shay::DisplayBoardwalk440SouthBeams()
{
	GLfloat intraPost;

	intraPost = 0;
	for (int ii = 0; ii < 8; ii++)
	{
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST_2));
		glPushMatrix();
		glTranslatef(intraPost, 0.00, 0.00);
		glCallList(2015);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(intraPost, 0.00, 128.0);
		glCallList(2015);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST_2));
		glPushMatrix();
		glTranslatef(intraPost, 0.0, 0.0);
		glCallList(2016);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(intraPost + 128.0, 0.0, 0.0);
		glCallList(2016);
		glPopMatrix();

		intraPost += 2280;
	}

}

void Shay::DrawBoardwalk440SouthBeams()
{
	tp.CreateDisplayList(XZ, 2015, 128.0, 256.0, -19052.0, 10000.0 + 1140.0, 41025.0, 1.0, 8.0);
	tp.CreateDisplayList(YZ, 2016, 128.0, 256.0, -19052.0, 10000.0 + 1140.0, 41025.0, 1.0, 8.0);
	//tp.CreateDisplayList(ZY_PLAIN, 2016, 256.0, 128.0, -19052.0, 10000.0+1140.0, 41050.0, 1.0, 8.0);


	//tp.CreateDisplayList(XY, 2011, 128.0, 256.0, -19052.0, 13000.0, 41050.0, 1.0, 6.2);		
	//tp.CreateDisplayList(YZ, 2012, 256.0, 128.0, -19052.0, 13000.0, 41050.0, 6.2, 1.0);		
}

void Shay::DisplayBoardwalk440WestBeams()
{
	GLfloat intraPost;

	intraPost = 0;
	for (int ii = 0; ii < 5; ii++)
	{
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST));
		glPushMatrix();
		glTranslatef(0.0, 0.00, intraPost);
		glCallList(2017);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 0.00, 0.0 + intraPost);
		glCallList(2017);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST));
		glPushMatrix();
		glTranslatef(0.0, 0.0, intraPost);
		glCallList(2018);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.00, 0.0, 128.0 + intraPost);
		glCallList(2018);
		glPopMatrix();

		intraPost -= 1900;
	}

}

void Shay::DrawBoardwalk440WestBeams()
{
	tp.CreateDisplayList(XZ, 2017, 256.0, 128.0, -19052.0 - 1900.00, 10000.0 + 1140.0, 41025.0 - 128.0, 7.42, 1.0);
	tp.CreateDisplayList(XY, 2018, 256.0, 128.0, -19052.0 - 1900.00, 10000.0 + 1140.0, 41025.0 - 128.0, 7.42, 1.0);


	//tp.CreateDisplayList(XY, 2011, 128.0, 256.0, -19052.0, 13000.0, 41050.0, 1.0, 6.2);		
	//tp.CreateDisplayList(YZ, 2012, 256.0, 128.0, -19052.0, 13000.0, 41050.0, 6.2, 1.0);		
}

void Shay::DisplayBoardwalk440EastBeams()
{
	GLfloat intraPost;

	intraPost = 0;
	for (int ii = 0; ii < 5; ii++)
	{
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST));
		glPushMatrix();
		glTranslatef(0.0, 0.00, intraPost);
		glCallList(2019);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 0.00, +intraPost);
		glCallList(2019);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST));
		glPushMatrix();
		glTranslatef(0.0, 0.0, intraPost);
		glCallList(2020);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0, 0.0, 128.0 + intraPost);
		glCallList(2020);
		glPopMatrix();

		intraPost -= 1900;
	}

}

void Shay::DrawBoardwalk440EastBeams()
{
	tp.CreateDisplayList(XZ, 2019, 256.0, 128.0, -3093.0 + 128.0, 10000.0 + 1140.0, 41025.0 - 128.0, 7.0, 1.0);
	tp.CreateDisplayList(XY, 2020, 256.0, 128.0, -3093.0 + 128.0, 10000.0 + 1140.0, 41025.0 - 128.0, 7.0, 1.0);
}

void Shay::DisplayBoardwalk440SouthLintels()
{
	GLfloat intraPost;

	intraPost = 0;
	for (int ii = 0; ii < 7; ii++)
	{
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST_2));
		glPushMatrix();
		glTranslatef(intraPost, 0.00, 0.00);
		glCallList(2021);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(intraPost, 128.00, 0.0);
		glCallList(2021);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST_2));
		glPushMatrix();
		glTranslatef(intraPost, 0.0, 0.0);
		glCallList(2022);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(intraPost, 0.0, 128.0);
		glCallList(2022);
		glPopMatrix();

		intraPost += 2280;
	}

}

void Shay::DrawBoardwalk440SouthLintels()
{
	tp.CreateDisplayList(XZ, 2021, 256.0, 128.0, -19052.0, 10000.0 + 1140.0, 41025.0, 9.32, 2.0);
	tp.CreateDisplayList(XY, 2022, 256.0, 128.0, -19052.0, 10000.0 + 1140.0, 41025.0, 9.32, 2.0);
}

void Shay::DisplayBoardwalk440EastLintels()
{
	GLfloat intraPost;

	intraPost = 0;
	for (int ii = 0; ii < 5; ii++)
	{
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST));
		glPushMatrix();
		glTranslatef(0.0, 0.00, intraPost);
		glCallList(2023);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 128.0, intraPost);
		glCallList(2023);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST));
		glPushMatrix();
		glTranslatef(0.0, 0.0, intraPost);
		glCallList(2024);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(128.0, 0.0, intraPost);
		glCallList(2024);
		glPopMatrix();

		intraPost -= 1900;
	}

}

void Shay::DrawBoardwalk440EastLintels()
{
	tp.CreateDisplayList(XZ, 2023, 128.0, 256.0, -3093.0 + 128.0, 10000.0 + 1140.0, 41025.0 - 2280.0 + 384.0, 2.0, 7.42);
	tp.CreateDisplayList(YZ, 2024, 128.0, 256.0, -3093.0 + 128.0, 10000.0 + 1140.0, 41025.0 - 2280.0 + 384.0, 2.0, 7.42);
}

void Shay::DisplayBoardwalk440WestLintels()
{
	GLfloat intraPost;

	intraPost = 0;
	for (int ii = 0; ii < 5; ii++)
	{
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST));
		glPushMatrix();
		glTranslatef(0.0, 0.00, intraPost);
		glCallList(2025);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 128.0, intraPost);
		glCallList(2025);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST));
		glPushMatrix();
		glTranslatef(0.0, 0.0, intraPost);
		glCallList(2026);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(128.0, 0.0, intraPost);
		glCallList(2026);
		glPopMatrix();

		intraPost -= 1900;
	}

}

void Shay::DrawBoardwalk440WestLintels()
{
	tp.CreateDisplayList(XZ, 2025, 128.0, 256.0, -19052.0 - 128.0, 10000.0 + 1140.0, 41025.0 - 2280.0 + 384.0, 2.0, 7.42);
	tp.CreateDisplayList(YZ, 2026, 128.0, 256.0, -19052.0 - 128.0, 10000.0 + 1140.0, 41025.0 - 2280.0 + 384.0, 2.0, 7.42);
}

//--------------------------------------------------------------------------------------
//  Boardwalk Paving 
//--------------------------------------------------------------------------------------
void Shay::DisplayBoardwalk440SouthCeiling()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_XY));
	glCallList(2027);
}

void Shay::DrawBoardwalk440SouthCeiling()
{
	tp.CreateDisplayList(XZ, 2027, 128.0, 256.0, -25030.0, 10000.0 + 1140.0 + 128.0, 41025.0, 216.0, 8.0);	// the boardwalk
}

//--------------------------------------------------------------------------------------
//  Boardwalk Paving 
//--------------------------------------------------------------------------------------
void Shay::DisplayBoardwalk440WestCeiling()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_XY));
	glCallList(2028);

}

void Shay::DrawBoardwalk440WestCeiling()
{
	tp.CreateDisplayList(XZ, 2028, 128.0, 256.0, -20952.0, 10000.0 + 1140.0 + 128.0, 31550.0, 15.0, 37.0);	// 440 west paving closest wall to canteen
}

//--------------------------------------------------------------------------------------
//  Boardwalk Paving 
//--------------------------------------------------------------------------------------
void Shay::DisplayBoardwalk440EastCeiling()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_XY));
	glCallList(2029);

}

void Shay::DrawBoardwalk440EastCeiling()
{
	tp.CreateDisplayList(XZ, 2029, 128.0, 256.0, -2982.0, 10000.0 + 1140.0 + 128.0, 31550.0, 14.0, 37.0);	// 440 east paving closest wall to canteen
}

//--------------------------------------------------------------------------------------
//  Boardwalk Wall
//--------------------------------------------------------------------------------------
void Shay::DisplayBoardwalk440SouthWallFacade()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_XY));
	glCallList(2030);

}

void Shay::DrawBoardwalk440SouthWallFacade()
{
	tp.CreateDisplayList(XY, 2030, 128.0, 128.0, -25030.0, 10000.0 + 1140.0 + 128.0 + 128.0 - 20.0, 43000.0 - 2048.0 + 50.0, 214.0, 9.91);	// 440 South wall
}

void Shay::DisplayBoardwalk440EastFacade()
{
	GLfloat intraPost;

	intraPost = 0;
	for (int ii = 0; ii < 5; ii++)
	{
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST));
		glPushMatrix();
		glTranslatef(0.0, 0.00, intraPost);
		glCallList(2031);
		glPopMatrix();

		intraPost -= 1900;
	}

}

void Shay::DrawBoardwalk440EastFacade()
{
	//tp.CreateDisplayList(XZ, 2023, 128.0, 256.0, -3093.0 + 128.0, 10000.0 + 1140.0, 41025.0 - 2280.0 + 384.0, 2.0, 7.42);
	tp.CreateDisplayList(YZ, 2031, 128.0, 256.0, -3093.0 + 128.0, 10000.0 + 1140.0 + 128.0 + 128.0 + 128.0, 41025.0 - 2280.0 + 384.0, 2.0, 7.42);
}

void Shay::DisplayBoardwalk440WestFacade()
{
	GLfloat intraPost;

	intraPost = 0;
	for (int ii = 0; ii < 5; ii++)
	{

		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST));
		glPushMatrix();
		glTranslatef(0.0, 0.00, intraPost);
		glCallList(2032);
		glPopMatrix();

		intraPost -= 1900;
	}

}

void Shay::DrawBoardwalk440WestFacade()
{
	//tp.CreateDisplayList(XZ, 2025, 128.0, 256.0, -19052.0 - 128.0, 10000.0 + 1140.0, 41025.0 - 2280.0 + 384.0, 2.0, 7.42);
	tp.CreateDisplayList(YZ, 2032, 128.0, 256.0, -19052.0, 10000.0 + 1140.0 + 128.0 + 128.0 + 128.0, 41025.0 - 2280.0 + 384.0, 2.0, 7.42);
}

void Shay::DisplayBoardwalk440WestFacadeLedge()
{
	GLfloat intraPost;

	intraPost = 0;
	for (int ii = 0; ii < 5; ii++)
	{
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST_2));
		glPushMatrix();
		glTranslatef(0.0, 0.00, intraPost);
		glCallList(2033);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0, 64.0, intraPost);
		glCallList(2033);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0, 0.00, intraPost);
		glCallList(2034);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(128.0, 0.0, intraPost);
		glCallList(2034);
		glPopMatrix();

		intraPost -= 1900;
	}

}

void Shay::DrawBoardwalk440WestFacadeLedge()
{
	tp.CreateDisplayList(XZ, 2033, 128.0, 256.0, -19052.0 - 64, 10000.0 + 1140.0 + 128.0 + 128.0 + 128.0 + 128.0 + 128.0, 41025.0 - 2280.0 + 384.0, 1, 7.42);
	tp.CreateDisplayList(YZ, 2034, 128.0, 256.0, -19052.0 - 64, 10000.0 + 1140.0 + 128.0 + 128.0 + 128.0 + 128.0 + 128.0, 41025.0 - 2280.0 + 384.0, 0.5, 7.42);
}

void Shay::DisplayBoardwalk440EastFacadeLedge()
{
	GLfloat intraPost;

	intraPost = 0;
	for (int ii = 0; ii < 5; ii++)
	{
		glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST_2));
		glPushMatrix();
		glTranslatef(0.0, 0.00, intraPost);
		glCallList(2035);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0, 64.0, intraPost);
		glCallList(2035);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0, 0.00, intraPost);
		glCallList(2036);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(128.0, 0.0, intraPost);
		glCallList(2036);
		glPopMatrix();

		intraPost -= 1900;
	}

}

void Shay::DrawBoardwalk440EastFacadeLedge()
{
	tp.CreateDisplayList(XZ, 2035, 128.0, 256.0, -3093.0 + 64, 10000.0 + 1140.0 + 128.0 + 128.0 + 128.0 + 128.0 + 128.0, 41025.0 - 2280.0 + 384.0, 1, 7.42);
	tp.CreateDisplayList(YZ, 2036, 128.0, 256.0, -3093.0 + 64, 10000.0 + 1140.0 + 128.0 + 128.0 + 128.0 + 128.0 + 128.0, 41025.0 - 2280.0 + 384.0, 0.5, 7.42);
}

//--------------------------------------------------------------------------------------
//  Corridor Wall East
//--------------------------------------------------------------------------------------
void Shay::DisplayBoardwalk440CorridorWallEast()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_XY));
	glCallList(2300);
}

void Shay::DrawBoardwalk440CorridorWallEast()
{
	tp.CreateDisplayList(XY, 2300, 128.0, 128.0, -1192.0, 10000.0, 41160.0, 29.69, 20.71);
}

//--------------------------------------------------------------------------------------
//  Corridor Wall West
//--------------------------------------------------------------------------------------

void Shay::DisplayBoardwalk440CorridorWallWest()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_XY));
	glCallList(2301);
}

void Shay::DrawBoardwalk440CorridorWallWest()
{
	tp.CreateDisplayList(XY, 2301, 128.0, 128.0, -25029.0, 10000.0, 41027.0, 31.87, 20.71);
}

//--------------------------------------------------------------------------------------
// Display Steps
//--------------------------------------------------------------------------------------
void Shay::Display440BoardwalkEastSteps()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BOARDWALK_440_STEP_XY));
	for (int i = 2110; i < 2120; i++) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BOARDWALK_440_STEP_XY));
	for (int i = 2120; i < 2130; i++) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BOARDWALK_440_STEP_XY));
	for (int i = 2130; i < 2140; i++) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BOARDWALK_440_STEP_XY));
	for (int i = 2140; i < 2150; i++) glCallList(i);
}

void Shay::Draw440BoardwalkEastSteps()
{
	//first flight stairs
	step = 10000.0+640.0;
	stepLength = 0.0;
	for (int i = 2100; i < 2110; i++)
	{
		tp.CreateDisplayList(XZ, i + 10, 64, 128.0, -1192.0 + 576.0 + stepLength, step, 40860.0 -570.0, 1, 4.45);
		tp.CreateDisplayList(YZ, i + 20, 64.0, 128.0, -1192.0 + 576.0 + stepLength, step - 64.0 , 40860.0 -570.0, 1, 4.45);
		//tp.CreateDisplayList(YZ, i + 200, 32.0, 64.0, -5005.0 + stepLength, step - 64.0 + 32.0, 35000, 1, 17.82);
		step -= 64.0;
		stepLength -= 64.0;
		
	}

	// second flight stairs
	step = 10000+1280.0;
	stepLength = 0.0;
	for (i = 2100; i < 2110; i++)
	{
		tp.CreateDisplayList(XZ, i + 30, 64.0, 128.0, -1192.0 - stepLength, step, 40860.0 -1140.0, 1, 4.45);
		tp.CreateDisplayList(YZ, i + 40, 64.0, 128.0, -1192.0 - stepLength + 64.0, step - 64.0, 40860.0 -1140.0, 1, 4.45);
		step -= 64.0;
		stepLength -= 64.0;
	}
	
	// steps next to GCL1
	//tp.CreateDisplayList(XZ, 206, 128.0, 1024.0, 34508.0, 10000.0, 41127, 1.0, 0.942);
	//tp.CreateDisplayList(XZ, 207, 256.0, 1024.0, 34352.0, 10000.0, 41127, 0.609, 0.942);
}

void Shay::Display440BoardwalkWestSteps()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BOARDWALK_440_STEP_XY));
	for (int i = 2210; i < 2220; i++) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BOARDWALK_440_STEP_XY));
	for (int i = 2220; i < 2230; i++) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BOARDWALK_440_STEP_XY));
	for (int i = 2230; i < 2240; i++) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BOARDWALK_440_STEP_XY));
	for (int i = 2240; i < 2250; i++) glCallList(i);
}

void Shay::Draw440BoardwalkWestSteps()
{
	//first flight stairs
	step = 10000.0 + 1280;
	stepLength = 0.0;
	for (int i = 2200; i < 2210; i++)
	{
		tp.CreateDisplayList(XZ, i + 10, 64.0, 128.0, -20952.0 - 64.0+ stepLength, step, 40860.0 - 1140.0, 1, 4.45);
		tp.CreateDisplayList(YZ, i + 20, 64.0, 128.0, -20952.0 - 64.0+ stepLength, step - 64.0, 40860.0 - 1140.0, 1, 4.45);
		//tp.CreateDisplayList(YZ, i + 200, 32.0, 64.0, -5005.0 + stepLength, step - 64.0 + 32.0, 35000, 1, 17.82);
		step -= 64.0;
		stepLength -= 64.0;

	}

	// second flight stairs
	step = 10000 + 640.0;
	stepLength = 0.0;
	for (i = 2200; i < 2210; i++)
	{
		tp.CreateDisplayList(XZ, i + 30, 64.0, 128.0, -20952.0 - 640.0 - stepLength, step, 40860.0 - 570.0, 1, 4.45);
		tp.CreateDisplayList(YZ, i + 40, 64.0, 128.0, -20952.0 - 640.0 - stepLength + 64.0, step - 64.0, 40860.0 - 570.0, 1, 4.45);
		step -= 64.0;
		stepLength -= 64.0;
	}

	// steps next to GCL1
	//tp.CreateDisplayList(XZ, 206, 128.0, 1024.0, 34508.0, 10000.0, 41127, 1.0, 0.942);
	//tp.CreateDisplayList(XZ, 207, 256.0, 1024.0, 34352.0, 10000.0, 41127, 0.609, 0.942);
}

//--------------------------------------------------------------------------------------
//  Boardwalk Stairwell
//--------------------------------------------------------------------------------------
void Shay::DisplayBoardwalk440EastStairwell()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_YZ));
	glCallList(2039);
	glCallList(2042);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_XY));
	glCallList(2040);
	glCallList(2041);
	

}

void Shay::DrawBoardwalk440EastStairwell()
{
	tp.CreateDisplayList(YZ, 2039, 128.0, 128.0, -1192.0, 10000.0, 40860.0, 20.71, 2.48);
	tp.CreateDisplayList(XY, 2040, 128.0, 128.0, -1192.0, 10000.0, 40860.0, 8.91, 20.71);
	tp.CreateDisplayList(XY, 2041, 128.0, 128.0, -1192.0, 10000.0, 40860.0 -1140.0, 8.91, 20.71);	// 440 East Stairwell
	tp.CreateDisplayList(YZ, 2042, 128.0, 128.0, -1192.0 + 1140.0, 10000.0, 40860.0 - 1140.0, 20.71, 8.91);
}

//--------------------------------------------------------------------------------------
//  Boardwalk Stairwell
//--------------------------------------------------------------------------------------
void Shay::DisplayBoardwalk440WestStairwell()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_YZ));
	glCallList(2043);
	glCallList(2044);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_XY));
	glCallList(2045);
	glCallList(2046);

}

void Shay::DrawBoardwalk440WestStairwell()
{
	tp.CreateDisplayList(YZ, 2043, 128.0, 128.0, -20952.0, 10000.0, 40860.0, 20.71, 1.48);
	tp.CreateDisplayList(YZ, 2044, 128.0, 128.0, -20952.0 - 1140.0, 10000.0, 40860.0 - 1140.0, 20.71, 8.91);
	tp.CreateDisplayList(XY, 2045, 128.0, 128.0, -20952.0 - 1140.0, 10000.0, 40860.0, 8.91, 20.71);
	tp.CreateDisplayList(XY, 2046, 128.0, 128.0, -20952.0 - 1140.0, 10000.0, 40860.0 - 1140.0, 8.91, 20.71);	// 440 West wall
}

//--------------------------------------------------------------------------------------
// Broadwalk doors
//--------------------------------------------------------------------------------------
void Shay::DisplayBoardwalk440WestDoors()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BOARDWALK_440_1M_DOOR_YZ));
	glCallList(2047);
	glCallList(2048);
	glCallList(2049);
	glCallList(2050);
}

void Shay::DrawBoardwalk440WestDoors()
{
	tp.CreateDisplayList(YZ, 2047, 640.0, 320.0, -20905.0, 10000.0, 31550.0 + 380.0, 1, 1);
	tp.CreateDisplayList(YZ, 2048, 640.0, 320.0, -20905.0, 10000.0, 31550.0 + 1140.0, 1, 1);
	tp.CreateDisplayList(YZ, 2049, 640.0, 320.0, -20905.0, 10000.0, 31550.0 + 3420.0, 1, 1);
	tp.CreateDisplayList(YZ, 2050, 640.0, 320.0, -20905.0, 10000.0, 31550.0 + 5700.0, 1, 1);
}

void Shay::DisplayBoardwalk440EastDoors()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BOARDWALK_440_1M_DOOR_YZ));
	glCallList(2051);
	glCallList(2052);
	glCallList(2053);
	glCallList(2054);
}

void Shay::DrawBoardwalk440EastDoors()
{
	tp.CreateDisplayList(YZ, 2051, 640.0, 320.0, -1232.0, 10000.0, 31550.0 + 3040.0, 1, 1);
	tp.CreateDisplayList(YZ, 2052, 640.0, 320.0, -1232.0, 10000.0, 31550.0 + 5700.0, 1, 1);
	tp.CreateDisplayList(YZ, 2053, 640.0, 320.0, -1232.0, 10000.0, 31550.0 + 7600.0, 1, 1);
}

void Shay::DisplayBroadwalkSouthDoors() {
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BOARDWALK_440_1M_DOOR_XY));
	for (i = 2055; i < 2061; i++) {
		glCallList(i);
	}

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BOOKSHOP_WINDOW_1));
	glCallList(2061);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BOOKSHOP_WINDOW_2));
	glCallList(2062);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BOOKSHOP_DOOR));
	glCallList(2063);
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BOOKSHOP_WINDOW_3));
	glCallList(2064);
}

void Shay::DrawBroadwalkSouthDoors() {
	//tp.CreateDisplayList(XYZ, listNo, xImgSize, zImgSize, xStart, yStart, zStart, xTimes, zTime);
	//tp.CreateDisplayList(XY, 2006, 128.0, 128.0, -25030.0, 10000.0, 43000.0, 214.0, 18.0);	// 440 South wall
	tp.CreateDisplayList(XY_FLIP, 2055, 320.0, 640.0, -22370, 10000.0, 42950.0, 1, 1); //Door 1
	tp.CreateDisplayList(XY_FLIP, 2056, 320.0, 640.0, -21290, 10000.0, 42950.0, 1, 1); //Door 2
	tp.CreateDisplayList(XY_FLIP, 2057, 320.0, 640.0, -17930, 10000.0, 42950.0, 1, 1); //Door 3
	tp.CreateDisplayList(XY_FLIP, 2058, 320.0, 640.0, -14950, 10000.0, 42950.0, 1, 1); //Door 4
	tp.CreateDisplayList(XY_FLIP, 2059, 320.0, 640.0, -12730, 10000.0, 42950.0, 1, 1); //Door 5
	tp.CreateDisplayList(XY_FLIP, 2060, 320.0, 640.0, -9750, 10000.0, 42950.0, 2, 1); //Door 6
	tp.CreateDisplayList(XY, 2061, 1520.0, 760.0, -6450, 10000.0, 42950.0, 1, 1); //Bookshop window 1
	tp.CreateDisplayList(XY, 2062, 1900.0, 760.0, -2650, 10000.0, 42950.0, 1, 1); //Bookshop window 2
	tp.CreateDisplayList(XY, 2063, 760.0, 760.0, -730, 10000.0, 42950.0, 1, 1);	  //Bookshop doors
	tp.CreateDisplayList(XY, 2064, 380.0, 760.0, 30, 10000.0, 42950.0, 1, 1);   //Bookshop window 3

}

//--------------------------------------------------------------------------------------
//  440 North Section Exterior
//--------------------------------------------------------------------------------------

void Shay::Display440NorthExterior()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_XY));
	glCallList(2325);

	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_YZ));
	glCallList(2326);
}

void Shay::Draw440NorthExterior()
{
	tp.CreateDisplayList(XY, 2325, 128.0, 128.0, -20952.0, 10000.0, 27334.0, 155.0, 34.32); //north wall
	tp.CreateDisplayList(YZ, 2326, 128.0, 128.0, -1112.0, 10000.0, 27334.0, 34.32, 32.9375); //east wall
}

void Shay::Display440NorthWindows()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BOARDWALK_440_WINDOW));
	for (int floor = 0; floor < 3; floor++)
	{
		for (int window = 0; window < 14; window++)
		{
			glPushMatrix();
				glTranslatef(1004*window, 1450*floor, 0);
				glCallList(2330);
			glPopMatrix();
		}
	}

	glPushMatrix();
		glTranslatef(1004 * -1, 1450 * 2, 0); //top left window
		glCallList(2330);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1004 * 14, 1450 * 2, 0); //top right window
		glCallList(2330);
	glPopMatrix();
}

void Shay::Draw440NorthWindows()
{
	GLdouble windWidth = 460; 
	GLdouble windHeight = 640;
	glNewList(2330, GL_COMPILE);
		glBegin(GL_POLYGON);
			glTexCoord2f(0.0, 1.0); //bottom right
			glVertex3f(-17500.0, 10500, 31590.0); 
			glTexCoord2f(1.0, 1.0); //top right
			glVertex3f(-17500.0+windWidth, 10500, 31590.0); 
			glTexCoord2f(1.0, 0.0); //top left
			glVertex3f(-17500.0+windWidth, 10500+windHeight, 31590.0); 
			glTexCoord2f(0.0, 0.0); //bottom left
			glVertex3f(-17500.0, 10500+windHeight, 31590.0);
		glEnd();
	glEndList();
}

void Shay::Draw440EastRoof()
{
	GLfloat roofLength = 9472.0;
	GLfloat roofRatio = 0.368;
	GLfloat roofWidth = 2188;
	GLfloat roofHeight = roofWidth * roofRatio;

	glNewList(2310, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); //bottom left
			glVertex3f(-3300.0, 12564.0, 31550.0);
			glTexCoord2f(0.0, roofLength/128); //bottom right
			glVertex3f(-3300.0, 12564.0, 31550.0 + roofLength);
			glTexCoord2f(1.0, roofLength/128); //top right
			glVertex3f(-3300.0 + roofWidth, 12564.0 + roofHeight, 31550.0 + roofLength);
			glTexCoord2f(1.0, 0.0); //top left
			glVertex3f(-3300.0 + roofWidth, 12564.0 + roofHeight, 31550.0);
		glEnd();
	glEndList();
}

void Shay::Draw440WestRoof()
{
	GLfloat roofLength = 9472.0;
	GLfloat roofRatio = -0.368;
	GLfloat roofWidth = -2252;
	GLfloat roofHeight = roofWidth * roofRatio; 
	
	glNewList(2311, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0); //bottom left
			glVertex3f(-18700.0, 12600.0, 31550.0);
			glTexCoord2f(0.0, roofLength/128); //bottom right
			glVertex3f(-18700.0, 12600.0, 31550.0 + roofLength);
			glTexCoord2f(1.0, roofLength/128); //top right
			glVertex3f(-18700.0 + roofWidth, 12600.0 + roofHeight, 31550.0 + roofLength);
			glTexCoord2f(1.0, 0.0); //top left
			glVertex3f(-18700.0 + +roofWidth, 12600.0 + roofHeight, 31550.0);
		glEnd();
	glEndList();
}

void Shay::Display440EastUpperWall() //across the top of the east balcony, above the stairwell doorframe
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_YZ));
	glCallList(2315);
}

void Shay::Draw440EastUpperWall()
{
	tp.CreateDisplayList(YZ, 2315, 128, 128, -1192.0, 12650.88, 31550.0, 689.0/128, 9472.0/128);
}

void Shay::Display440WestUpperWall() //across the top of the west balcony, above the stairwell doorframe
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_YZ));
	glCallList(2316);
}

void Shay::Draw440WestUpperWall()
{
	tp.CreateDisplayList(YZ, 2316, 128, 128, -20952.0, 12650.88, 31550.0, 777.0 / 128, 9472.0 / 128);
}
//--------------------------------------------------------------------------------------
//  Boardwalk Paving Stairwell West
//--------------------------------------------------------------------------------------
void Shay::DisplayBoardwalk440WestPavingStairwell()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENT));
	glCallList(2065);

}

void Shay::DrawBoardwalk440WestPavingStairwell()
{
	tp.CreateDisplayList(XZ, 2065, 128.0, 256.0, -20952.0 - 1140.0, 10000.0, 40860.0 - 1140.0, 8.91, 4.45);	// 440 west paving closest wall to canteen
}

//--------------------------------------------------------------------------------------
//  Boardwalk Paving Stairwell East
//--------------------------------------------------------------------------------------
void Shay::DisplayBoardwalk440EastPavingStairwell()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENT));
	glCallList(2066);

}

void Shay::DrawBoardwalk440EastPavingStairwell()
{
	tp.CreateDisplayList(XZ, 2066, 128.0, 256.0, -1192.0, 10000.0, 40860.0 - 1140.0, 8.91, 4.45);	// 440 west paving closest wall to canteen
}

//--------------------------------------------------------------------------------------
//  Boardwalk Paving Landing East
//--------------------------------------------------------------------------------------
void Shay::DisplayBoardwalk440EastLandingStairwell()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENT));
	glCallList(2067);

}

void Shay::DrawBoardwalk440EastLandingStairwell()
{
	tp.CreateDisplayList(XZ, 2067, 128.0, 256.0, -1192.0 + 640.0, 10000.0 + 640.0, 40860.0 - 1140.0, 3.56, 4.45);	// 440 west paving closest wall to canteen
}

//--------------------------------------------------------------------------------------
//  Boardwalk Paving Landing West
//--------------------------------------------------------------------------------------
void Shay::DisplayBoardwalk440WestLandingStairwell()
{
	glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENT));
	glCallList(2068);

}

void Shay::DrawBoardwalk440WestLandingStairwell()
{
	tp.CreateDisplayList(XZ, 2068, 128.0, 256.0, -20952.0 -1140.0 + 64.0, 10000.0 + 640.0, 40860.0 - 1140.0, 3.56, 4.45);	// 440 west paving closest wall to canteen
}
