#ifndef SHAY_H
#define SHAY_H

#include <math.h>
#include <gl/glut.h>
#include <time.h>

#include "Shay/texturedPolygons.h"
#include "Shay/camera.h"
#include "Shay/Model_Shay.h"


class Game;

#define PI 3.1415962654

// TEXTURE IMAGE AXISES
#define XY		0
#define XZ		1
#define YZ		2
#define YZ_FLIP 3
#define XY_FLIP 4

// PLAIN TYPES
#define FLAT_PLAIN	0
#define XY_PLAIN	1
#define ZY_PLAIN	2

// TEXTURES
// Grass Textures
#define GRASS						1
#define GRASS_2						2
#define GRASS_HILL					3
// Pavement Textures
#define PAVEMENT					4
#define PAVEMENT_TOP				5
#define PAVEMENTSIDE_LEFT			6
#define PAVEMENTSIDE_RIGHT			7
#define PAVEMENTSIDE_TOP			8
#define PAVEMENT_CORNER_1			9
#define PAVEMENT_CORNER_2			10
#define PAVEMENT_FLIP				11
#define PAVEMENT_TOP_FLIP			12
#define PAVEMENT_16					13
#define DOORPAVE_1					14
// Wall Brick Textures
#define WALL_BRICK_YZ				15
#define WALL_BRICK_XY				16
#define WALL_BRICK_XY_87WIDTH		17
#define WALL_BRICK_GAP_YZ			18
#define WALL_BRICK_GAP2_YZ			19
#define	WALL_BRICK_USD_YZ			20
#define WALL_BRICK_XY_END			21
#define WALL_BRICK_YZ_END			22
#define	WALL_GAP_1					23
#define WALL_BRICK_3_4				24
#define SHADOW_BRICK				25
#define WALL_BRICK_SEC_SIGN			216
// Window Post Textures
#define WINDOWPOST_CHANC_FRONT		26
#define WINDOWPOST_CHANC_RIGHT	    27
#define WINDOWPOST_CHANC_LEFT	    28
#define WINDOWLEDGE_CHANC_FRONT		29
#define WINDOWLEDGE_CHANC_TOP		30
#define WINDOWPOST_PHYSSCI_FRONT	31
#define WINDOWPOST_PHYSSCI_RIGHT	32
#define WINDOWPOST_PHYSSCI_LEFT		33
#define	WINDOWPOST_LIB_FRONT		34
#define	WINDOWPOST_LIB_LEFT			35
#define	WINDOWPOST_LIB_RIGHT		36
// Door Post Textures
#define DOOR_POST_SECURITY			37
// Window Ledge Textures
#define WINDOWLEDGE_PS_FRONT		38
#define WINDOWLEDGE_PS_TOP			39
#define WINDOWLEDGE_PS_BOTT			40
#define WINDOWLEDGE_LIB_A			41
#define WINDOWLEDGE_LIB_B			42
#define WINDOWLEDGE_LIB_TOP_A		43
#define WINDOWLEDGE_LIB_TOP_B		44
#define WINDOW_LEDGE_END_1			45
#define WINDOW_LEDGE_END_2			46
// Main Post Textures
#define	MAIN_POST					47
#define	MAIN_POST_2					48
// Door Post Textures
#define DOOR_POST_CHANC				49
#define DOOR_SIDEPOST_CHANC			50
#define DOOR_POST_LIB				215
// Coloured Posts Textures
#define PURPLE_POST					51
#define PURPLE_POSTSIDE				52
#define RED_POST					53
#define RED_POSTSIDE				54
// Roof Textures
#define ROOF_TOP					55
#define ROOF_TOP_LIB				56
#define ROOF_PLANKS					57
#define ROOF_BEAM_1					58
#define ROOF_PLANKS_2				59
#define ROOF_BEAM_2					60
#define BELOW_ROOF_FILL				61
#define ROOF_BEAM_3					62
#define ROOF_BEAM_4					63
#define ROOF_BEAM_3_TOP				64
// KBLT Textures
#define KBLT						65
#define KBLT_EDGE					66
#define KBLT_EDGE_2					67
#define KBLT_EDGE_CORNER			68
#define KBLT_SIDE_1					69
#define KBLT_SIDE_2					70
// Sign and Other Textures
#define NEXUS_SIGN					71
#define NEXUS_SIDE					72
#define SECURITY_SIGN				73
#define SECURITY_SIGN_2				74
#define SIGN_1						75
#define SIGN_1_SIDE_1				76
#define SIGN_1_SIDE_2				77
#define SIGN_2						78
#define SIGN_2_SIDE					79
#define PSC_SIGN					80
#define PSC_SIGN_2					81
#define CO_SIGN						82
#define STA_TRAVEL					83
#define STA_TRAVEL_EDGE				84
#define STA_TRAVEL_BRACKET			85
#define STA_TRAVEL_2				86
#define STA_TRAVEL_BOTTOM			87
#define TOILET_MEN					88
#define TOILET_WOMEN				89
#define GS_SIGN						90
#define GS_SIGN_2					91
#define GS_SIGN_EDGE				92
#define MAP_2						93
#define GLASS_BOARD					94
#define GLASS_BOARD_2				95
#define GLASS_BOARD_3				96
#define GLASS_B_SIDE				97
#define RUSTY_MAN					98
#define NO_SMOKE_SIGN				99
#define CARPET						100
// Drinks Machine Textures
#define DRINKS_SIDE					101
#define DRINKS_TOP					102
#define DRINKS_EDGE					103
#define DRINKS_SIDE_2				104
#define COKE_MACHINE				105
#define COFFEE_MACHINE				106
#define SWEET_MACHINE				107
#define MACHINE_SIDES				108
#define MACHINE_SIDES_2				109
// Telephone Box Textures
#define TELEPHONE_BACK				110
#define TELEPHONE_FRONT				111
#define TELEPHONE_SIDE_1			112
#define TELEPHONE_FRONT_2			113
#define TELEPHONE_MAIN_SIDE			114
#define TELEPHONE_TOP_1				115
#define TELEPHONE_SIDE_2			116
#define TELEPHONE_TOP_2				117
#define TELEPHONE_BOTTOM			118
#define TELEPHONE_FILL				119
#define TELEPHONE_FRONT_3			120
// Step Textures
#define STEPS_LIBRARY				121
#define STEPS_LIBRARY_TOP			122
#define	STEP_PAVING_1				123
#define	STEP_EDGE					124
// Larger Window and Door Textures Etc
#define WINDOW_1					125
#define WINDOW_2					126
#define WINDOW_3					127
#define WINDOW_4					128
#define WINDOW_5					129
#define WINDOW_6					130
#define WINDOW_7					131
#define WINDOW_8					132
#define WINDOW_9					133
#define WINDOW_10					134
#define WINDOW_11					135
#define WINDOW_12					136
#define WINDOW_13					137
#define WINDOW_14					138
#define WINDOW_14B					139
#define WINDOW_15					140
#define WINDOW_16					141
#define WINDOW_17					142
#define WINDOW_2B					143
#define WINDOW_2C					144
#define WINDOW_2US					145
#define WINDOW_3B					146
#define WINDOW_2USB					147
#define WINDOW_LIB_1				148
#define WINDOW_LIB_1A				149
#define WINDOW_LIB_1B				150
#define WINDOW_LIB_1C				151
#define WINDOW_LIB_US_A				152
#define WINDOW_LIB_US_B				153
#define WINDOW_LIB_DOOR_1			154
#define WINDOW_LIB_DOOR_2			155
#define WINDOW_LIB_LONG				156
#define ENTRANCE					157
#define ENTRANCE_2					158
#define EXIT_EAST					159
#define EXIT_WEST					220
#define CHANC_DOOR_1				160
#define CHANC_DOOR_2				161
#define WINDOW_2D					162
#define WINDOW_2E					163
#define WINDOW_1B					164
#define STEP_WINDOW					221
// Above Window Block Textures
#define ABOVE_WINDOW_BLOCK			165
#define ABOVE_WINDOW_BLOCK_2		166
#define ABOVE_WINDOW_BLOCK_3		167
#define ABOVE_WINDOW_EDGE_3B		168
#define ABOVE_WINDOW_BLOCK_XY_3		169
#define	ABOVE_LIB					170
#define	ABOVE_UNDER_POSTS			171
#define ABOVE_UNDER_POSTS_2			172
#define ABOVE_WINDOW_UNDER_LIB		173
#define ABOVE_WINDOW_BLOCK_CHANC	174
#define ABOVE_WINDOW_EDGE_3B_LIB	175
#define ABOVE_WINDOW_EDGE_4B_LIB	176
#define ABOVE_UNDER_4B				177
#define ABOVE_CHANC_TEXT			178
#define ABOVE_CHANC_TEXT_2			179
#define ABOVE_PHYS_SCI_TEXT			180
#define ABOVE_CHANC_TEXT_3			181
#define ABOVE_LIB_TEXT				182
#define ABOVE_LIB_TEXT_2			183
#define ABOVE_TICKETS_TEXT			184
#define ABOVE_CHANC_EDGE			185
#define TOILET_DOOR_TOP				186
// Light Fitting Textures
#define LIGHT						187
#define	LIGHT_SUPPORT				188
#define	LIGHT_SUPPORT_2				189
// Bench Textures
#define BENCH_TOP					190
#define BENCH_SIDE					191
#define BENCH_SIDE_2				192
#define BENCH_EDGE					193
#define BENCH_EDGE_TOP				194
#define BENCH_EDGE_SIDE				195
#define BENCH_EDGE_TOP_2			196
#define BENCH_EDGE_2				197
#define BENCH_EDGE_3				198
// Ticket Counter and Ledge Textures
#define TICKET_COUNTER_TOP			200
#define TICKET_COUNTER_EDGE			201
#define TICKET_COUNTER_EDGE_2		202
#define TICKET_COUNTER_EDGE_3		203
#define TICKET_LEDGE				204
#define TICKET_LEDGE_EDGE			205
#define TICKET_LEDGE_EDGE_2			206
// Wall by Steps Textures
#define WALL_BRICK_STEPS_TOP		207
#define WALL_BRICK_STEPS			208
#define WALL_BRICK_STEPS_COVER		209
#define WALL_BRICK_STEPS_EDGE		210
#define WALL_BRICK_STEPS_EDGE_2		211
// Extra Textures
#define DRAINPIPE					212
#define COUNTER_TOP					213
#define COUNTER_SIDE				214
// Welcome, Exit and Map Screens
#define MAP							217
#define WELCOME						218
#define EXIT						219
#define NO_EXIT						222
//Banner
#define THE_BANNER					223

#define BOARDWALK_440_STEP_XY		224
#define BOARDWALK_440_STEP_YZ		225
#define BOARDWALK_440_STEPTOPSTRIPE_XY 226
#define BOARDWALK_440_STEPTOPSTRIPE_YZ 227
#define BOARDWALK_440_1M_DOOR_XY	228
#define BOARDWALK_440_1M_DOOR_YZ	229

#define BOARDWALK_440_WINDOW		230

#define BOOKSHOP_DOOR				231
#define BOOKSHOP_WINDOW_1			232
#define BOOKSHOP_WINDOW_2			233
#define BOOKSHOP_WINDOW_3			234

class Shay {
public:
	Shay(Game * ownerIn);
	virtual ~Shay();

	Game* owner;

	void Draw();

	void Init();

	void DownKey(unsigned char key, int x, int y);
	void UpKey(unsigned char key, int x, int y);
	void MouseClick(int button, int state, int x, int y);

	void SetWidthHeight(int w, int h);

	// calls display functions below to draw the backdrops
	void DrawBackdrop();
	// functions to display display lists (images) and bind them to a texture
	void DisplayAboveWindowBlock ();
	void DisplayBench ();
	void DisplayBricks ();
	void DisplayChancPosts ();
	void DisplayCylinders ();
	void DisplayDoorPaving ();
	void DisplayDoorPosts ();
	void DisplayEntranceSteps ();
	void DisplayExtras ();
	void DisplayGrass ();
	void DisplayLargerTextures ();
	void DisplayLibraryPosts ();
	void DisplayMainPosts ();
	void DisplayPavement ();
	void DisplayPhysSciPosts ();
	void DisplayPurplePosts ();
	void DisplayRedPosts ();
	void DisplayRoof();
	void DisplayStepBricks ();
	void DisplayLights ();

	void DisplayBanner();

	//---------------------------------------------------
	// Broadwalk
	void DisplayBoardWalkGarden();
	void DisplayBoardwalk440WestPaving();
	void DisplayBoardwalk440SouthPaving();
	void DisplayBoardwalk440EastPaving();
	void DisplayBoardwalk440NorthWall();
	void DisplayBoardwalk440SouthWall();
	void DisplayBoardwalk440EastWall();
	void DisplayBoardwalk440WestWall();
	void DisplayBoardwalk440SouthPosts();
	void DisplayBoardwalk440WestPosts();
	void DisplayBoardwalk440EastPosts();
	void DisplayBoardwalk440SouthBeams();
	void DisplayBoardwalk440WestBeams();
	void DisplayBoardwalk440EastBeams();
	void DisplayBoardwalk440SouthLintels();
	void DisplayBoardwalk440EastLintels();
	void DisplayBoardwalk440WestLintels();
	void DisplayBoardwalk440SouthCeiling();
	void DisplayBoardwalk440WestCeiling();
	void DisplayBoardwalk440EastCeiling();
	void DisplayBoardwalk440SouthWallFacade();
	void DisplayBoardwalk440EastFacade();
	void DisplayBoardwalk440WestFacade();

	void DisplayBoardwalk440CorridorWallEast();
	void DisplayBoardwalk440CorridorWallWest();

	void DisplayBoardwalk440WestFacadeLedge();
	void DisplayBoardwalk440EastFacadeLedge();

	void Display440BoardwalkEastSteps();
	void Display440BoardwalkWestSteps();

	void DisplayBoardwalk440EastStairwell();
	void DisplayBoardwalk440WestStairwell();

	void DisplayBWRoofSouth();
	void DisplayBWRoofEast();
	void DisplayBWRoofWest();
	void Display440RoofNorth();

	void Display440NorthExterior();
	void Display440NorthWindows();

	void DisplayBoardwalk440WestDoors();
	void DisplayBoardwalk440EastDoors();
	void DisplayBroadwalkSouthDoors();

	void Display440EastUpperWall();
	void Display440WestUpperWall();

	void DisplayBoardwalk440WestPavingStairwell();
	void DisplayBoardwalk440EastPavingStairwell();

	void DisplayBoardwalk440EastLandingStairwell();
	void DisplayBoardwalk440WestLandingStairwell();

	//---------------------------------------------------

	// calls functions to create display lists (below)
	void CreateTextureList();
	// creates display lists
	void DrawGrass ();
	void DrawChancPosts ();
	void DrawDoorPosts ();
	void DrawPurplePosts ();
	void DrawRedPosts ();
	void DrawMainPosts ();
	void DrawAboveWindowBlock ();
	void DrawDoorPaving ();
	void DrawPhysSciPosts ();
	void DrawLibraryPosts ();
	void DrawBricks ();
	void DrawPavement ();
	void DrawExtras ();
	void DrawRoof();
	void DrawEntranceSteps ();
	void DrawLargerTextures ();
	void DrawLights ();
	void DrawBench ();
	void DrawCylinders ();
	void DrawAngledRoofBeam (int listNo, GLdouble x, GLdouble y, GLdouble z, GLdouble beamSize);
	void DrawAngledRoofBeam2 (int listNo, GLdouble x, GLdouble y, GLdouble z, GLdouble beamSize);
	void DrawStepBricks ();
	void DrawMapExit ();

	void DrawBanner();

	//-----------------------------------------------------
	// Broadwalk
	void DrawBoardWalkGarden();
	void DrawBoardwalk440WestPaving();
	void DrawBoardwalk440SouthPaving();
	void DrawBoardwalk440EastPaving();
	void DrawBoardwalk440NorthWall();
	void DrawBoardwalk440SouthWall();
	void DrawBoardwalk440EastWall();
	void DrawBoardwalk440WestWall();
	void DrawBoardwalk440SouthPosts();
	void DrawBoardwalk440WestPosts();
	void DrawBoardwalk440EastPosts();
	void DrawBoardwalk440SouthBeams();
	void DrawBoardwalk440WestBeams();
	void DrawBoardwalk440EastBeams();
	void DrawBoardwalk440SouthLintels();
	void DrawBoardwalk440EastLintels();
	void DrawBoardwalk440WestLintels();
	void DrawBoardwalk440SouthCeiling();
	void DrawBoardwalk440WestCeiling();
	void DrawBoardwalk440EastCeiling();
	void DrawBoardwalk440SouthWallFacade();
	void DrawBoardwalk440EastFacade();
	void DrawBoardwalk440WestFacade();
	void DrawBoardwalk440CorridorWallEast();
	void DrawBoardwalk440CorridorWallWest();

	void DrawBoardwalk440EastFacadeLedge();
	void DrawBoardwalk440WestFacadeLedge();
	
	void Draw440BoardwalkEastSteps();
	void Draw440BoardwalkWestSteps();

	void DrawBoardwalk440EastStairwell();
	void DrawBoardwalk440WestStairwell();

	void Draw440RoofNorth();
	void Draw440NorthExterior();
	void Draw440NorthWindows();

	void DrawBoardwalk440WestDoors();
	void DrawBoardwalk440EastDoors();
	void DrawBroadwalkSouthDoors();

	void Draw440EastRoof();
	void Draw440WestRoof();
	void Draw440EastUpperWall();
	void Draw440WestUpperWall();

	void DrawBoardwalk440WestPavingStairwell();
	void DrawBoardwalk440EastPavingStairwell();

	void DrawBoardwalk440EastLandingStairwell();
	void DrawBoardwalk440WestLandingStairwell();

	//-----------------------------------------------------

	// loads images and creates texture
	void CreateTextures();
	// creates bounding boxes for collsion detection
	void CreateBoundingBoxes();
	// creates different plains
	void CreatePlains();

	// deletes image and clears memory
	void DeleteImageFromMemory(unsigned char* tempImage);

	void IncrementFrameCount();
private:
	//Models
	ModelShay * statBase;
	ModelShay * portalMod;

	

	float rot = 0;

	// varibles used for tarnslating graphics etc
	GLdouble step, step2, stepLength;

	// Glut Cylinder
	GLUquadricObj *glu_cylinder;

	// Stores raw image file
	unsigned char* image = NULL;

	// display campus map
	bool DisplayMap = false;
	// display welcome screen
	bool DisplayWelcome = true;
	// display exit screen
	bool DisplayExit = false;
	// display light fittings
	bool lightsOn;

	// objects
	Camera cam;
	TexturedPolygons tp;

	GLdouble stepIncrement;
	GLdouble angleIncrement;
	int frameCount = 0;
	clock_t lastClock = 0;

	int width, height;
	bool hasSwitched = false;
	int i, j, k;
};

#endif
