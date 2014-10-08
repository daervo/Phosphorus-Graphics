#include "../headers/SuperHeader.h"

#include "../headers/Draw.h"
#include "../headers/Textures.h"
#include "../headers/mat4.h"

GLfloat theta;
float matrix[16];
mat4* proj = new mat4();
void drawHandle(HDC hDC, const std::vector<meshLoader*>& scenes, std::map<std::string, GLuint*> textureIdMap, Camera* camera, vector3d* position)
{
	/* OpenGL animation code goes here */

	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);		 // Enables Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glDepthFunc(GL_LEQUAL);			// The Type Of Depth Test To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculation

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_NORMALIZE);
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();				// Reset MV Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-0.5, 0.5, -0.5, 0.5, -0.25, 20);
	glFrustum(-0.5, 0.5, -0.5, 0.5, 5, 100);

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
			scenes[0]->draw(textureIdMap);
		glPopMatrix();
		glPushMatrix();
			glTranslated(0.5, 0.5, 0.5);
			glScaled(0.05, 0.05, 0.05);
			scenes[1]->draw(textureIdMap);


		glPopMatrix();
		glPushMatrix();
			glTranslated(-0.5, -0.5, -0.5);
			glScaled(0.05, 0.05, 0.05);
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
	//glTranslatef(0.0, 0.0, 0.01);
	//glRotatef(theta, 0.0, 1.0, 0.0);

	glFlush();
	glFinish();

	SwapBuffers(hDC);
	theta+=0.002;
}

void setOrthographicPrjoection(mat4* matrix, GLfloat r, GLfloat l, GLfloat t, GLfloat b, GLfloat f, GLfloat n)
{
	matrix->setRight(1/r, 0, 0);
	matrix->setUp(0, 1/t, 0);
	matrix->setForward(0, 0, -2/(f-n));
	matrix->setPosition(0, 0, -(f+n)/(f-n));
}
