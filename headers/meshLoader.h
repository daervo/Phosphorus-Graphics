/*
 * meshLoader.h
 *
 *  Created on: 25/09/2014
 *      Author: Ervin
 */

#ifndef MESHLOADER_H_
#define MESHLOADER_H_

#include <vector>
#include "../headers/mesh.h"
#include "SuperHeader.h"
#include <glm/glm.hpp>

class meshLoader{
	const aiScene* mScene;
	std::string path;
	std::map<std::string, GLuint*> textureIdMap;
	std::vector<mesh*> meshes;
private:
	void recursiveProcess(const aiScene* sc, aiNode* nd,  float scale);
	void apply_material(const struct aiMaterial *mtl);
	unsigned int loadTexture(const char* filename);
	void color4_to_float4(aiColor4D *c, float f[4]);
	void set_float4(float f[4], float a, float b, float c, float d);
	void Color4f(const aiColor4D *color);
public:
	/**
	 * loads the scene from a file
	 * @param filename path to the file
	 */
	meshLoader(std::string filename);
	~meshLoader();
	/**
	 * draws each mesh recursively
	 * @param textureIdMap texture map
	 */
	void draw(std::map<std::string, GLuint*> textureIdMap);
	/**
	 * returns the meshes
	 * @return vector of meshes
	 */
	std::vector<mesh*>& getMeshes();
	/**
	 * returns while scene
	 * @return scene
	 */
	const aiScene* getScene();
	/**
	 * returns path of the scene
	 * @return path
	 */
	std::string getPath(){
		return path;
	}
};



#endif /* MESHLOADER_H_ */
