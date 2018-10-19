#pragma once
class GUI
{
	public:
		GUI(Game * inputParent);
		~GUI();

		void Init();
		void DrawGUI();
		void DrawReticle();
		void DrawReticleSOIL();

	private:
		Game * theParent;
		std::vector<GLuint> temp;

};

