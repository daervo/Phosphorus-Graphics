#ifndef MESH_H
#define MESH_H
#include <iostream>
#include "GLee.h"
#include "meshData.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <string>
#include <scene.h>

class mesh{
	std::vector<vertexData> data;
	std::vector<textureData> textures;
	std::vector<unsigned int> indices;

	unsigned int VBO;
	unsigned int IND;
	aiMesh* mMesh;
	public:
		mesh(aiMesh* m, std::vector<vertexData>* vd,std::vector<unsigned int>* id,std::vector<textureData>* td=NULL);
		~mesh();
		void draw(unsigned int programId);
};
#endif
