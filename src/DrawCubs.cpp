#include "../headers/SuperHeader.h"

void drawCube(){
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, 0.5f);
			glVertex3f(-0.5f, -0.5f, 0.5f);
			glVertex3f(-0.5f, 0.5f, 0.5f);

		glColor3f(1.0f, 1.0f, 0.0f);
			glVertex3f(0.5f, 0.5f, -0.5f);
			glVertex3f(0.5f, -0.5f, -0.5f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f(-0.5f, 0.5f, -0.5f);

		glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(0.5f, 0.5f, -0.5f);
			glVertex3f(-0.5f, 0.5f, -0.5f);
			glVertex3f(-0.5f, 0.5f, 0.5f);

		glColor3f(0.0f, 1.0f, 1.0f);
			glVertex3f(0.5f, -0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, -0.5f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f(-0.5f, -0.5f, 0.5f);

		glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, -0.5f);
			glVertex3f(0.5f, 0.5f, -0.5f);

		glColor3f(1.0f, 0.0f, 1.0f);
			glVertex3f(-0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, -0.5f, 0.5f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f(-0.5f, 0.5f, -0.5f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
}

