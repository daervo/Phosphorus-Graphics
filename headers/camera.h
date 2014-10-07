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
	glm::vec3 left;
	glm::vec3 up;
	glm::vec3 forward;
	glm::vec3 position;
public:
	Camera(){
		left = glm::vec3(1.0f, 0.0f, 1.0f);
		up = glm::vec3 (0.0f, 1.0f, 1.0f);
		forward = glm::vec3 (0.0f, 0.0f, 0.0f);
		position  = glm::vec3(0.0f, 0.0f, 1.0f);
	}
	~Camera(){
		left = glm::vec3(1.0f, 0.0f, 1.0f);
		up = glm::vec3 (0.0f, 1.0f, 1.0f);
		forward = glm::vec3 (0.0f, 0.0f, 0.0f);
		position  = glm::vec3(0.0f, 0.0f, 1.0f);

	}

	const glm::vec3& getLeft(){
		return left;
	}

	const glm::vec3& getUp(){
		return up;
	}

	const glm::vec3& getForward() const{
		return forward;
	}
	glm::vec3 getPosition(){
		return position;
	}
	void setLeft(glm::vec3 nLeft){
		left = nLeft;
	}
	void setLeft(GLfloat x, GLfloat y, GLfloat z){
		left.x = x;
		left.y = y;
		left.z = z;
	}
	void setUp(glm::vec3 nUp){
		up = nUp;
	}
	void setUp(GLfloat x, GLfloat y, GLfloat z){
		up.x = x;
		up.y = y;
		up.z = z;
	}
	void setForward(glm::vec3 nForward){
		forward.x = nForward.x;
		forward.y = nForward.y;
		forward.z = nForward.z;
	}
	void setForward(GLfloat x, GLfloat y, GLfloat z){
		forward.x = x;
		forward.y = y;
		forward.z = z;
	}
	void setPosition(GLfloat x, GLfloat y, GLfloat z){
		position.x = x;
		position.y = y;
		position.z = z;
	}
	///////////////////////////////////////////////////////////////////////////////
	// compute transform axis from object position and target point
	///////////////////////////////////////////////////////////////////////////////
	/*void lookAtToAxes(const glm::vec3& target)
	{
	    // compute the forward vector
	    forward = target - position;
	    glm::normalize(&forward);

	    // compute temporal up vector based on the forward vector
	    // watch out when look up/down at 90 degree
	    // for example, forward vector is on the Y axis

	        up = glm::vec3(0, 1, 0);
	    // compute the left vector
	    //left = up.cross(forward);  // cross product
	    left = glm::cross(up, forward);
	    //left.normalize();
	    glm::normalize(&left);

	    // re-calculate the orthonormal up vector
	    //up = forward.cross(left);  // cross product
	    up = glm::cross(forward, left);
	    //up.normalize();
	    glm::normalize(&up);
	}*/
	void anglesToAxes(const glm::vec3 angles)
	{
		const float DEG2RAD = 3.141593f / 180;
		float sx, sy, sz, cx, cy, cz, theta;


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
		cout << "left: (" << cy*cz << " " << (sx*sy*cz + cx*sz) << " " << (-cx*sy*cz + sx*sz) << ")" << endl;
		left.x += (cy*cz);
		left.y += (sx*sy*cz + cx*sz);
		left.z += (-cx*sy*cz + sx*sz);

		// determine up axis
		cout << "up: (" << (-cy*sz) << " " << (-sx*sy*sz + cx*cz) << " " << (cx*sy*sz + sx*cz) << ")" << endl;
		up.x += (-cy*sz);
		up.y += (-sx*sy*sz + cx*cz);
		up.z += (cx*sy*sz + sx*cz);

		// determine forward axis
		cout << "forward: (" << (sy) << " " << (-sx*cy) << " " << (cx*cy) << ")" << endl;
		forward.x += (sy);
		forward.y += (-sx*cy);
		forward.z += (cx*cy);
		glm::normalize(&forward);

	}
	void print(){
		cout<<"//////////////////"<<endl;
		cout<<"forward ("<<forward.x<<" "<<forward.y<<" "<<forward.z<<" "<<")"<<endl;
		cout<<"up ("<<up.x<<" "<<up.y<<" "<<up.z<<" "<<")"<<endl;
		cout<<"left ("<<left.x<<" "<<left.y<<" "<<left.z<<" "<<")"<<endl;
		cout<<"position ("<<position.x<<" "<<position.y<<" "<<position.z<<" "<<")"<<endl;
		cout<<"//////////////////"<<endl;
	}
};




#endif /* CAMERA_H_ */
