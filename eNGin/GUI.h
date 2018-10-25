#ifndef GUI_h
#define GUI_h

/**
 *	@class GUI
 *	@brief Defines the look of the users GUI
 *
 *	@author Rebecca Lim
 *	@date 17-10-2018
 *	@version 1.0
 */
class GUI
{
public:
	/**
	 *	A constructor with parameters
	 *	Initiliases values with those passed in
	 */
	GUI(Game * inputParent);

	/**
	 *	Draws the gui scrren for the player to see
	 */
	void DrawGUI();

	/**
	 *	Draws the reticule in the centre of the screen
	 */
	void DrawReticle();
	
private:
	Game * theParent; /*<! The owner of the GUI instance */
};

#endif
