
#include <gl/glut.h>
#include "Game.h"
#include "GUI.h"



GUI::GUI(Game * inputParent)
{
	theParent = inputParent;
	
}


GUI::~GUI()
{
	
}

void GUI::Init()
{
	
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

	//glClear(GL_STENCIL_BUFFER_BIT);

	//Assign Texture
	
	std::vector<unsigned char> temp = theParent->GetTexture()[20].GetTexture();
	//glEnable(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
	//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	//glEnable(GL_STENCIL_TEST);
	//glEnable(GL_ALPHA_TEST);
	
	
	//glStencilMask(0x0);
	//glStencilFunc(GL_NOTEQUAL, 0x1, 0x1);
	//glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); 
	//glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	//glDepthMask(GL_FALSE);
	
	//glAlphaFunc(GL_GREATER, 0.05);
	// draw stencil pattern
	//glStencilMask(8);
	
	

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
	

	//glStencilFunc(GL_NOTEQUAL, 0x0, 0x0);
	//glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	//glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	//glDepthMask(GL_TRUE);

	//glDisable(GL_ALPHA_TEST);
	//glDisable(GL_STENCIL_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	//glDisable(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, 1, 1.0, 250000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
}
