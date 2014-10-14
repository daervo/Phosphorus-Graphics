/*
 * camera.cpp
 *
 *  Created on: 30/09/2014
 *      Author: Ervin
 */
#include "../headers/camera.h"
#include <glm/gtx/transform.hpp>


Camera::Camera(){
	up = glm::vec3 (0.0f, 1.0f, 0.0f);
	lookAt = glm::vec3 (0.0f, 0.0f, 0.0f);
	position  = glm::vec3(0.0f, 0.0f, 1.0f);
}

void Camera::turn (float const x, float const y, float const speed){
	glm::vec3 newVec3;
	glm::vec3 right;

	//Translate to the origin
	translateOrigin();

	//calculate right vector

	//Rotate about x
	setLookAt(glm::mat3(glm::rotate(speed * y, getRight()))*lookAt);

	//Rotate about y
	glm::vec3 currentUp = getCurrentUp();
	setLookAt(glm::mat3(glm::rotate(speed * x, currentUp))*lookAt);

	//Translate back to previous position
	translatePosition();
}

void Camera::moveForward(float units){
	glm::vec3 newPosition = position - lookAt;
	newPosition = glm::normalize(newPosition);

	//move both position and lookAt
	setPosition(position.x - (units*newPosition.x),
			position.y - (units*newPosition.y),
			position.z - (units*newPosition.z));
	setLookAt(lookAt.x - (units*newPosition.x),
			lookAt.y - (units*newPosition.y),
			lookAt.z - (units*newPosition.z));

}

void Camera::moveRight(float units){
	//Translate to origin
	translateOrigin();

	//Calculate right vector
	glm::vec3 right = getRight();

	//Normalize right vector
	right = glm::normalize(right);
	glm::mat4 transMat = glm::translate(right*units);

	//Translate back
	translatePosition();

	//move both position and lookAt
	setLookAt(glm::vec3(transMat*glm::vec4(lookAt, 1)));
	setPosition(glm::vec3(transMat*glm::vec4(position, 1)));

}

void Camera::zoom(float units){
	glm::vec3 newPosition = position - lookAt;
	newPosition = glm::normalize(newPosition);
	setPosition(position.x + (units*newPosition.x),
			position.y + (units*newPosition.y),
			position.z + (units*newPosition.z));
}

void Camera::print(){
	cout<<"//////////////////"<<endl;
	cout<<"lookAt ("<<lookAt.x<<" "<<lookAt.y<<" "<<lookAt.z<<" "<<")"<<endl;
	cout<<"up ("<<up.x<<" "<<up.y<<" "<<up.z<<" "<<")"<<endl;
	cout<<"position ("<<position.x<<" "<<position.y<<" "<<position.z<<" "<<")"<<endl;
	cout<<"//////////////////"<<endl;
}

void Camera::print(glm::vec3 vector){
	cout<<"("<<vector.x<<", "<<vector.y<<", "<<vector.z <<")"<<endl;
}

