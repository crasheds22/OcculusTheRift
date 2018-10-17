#pragma once
class GUI
{
	public:
		GUI(Game * inputParent);
		~GUI();

		void DrawGUI();
		void DrawReticle();


	private:
		Game * theParent;

};

