
#include "SuperHeader.h"

#include "Draw.h"

GLint theta;

void drawHandle(HDC hDC, meshLoader* scene){
/* OpenGL animation code goes here */
	unsigned int program=glCreateProgram();

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        glPushMatrix();


        glRotatef(theta, 1.0f, 1.0f, 1.0f);

        //draw();
        scene->draw(program);


        glPopMatrix();
        glFlush();
        glFinish();

        SwapBuffers(hDC);

        theta++;
}
