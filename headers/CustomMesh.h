/*
 * CustomMesh.h
 *
 *  Created on: 12 Oct 2014
 *      Author: Ervin
 */

#ifndef CUSTOMMESH_H_
#define CUSTOMMESH_H_

#include "SuperHeader.h"
#include <IL/IL.h>
#include <glm/glm.hpp>

class CustomMesh {
	std::map<std::string, GLuint*> textureIdMap;
	GLuint	textureID;							// pointer to texture Array
	ILuint* imageIds = NULL;
	std::string texFileName;
	int width;
	int height;
	int type; // matches OpenGL
	int format; // matches OpenGL
	const glm::vec3* p1;
	const glm::vec3* p2;
	const glm::vec3* p3;
	const glm::vec3* p4;
	float x = 0;
	float y = 0;
	float z = 0;
	float xRot = 0;
	float yRot = 0;
	float zRot = 0;
	float scale = 1.0;
private:
	int const NUM_TEXTURES = 1;
	void drawShape();
	GLuint loadImageToTexture(char const * const thefilename);
public:
	CustomMesh(
			const glm::vec3* p1, // bottom left
			const glm::vec3* p2, // top left
			const glm::vec3* p3, // top right
			const glm::vec3* p4, // bottom right
			std::string texFileName = "");
	void draw();
};

#endif /* CUSTOMMESH_H_ */
