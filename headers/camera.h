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
#include <glm/gtx/rotate_vector.hpp>

class Camera{
	glm::vec3 up;
	glm::vec3 lookAt;
	glm::vec3 position;
public:
	Camera(){
		up = glm::vec3 (0.0f, 1.0f, 0.0f);
		lookAt = glm::vec3 (0.0f, 0.0f, 0.0f);
		position  = glm::vec3(0.0f, 0.0f, 1.0f);
	}
	~Camera(){

	}

	const glm::vec3& getUp(){
		return up;
	}

	const glm::vec3& getLookAt() const{
		return lookAt;
	}
	glm::vec3 getPosition(){
		return position;
	}
	void setLookAt(glm::vec3 nlookAt){
		lookAt.x = nlookAt.x;
		lookAt.y = nlookAt.y;
		lookAt.z = nlookAt.z;
	}
	void setLookAt(GLfloat x, GLfloat y, GLfloat z){
		lookAt.x = x;
		lookAt.y = y;
		lookAt.z = z;
	}
	void setPosition(GLfloat x, GLfloat y, GLfloat z){
		position.x = x;
		position.y = y;
		position.z = z;
	}
	void setPosition(glm::vec3 nPos){
		position.x = nPos.x;
		position.y = nPos.y;
		position.z = nPos.z;
	}
	glm::vec3 getRight(){
		//warning: needs to set to the origin before using
		return glm::cross(lookAt, up);
	}
	void turn (float const x, float const y, float const speed){
		glm::vec3 newVec3;
		glm::vec3 right;

		//Translate to the origin
		translateOrigin();

		//calculate right vector

		//Rotate about x
		setLookAt(glm::mat3(glm::rotate(speed * y, getRight()))*lookAt);

		//Rotate about y
		setLookAt(glm::mat3(glm::rotate(speed * x, up))*lookAt);

		//Translate back to previous position
		translatePosition();
	}
	void translateOrigin(){
		setLookAt(lookAt-position);
	}
	void translatePosition(){
		setLookAt(lookAt+position);
	}
	void zoom(float units){
		glm::vec3 newPosition = position - lookAt;
		glm::normalize(&newPosition);
		setPosition(position.x + (units*newPosition.x),
				position.y + (units*newPosition.y),
				position.z + (units*newPosition.z));
	}
	void moveForward(float units){
		glm::vec3 newPosition = position - lookAt;
		glm::normalize(&newPosition);

		//move both position and lookAt
		setPosition(position.x - (units*newPosition.x),
				position.y - (units*newPosition.y),
				position.z - (units*newPosition.z));
		setLookAt(lookAt.x - (units*newPosition.x),
				lookAt.y - (units*newPosition.y),
				lookAt.z - (units*newPosition.z));

	}
	void moveRight(float units){
		//Translate to origin
		translateOrigin();

		//Calculate right vector
		glm::vec3 right = getRight();

		//Normalize right vector
		right = glm::normalize(right);
		glm::mat4 transMat = glm::translate(right*units);

		//Translate back
		translatePosition();
		print(lookAt);

		//move both position and lookAt
		setLookAt(glm::vec3(transMat*glm::vec4(lookAt, 1)));
		setPosition(glm::vec3(transMat*glm::vec4(position, 1)));

	}
	void print(){
		cout<<"//////////////////"<<endl;
		cout<<"lookAt ("<<lookAt.x<<" "<<lookAt.y<<" "<<lookAt.z<<" "<<")"<<endl;
		cout<<"up ("<<up.x<<" "<<up.y<<" "<<up.z<<" "<<")"<<endl;
		cout<<"position ("<<position.x<<" "<<position.y<<" "<<position.z<<" "<<")"<<endl;
		cout<<"//////////////////"<<endl;
	}
	void print(glm::vec3 vector){
		cout<<"("<<vector.x<<", "<<vector.y<<", "<<vector.z <<")"<<endl;
	}
};




#endif /* CAMERA_H_ */
