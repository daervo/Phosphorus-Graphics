/*
 * sceneLoader.h
 *
 *  Created on: 24/09/2014
 *      Author: Ervin
 */

#ifndef SCENELOADER_H_
#define SCENELOADER_H_

#include <vector>
#include <Importer.hpp>
#include <scene.h>
#include <postprocess.h>

class sceneLoader{
	std::vector<mesh*> meshes;
	void recursiveProcess (aiNode* node, const aiScene* scene);
	void processMesh (aiMesh* mesh, const aiScene* scene);
	unsigned int loadTexture(const char* filename);
public:
	meshLoader (const char* filename);
	~meshLoader();
	void draw (unsigned int programId);
	std::vector<mesh*>& getMesh(int id);
};



#endif /* SCENELOADER_H_ */
