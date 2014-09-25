/*
 * meshLoader.h
 *
 *  Created on: 25/09/2014
 *      Author: Ervin
 */

#ifndef MESHLOADER_H_
#define MESHLOADER_H_

#include <vector>
#include <cimport.h>
#include <Importer.hpp>
#include <scene.h>
#include <postprocess.h>
#include "mesh.h"

class meshLoader{
	std::vector<mesh*> meshes;
	void recursiveProcess(aiNode* node,const aiScene* scene);
	void processMesh(aiMesh* mesh,const aiScene* scene);
	unsigned int loadTexture(const char* filename);
	public:
		meshLoader(const char* filename);
		~meshLoader();
		void draw(unsigned int programId);
		std::vector<mesh*>& getMeshes();
};



#endif /* MESHLOADER_H_ */
