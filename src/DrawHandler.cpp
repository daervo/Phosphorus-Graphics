
#include "../headers/SuperHeader.h"

#include "../headers/Draw.h"
#include "../headers/Textures.h"

GLint theta;
GLfloat xrot, yrot, zrot = 0.0f;
void drawHandle(HDC hDC, meshLoader* scene, std::map<std::string, GLuint*> textureIdMap)
{
/* OpenGL animation code goes here */
	unsigned int program=glCreateProgram();

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
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();				// Reset MV Matrix


	glRotatef(theta, 1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glScaled(0.05, 0.05, 0.05);
	glTranslated(0.0, 0.0, 1.0);
	scene->draw(textureIdMap);


	glPopMatrix();
	glFlush();
	glFinish();

	SwapBuffers(hDC);
	theta++;
}
