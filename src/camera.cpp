/*
 * camera.cpp
 *
 *  Created on: 30/09/2014
 *      Author: Ervin
 */
#include "../headers/camera.h"
#include <glm/gtx/transform.hpp>

Camera::Camera()
{
}

glm::mat4 Camera::getWorldToViewMatrix() const
{
	return glm::lookAt(position, position + viewDirecton, UP);
}
