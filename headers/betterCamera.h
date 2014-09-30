/*
 * betterCamera.h
 *
 *  Created on: 01/10/2014
 *      Author: Ervin
 */

#ifndef BETTERCAMERA_H_
#define BETTERCAMERA_H_
#include "SuperHeader.h"
#include <glm/glm.hpp>

class BetterCamera{
	glm::vec3 position;
	glm::vec3 viewDirection;
	glm::vec3 UP;
public:
	BetterCamera();
	glm::mat4 getWorldToViewMatrix() const;
};

#endif /* BETTERCAMERA_H_ */
