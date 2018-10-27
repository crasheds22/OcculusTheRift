#include <gl/glut.h>
#include <pch.h>
#include "Game.h"
#include "GUI.h"

GUI::GUI(Game * inputParent)
{
	theParent = inputParent;
}

void GUI::DrawGUI()
{
	//Set View mode to orthographic
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-8.0, 8.0, -5.0, 5.0, 1.0, 30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Assign Texture
	std::vector<unsigned char> temp = theParent->GetTexture()[0].GetTexture();
	glEnable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, theParent->GetTexture()[0].GetWidth(), theParent->GetTexture()[0].GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, &temp[0]);

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

void GUI::DrawReticle()
{
	//Set View mode to orthographic
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-8.0, 8.0, -5.0, 5.0, 1.0, 30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Assign Texture
	std::vector<unsigned char> temp = theParent->GetTexture()[20].GetTexture();
	//glEnable(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
	//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, theParent->GetTexture()[20].GetWidth(), theParent->GetTexture()[20].GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, &temp[0]);

	//Draw Crosshair
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(-1.0, 1.0);
			glVertex3f(-0.5, -0.5, -1);
			glTexCoord2f(-1.0, 0.0);
			glVertex3f(-0.5, 0.5, -1);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(0.5, 0.5, -1);
			glTexCoord2f(0.0, 1.0);
			glVertex3f(0.5, -0.5, -1);
		glEnd();
	glPopMatrix();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	//glDisable(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, 1.0 * glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT), 1.0, 400.0);
	//gluPerspective(60.0, 1, 1.0, 250000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
