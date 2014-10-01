/*
 * mat4.h
 *
 *  Created on: 01/10/2014
 *      Author: Ervin
 */

#ifndef MAT4_H_
#define MAT4_H_
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "vector3d.h"
class mat4{
	float right[4] = {1, 0, 0, 0};
	float up[4] = {0, 1, 0, 0};
	float forward[4] = {0, 0, 1, 0};
	float position[4] = {0, 0, 0, 1};
	float rightTheta = 0;
	float upTheta = 0;
	float matrix[16] = {
			right[0],    right[1],    right[2],    right[3] , // First column
			up[0],       up[1],       up[2],       up[3] , // Second column
			forward[0],  forward[1],  forward[2],  forward[3], // Third column
			position[0], position[1], position[2], position[3]   // Forth column
	};
	glm::vec2 oldPos;
public:
	mat4(){

	}
	~mat4();
	void updateMatrix(){
		matrix[0] = right[0];
		matrix[1] = right[1];
		matrix[2] = right[2];
		matrix[3] = right[3];
		matrix[4] = up[0];
		matrix[5] = up[1];
		matrix[6] = up[2];
		matrix[7] = up[3];
		matrix[8] = forward[0];
		matrix[9] = forward[1];
		matrix[10] = forward[2];
		matrix[11] = forward[3];
		matrix[12] = position[0];
		matrix[13] = position[1];
		matrix[14] = position[2];
		matrix[15] = position[3];
	}
	void setRight(float rx, float ry, float rz){
		vector3d vector(rx, ry, rz);
		vector.normalize();
		right[0] = vector.x;
		right[1] = vector.y;
		right[2] = vector.z;
		right[3] = 0;
		updateMatrix();
	}
	void setUp(float ux, float uy, float uz){
		vector3d vector(ux, uy, uz);
		vector.normalize();
		up[0] = vector.x;
		up[1] = vector.y;
		up[2] = vector.z;
		up[3] = 0;
		updateMatrix();
	}
	void setForward(float fx, float fy, float fz){
		vector3d vector(fx, fy, fz);
		vector.normalize();
		forward[0] = vector.x;
		forward[1] = vector.y;
		forward[2] = vector.z;
		forward[3] = 0;
		updateMatrix();
	}
	void setPosition(float px, float py, float pz){
		vector3d vector(px, py, pz);
		vector.normalize();
		position[0] = vector.x;
		position[1] = vector.y;
		position[2] = vector.z;
		position[3] = 1;
		updateMatrix();
	}
	void addRight(float x, float y, float z){
		vector3d vector(right[0]+x, right[1]+y, right[2]+z);
		vector.normalize();
		right[0] = vector.x;
		right[1] = vector.y;
		right[2] = vector.z;
		right[3] = 0;
		updateMatrix();
	}
	void addForward(float x, float y, float z){
		vector3d vector(forward[0]+x, forward[1]+y, forward[2]+z);
		vector.normalize();
		forward[0] = vector.x;
		forward[1] = vector.y;
		forward[2] = vector.z;
		forward[3] = 0;
		updateMatrix();
	}
	void addUp(float x, float y, float z){
		vector3d vector(up[0]+x, up[1]+y, up[2]+z);
		vector.normalize();
		up[0] = vector.x;
		up[1] = vector.y;
		up[2] = vector.z;
		up[3] = 0;
		updateMatrix();
	}
	void addPosition(float x, float y, float z){
		vector3d vector(position[0]+x, position[1]+y, position[2]+z);
		vector.normalize();
		position[0] = vector.x;
		position[1] = vector.y;
		position[2] = vector.z;
		position[3] = 0;
		updateMatrix();
	}
	float* getFloat(){
		return matrix;
	}
	void mouseUpdate (glm::vec2& newPos){
		glm::vec2 mouseDelta = newPos - oldPos;
		glm::vec3 UPv3(up[0], up[1], up[2]);
		glm::vec3 forwardv3(up[0], up[1], up[2]);
		glm::vec3 newForward = glm::mat3(glm::rotate(mouseDelta.x, UPv3))
				* forwardv3;
		setForward(newForward.x, newForward.y, newForward.z);
		oldPos = newPos;
	}
	void turnRight (float theta){
		//rightTheta += theta;
		glm::vec3 UPv3(up[0], up[1], up[2]);
		glm::vec3 forwardv3(forward[0], forward[1], forward[2]);
		glm::vec3 newForward = glm::mat3(glm::rotate(theta, UPv3))
				* forwardv3;
		setForward(newForward.x, newForward.y, newForward.z);
	}
	void lookUp (float theta){
		//upTheta += theta;
		glm::vec3 rightv3(right[0], right[1], right[2]);
		glm::vec3 forwardv3(forward[0], forward[1], forward[2]);
		glm::vec3 newForward = glm::mat3(glm::rotate(theta, rightv3))
				* forwardv3;
		setForward(newForward.x, newForward.y, newForward.z);
	}
	float getRightTheta(){
		return rightTheta;
	}
	float getUpTheta(){
		return upTheta;
	}
	vector3d getForward(){
		vector3d forwardVec(forward[0], forward[1], forward[2]);
		return forwardVec;
	}
	vector3d getUp(){
		vector3d upVec(up[0], up[1], up[2]);
		return upVec;
	}
	vector3d getRight(){
		vector3d rightVec(right[0], right[1], right[2]);
		return rightVec;
	}
};



#endif /* MAT4_H_ */
