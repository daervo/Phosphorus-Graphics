#include "../headers/SuperHeader.h"

#include "../headers/Draw.h"
#include "../headers/Textures.h"
#include "../headers/mat4.h"

GLfloat theta;
float matrix[16];
void drawHandle(HDC hDC, std::vector<meshLoader*> scenes, std::map<std::string, GLuint*> textureIdMap, mat4* viewMatrix, vector3d* position)
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

	glPushMatrix();
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glTranslatef(position->x, position->y, position->z);


		glPushMatrix();
			glTranslated(position->x, position->y, position->z);
			glRotatef(theta, viewMatrix->getUp().x, viewMatrix->getUp().y, viewMatrix->getUp().z);
			glScaled(0.05, 0.05, 0.05);
			scenes[0]->draw(textureIdMap);
		glPopMatrix();
		glPushMatrix();
			glRotatef(theta, viewMatrix->getUp().x, viewMatrix->getUp().y, viewMatrix->getUp().z);
			glTranslated(0.5, 0.5, 0.5);
			glScaled(0.05, 0.05, 0.05);
			scenes[1]->draw(textureIdMap);


		glPopMatrix();
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glMultMatrixf(viewMatrix->getFloat());
	//glTranslatef(0.0, 0.0, 0.01);
	//glRotatef(theta, 0.0, 1.0, 0.0);
	glFlush();
	glFinish();

	SwapBuffers(hDC);
	theta+=0.002;
}
