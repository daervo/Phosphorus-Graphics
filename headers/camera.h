/*
 * camera.h
 *
 *  Created on: 30/09/2014
 *      Author: Ervin
 */

#ifndef CAMERA_H_
#define CAMERA_H_
#include "SuperHeader.h"
#include "vector3d.h"
#include <glm/glm.hpp>

class Camera{
	vector3d* left;
	vector3d* up;
	vector3d* forward;
	vector3d* position;
public:
	Camera(){
		left = new vector3d(1.0f, 0.0f, 0.0f);
		up = new vector3d(0.0f, 1.0f, 0.0f);
		forward = new vector3d(0.0f, 0.0f, 0.0f);
		position = new vector3d(0.0f, 0.0f, 1.0f);
	}
	~Camera();

	vector3d* getLeft(){
		return left;
	}

	vector3d* getUp(){
		return up;
	}

	vector3d* getForward(){
		return forward;
	}
	vector3d* getPosition(){
		return position;
	}
	void setLeft(vector3d* nLeft){
		left = nLeft;
	}
	void setUp(vector3d* nUp){
		up = nUp;
	}
	void setForward(vector3d* nForward){
		forward = nForward;
	}
	void setPosition(GLfloat x, GLfloat y, GLfloat z){
		position->x = x;
		position->y = y;
		position->z = z;
	}
	void anglesToAxes(const vector3d angles)
	{
		const float DEG2RAD = 3.141593f / 180;
		float sx, sy, sz, cx, cy, cz, theta;

		// un-translate
		setToOrigin();

		// rotation angle about X-axis (pitch)
		theta = angles.x * DEG2RAD;
		sx = sinf(theta);
		cx = cosf(theta);

		// rotation angle about Y-axis (yaw)
		theta = angles.y * DEG2RAD;
		sy = sinf(theta);
		cy = cosf(theta);

		// rotation angle about Z-axis (roll)
		theta = angles.z * DEG2RAD;
		sz = sinf(theta);
		cz = cosf(theta);

		// determine left axis
		left->x = cy*cz;
		left->y = sx*sy*cz + cx*sz;
		left->z = -cx*sy*cz + sx*sz;

		// determine up axis
		up->x = -cy*sz;
		up->y = -sx*sy*sz + cx*cz;
		up->z = cx*sy*sz + sx*cz;

		// determine forward axis
		forward->x = sy;
		forward->y = -sx*cy;
		forward->z = cx*cy;

		// re-translate
		setBack();
	}
	void setToOrigin(){
		forward->x -= position->x;
		forward->y -= position->y;
		forward->z -= position->z;
		up->x -= position->x;
		up->y -= position->y;
		up->z -= position->z;
		left->x -= position->x;
		left->y -= position->y;
		left->z -= position->z;
	}
	void setBack(){
		forward->x += position->x;
		forward->y += position->y;
		forward->z += position->z;
		up->x += position->x;
		up->y += position->y;
		up->z += position->z;
		left->x += position->x;
		left->y += position->y;
		left->z += position->z;

	}
};




#endif /* CAMERA_H_ */
