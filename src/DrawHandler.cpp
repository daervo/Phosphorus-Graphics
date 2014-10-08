#include "../headers/SuperHeader.h"

#include "../headers/Draw.h"
#include "../headers/Textures.h"

GLfloat theta;
float matrix[16];
void drawHandle(HDC hDC, const std::vector<meshLoader*>& scenes, std::map<std::string, GLuint*> textureIdMap, Camera* camera){
	/* OpenGL animation code goes here */

	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);		 // Enables Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glDepthFunc(GL_LEQUAL);			// The Type Of Depth Test To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculation

	//set up lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_NORMALIZE);
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//set Ortho or Frustum
	//glOrtho(-0.5, 0.5, -0.5, 0.5, -0.25, 20);
	glFrustum(-0.5, 0.5, -0.5, 0.5, 5, 100);

	//draw objects
	glPushMatrix();
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(camera->getPosition().x, camera->getPosition().y, camera->getPosition().z, camera->getLookAt().x,
					camera->getLookAt().y, camera->getLookAt().z, camera->getUp().x, camera->getUp().y, camera->getUp().z);


		glPushMatrix();
			glTranslated(0.0, -0.5, -1.0);
			//glRotatef(theta, 1.0, 0, 0);
			glScaled(0.05, 0.05, 0.05);
			//drawCube();
			scenes[1]->draw(textureIdMap);
		glPopMatrix();
		glPushMatrix();
			glTranslated(0.5, 0.5, 0.5);
			glScaled(0.1, 0.1, 0.1);
			scenes[1]->draw(textureIdMap);


		glPopMatrix();
		glPushMatrix();
			glTranslated(-0.5, -0.5, -0.5);
			glScaled(0.5, 0.5, 0.5);
			scenes[1]->draw(textureIdMap);


		glPopMatrix();
		glPushMatrix();
			glTranslated(-0.5, 0.5, 0.5);
			glScaled(0.05, 0.05, 0.05);
			scenes[1]->draw(textureIdMap);


		glPopMatrix();
		glPushMatrix();
			glTranslated(0.5, -0.5, 0.5);
			glScaled(0.05, 0.05, 0.05);
			scenes[1]->draw(textureIdMap);


		glPopMatrix();
		glPushMatrix();
			glTranslated(0.5, 0.5, -0.5);
			glScaled(0.05, 0.05, 0.05);
			scenes[1]->draw(textureIdMap);


		glPopMatrix();
	glPopMatrix();

	glFlush();
	glFinish();

	SwapBuffers(hDC);
}

