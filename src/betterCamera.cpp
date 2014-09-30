/*
 * betterCamera.cpp
 *
 *  Created on: 01/10/2014
 *      Author: Ervin
 */

#include "../headers/betterCamera.h";
#include <glm/gtx/transform.hpp>

BetterCamera::BetterCamera():
viewDirection(0.0f, 0.0f, 0.0f),
UP(0.0f, 1.0f, 0.0f)
{

}

glm::mat4 BetterCamera::getWorldToViewMatrix() const{
	return glm::lookAt(position, position+viewDirection, UP);
}
