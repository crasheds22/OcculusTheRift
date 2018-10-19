#pragma once
class GUI
{
	public:
		GUI(Game * inputParent);
		~GUI();

		void Init();
		void DrawGUI();
		void DrawReticle();
	

	private:
		Game * theParent;
		std::vector<GLuint> temp;

};

