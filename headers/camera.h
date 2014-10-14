/*
 * camera.h
 *
 *  Created on: 30/09/2014
 *      Author: Ervin
 */

#ifndef CAMERA_H_
#define CAMERA_H_
#include "SuperHeader.h"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

class Camera{
	/**
	 * the up position of the world (constant)
	 */
	glm::vec3 up;
	/**
	 * what the camera is looking at
	 */
	glm::vec3 lookAt;
	/**
	 * where the eye position is
	 */
	glm::vec3 position;
private:
	void translateOrigin(){
		setLookAt(lookAt-position);
	}
	void translatePosition(){
		setLookAt(lookAt+position);
	}
	glm::vec3 getCurrentUp(){
		return glm::normalize(glm::cross(getRight(), lookAt));
	}
public:
	/**
	 * constructor initializes to the default values
	 */
	Camera();
	~Camera(){

	}
	/**
	 * gets the up
	 * @return up vector
	 */
	const glm::vec3& getUp(){
		return up;
	}

	/**
	 * gets the lookAt
	 * @return lookAt vector
	 */
	const glm::vec3& getLookAt() const{
		return lookAt;
	}
	/**
	 * gets the position
	 * @return position vector
	 */
	glm::vec3 getPosition(){
		return position;
	}
	/**
	 * sets the lookAt from a set of coordinates
	 * @param x x coordinate
	 * @param y y coordinate
	 * @param z z coordinate
	 */
	void setLookAt(glm::vec3 nlookAt){
		lookAt.x = nlookAt.x;
		lookAt.y = nlookAt.y;
		lookAt.z = nlookAt.z;
	}
	/**
	 * sets the lookAt vector from a set of coordinates
	 * @param x x coordinate
	 * @param y y coordinate
	 * @param z z coordinate
	 */
	void setLookAt(GLfloat x, GLfloat y, GLfloat z){
		lookAt.x = x;
		lookAt.y = y;
		lookAt.z = z;
	}
	/**
	 * sets the position from a set of coordinates
	 * @param x x coordinate
	 * @param y y coordinate
	 * @param z z coordinate
	 */
	void setPosition(GLfloat x, GLfloat y, GLfloat z){
		position.x = x;
		position.y = y;
		position.z = z;
	}
	/**
	 * sets the position from a vector
	 * @param nPos the new position
	 */
	void setPosition(glm::vec3 nPos){
		position.x = nPos.x;
		position.y = nPos.y;
		position.z = nPos.z;
	}
	/**
	 * gets the right vector.
	 * Note: you need to translate to the origin first because up
	 * is always on the origin.
	 * @return right vector
	 */
	glm::vec3 getRight(){
		return glm::cross(lookAt, up);
	}
	/**
	 * turns around an axis
	 * @param x turns around the up axis x units
	 * @param y turns around the right axis y units
	 * @param speed how fast you want it to turn
	 */
	void turn (float const x, float const y, float const speed);
	/**
	 * zooms into what the camera is looking at
	 * @param number of units the camera zooms into
	 */
	void zoom(float units);
	/**
	 * moves the camera forward
	 * @param units number of units the camera will move forward
	 */
	void moveForward(float units);
	/**
	 * move the camera to the right
	 * @param units number of units the camera will move right
	 */
	void moveRight(float units);
	/**
	 * general print function for displaying current vectors
	 */
	void print();
	/**
	 * print function for a vector
	 * @param vector vector to be printed
	 */
	void print(glm::vec3 vector);
};




#endif /* CAMERA_H_ */
