/*
 * camera.cpp
 *
 *  Created on: 30/09/2014
 *      Author: Ervin
 */
#include "../headers/camera.h"
#include <glm/gtx/transform.hpp>

Camera::Camera(GLfloat x, GLfloat y, GLfloat z, GLfloat xRot, GLfloat yRot, GLfloat zRot)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->xRot = xRot;
	this->yRot = yRot;
	this->zRot = zRot;
}


