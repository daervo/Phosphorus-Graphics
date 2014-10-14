/*
 * meshLoader.h
 *
 *  Created on: 25/09/2014
 *      Author: Ervin
 */

#ifndef MESHLOADER_H_
#define MESHLOADER_H_

#include <vector>
#include "SuperHeader.h"
#include "AssImpHeaders.h"
#include <glm/glm.hpp>

class MeshLoader{
	const aiScene* mScene;
	std::string path;
	std::map<std::string, GLuint*> textureIdMap;
	float x = 0;
	float y = 0;
	float z = 0;
	float xRot = 0;
	float yRot = 0;
	float zRot = 0;
	float scale = 1.0;
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
	 * @param file path to the textures. Defaults to null
	 */
	MeshLoader(std::string const filename, std::string const textureBasePath = "");
	~MeshLoader();
	/**
	 * draws each mesh recursively
	 */
	void draw();
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
	void setScale(float nScale){
		scale = nScale;
	}
	void setRotations(float x_rot, float y_rot, float z_rot){
		xRot = x_rot;
		yRot = y_rot;
		zRot = z_rot;
	}
	void setTranslation(float _x, float _y, float _z){
		x = _x;
		y = _y;
		z = _z;
	}
};



#endif /* MESHLOADER_H_ */
