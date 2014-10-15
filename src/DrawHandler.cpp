/*
 * DrawHandler.cpp
 *
 *  Created on: 11 Oct 2014
 *      Author: Ervin
 */

#include "../headers/DrawHandler.h"
#include "../headers/CustomMesh.h"

DrawHandler::DrawHandler(GLFWwindow* nWindow) {
	// TODO Auto-generated constructor stub
	window = nWindow;
	setPerspectiveMode(PH_FRUSTRUM);
}

DrawHandler::~DrawHandler(){

}

void DrawHandler::draw(){
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);		 // Enables Smooth Shading
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glDepthFunc(GL_LEQUAL);			// The Type Of Depth Test To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculation

	//set up lighting
	setUpLighting();


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//set perspective mode
	setUpPerspective();

	//Draw stuff
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	gluLookAt(cameras[currentCam]->getPosition().x,
			cameras[currentCam]->getPosition().y,
			cameras[currentCam]->getPosition().z,
			cameras[currentCam]->getLookAt().x,
			cameras[currentCam]->getLookAt().y,
			cameras[currentCam]->getLookAt().z,
			cameras[currentCam]->getUp().x,
			cameras[currentCam]->getUp().y,
			cameras[currentCam]->getUp().z
	);

	//Enable Guide
	if (guideEnabled){
		glBegin(GL_QUADS);
		glVertex3f(-1.0f, 0.0f, -1.0f);
		glVertex3f(1.0f, 0.0f, -1.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, 0.0f, 1.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glEnd();
	}

	//Draw all objects
	for (unsigned int i = 0; i < meshLoaders.size(); i++){
		meshLoaders[i]->draw();
	}

	//Draw CustomMeshes
	for (unsigned int i = 0; i < meshLoaders.size(); i++){
		//customMeshes[i]->draw();
	}
	glPopMatrix();
	glfwSwapBuffers(window);
}

void DrawHandler::addCustomMesh(CustomMesh* customMesh)
{
	customMeshes.push_back(customMesh);
}

void DrawHandler::setUpLighting(){
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_NORMALIZE);
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
}


void DrawHandler::setPerspectiveMode (int mode){
	perspectiveMode = mode;
	if (mode == PH_FRUSTRUM){
		for (int i = 0; i < NUM_PERSPECTIVE_VALUES; i++){
			perspectiveValues[i] = frustrum[i];
		}
	}else if (mode == PH_ORTHO){
		for (int i = 0; i < NUM_PERSPECTIVE_VALUES; i++){
			perspectiveValues[i] = ortho[i];
		}
	}
}


void DrawHandler::setPerspectiveValues(float v1, float v2, float v3, float v4, float v5, float v6){
	perspectiveValues[0] = v1;
	perspectiveValues[1] = v2;
	perspectiveValues[2] = v3;
	perspectiveValues[3] = v4;
	perspectiveValues[4] = v5;
	perspectiveValues[5] = v6;
}

void DrawHandler::setUpPerspective(){
	if (perspectiveMode == PH_FRUSTRUM){
		glFrustum(perspectiveValues[0],
				perspectiveValues[1],
				perspectiveValues[2],
				perspectiveValues[3],
				perspectiveValues[4],
				perspectiveValues[5]
		);
	}else if (perspectiveMode == PH_ORTHO){
		glOrtho(perspectiveValues[0],
				perspectiveValues[1],
				perspectiveValues[2],
				perspectiveValues[3],
				perspectiveValues[4],
				perspectiveValues[5]
		);
	}
}


