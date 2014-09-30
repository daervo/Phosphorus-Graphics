/*
 * camera.h
 *
 *  Created on: 30/09/2014
 *      Author: Ervin
 */

#ifndef CAMERA_H_
#define CAMERA_H_
#include "SuperHeader.h"
#include <glm/glm.hpp>

class Camera{
	GLfloat x, y, z;
	GLfloat xRot, yRot, zRot;
public:
	Camera(GLfloat x, GLfloat y, GLfloat z, GLfloat xRot, GLfloat yRot, GLfloat zRot);
	~Camera();

	GLfloat getX(){
		return x;
	}
	GLfloat getY(){
		return y;
	}
	GLfloat getZ(){
		return z;
	}
	GLfloat getXRot(){
		return xRot;
	}
	GLfloat getYRot(){
		return yRot;
	}
	GLfloat getZRot(){
		return zRot;
	}
	void addX(GLfloat dist){
		x+=dist;
	}
	void addY(GLfloat dist){
		y+=dist;
	}
	void addZ(GLfloat dist){
		z+=dist;
	}
	void addxRot(GLfloat theta){
		xRot+=theta;
	}
	void addyRot(GLfloat theta){
		yRot+=theta;
	}
	void addzRot(GLfloat theta){
		zRot+=theta;
	}
};




#endif /* CAMERA_H_ */
