/*
 * CustomMesh.cpp
 *
 *  Created on: 12 Oct 2014
 *      Author: Ervin
 */

#include "../headers/CustomMesh.h"

CustomMesh::CustomMesh(
		const glm::vec3* p1, // bottom left
		const glm::vec3* p2, // top left
		const glm::vec3* p3, // top right
		const glm::vec3* p4, // bottom right
		std::string texFileName) {
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->p4 = p4;
	if (texFileName != ""){
		this->texFileName = texFileName;
		textureID = loadImageToTexture(texFileName.c_str());
	}

}

GLuint CustomMesh::loadImageToTexture(char const * const thefilename)
{

	ILuint imageID;
	ilGenImages(1, &imageID);
	ilBindImage(imageID);
	//now you can load an image from a file

	ilLoadImage(thefilename);
	//check that the image does offer data, if not so, clean up

	GLuint textureID;

	/* Convert image to RGBA with unsigned byte data type */
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

	glGenTextures(1, &textureID);

	width = ilGetInteger(IL_IMAGE_WIDTH);
	height = ilGetInteger(IL_IMAGE_HEIGHT);


	return textureID;
}

void CustomMesh::draw()
{
	//do transformations:

	glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(zRot, 0.0f, 0.0f, 1.0f);
		glRotatef(yRot, 0.0f, 1.0f, 0.0f);
		glRotatef(xRot, 1.0f, 0.0f, 0.0f);
		drawShape();
	glPopMatrix();

}

void CustomMesh::drawShape()
{


	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, IL_RGBA, width, height, 0, IL_RGBA, IL_UNSIGNED_BYTE, ilGetData());

	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glm::vec3 normal;

	glBegin(GL_POLYGON);
	// bottom left
	glTexCoord2f(0.0f, 0.0f);
	normal = glm::cross(*p4, *p2);
	glNormal3f(normal.x, normal.y, normal.z);
	glVertex3f(p1->x, p1->y, p1->z);

	// top left
	glTexCoord2f(0.0f, 1.0f);
	normal = glm::cross(*p1, *p3);
	glNormal3f(normal.x, normal.y, normal.z);
	glVertex3f(p2->x, p2->y, p2->z);

	// top right
	glTexCoord2f(1.0f, 1.0f);
	normal = glm::cross(*p2, *p4);
	glNormal3f(normal.x, normal.y, normal.z);
	glVertex3f(p3->x, p3->y, p3->z);

	// bottom right
	glTexCoord2f(1.0f, 0.0f);
	normal = glm::cross(*p3, *p1);
	glNormal3f(normal.x, normal.y, normal.z);
	glVertex3f(p4->x, p4->y, p4->z);
	glEnd();

}

