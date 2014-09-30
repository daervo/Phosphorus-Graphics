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
	glm::vec3 position;
	glm::vec3 viewDirecton;
	const glm::vec3 UP;
public:
	Camera();
	~Camera();
	glm::mat4 getWorldToViewMatrix() const;
	void mouseUpdate( const glm::vec2& newMousePosition);
};




#endif /* CAMERA_H_ */
