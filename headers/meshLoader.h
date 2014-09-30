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
	std::vector<mesh*> meshes;
	void recursiveProcess(const aiScene* sc, aiNode* nd,  float scale);
	void apply_material(const struct aiMaterial *mtl);
	unsigned int loadTexture(const char* filename);
	void color4_to_float4(aiColor4D *c, float f[4]);
	void set_float4(float f[4], float a, float b, float c, float d);
	void Color4f(const aiColor4D *color);
	const aiScene* mScene;
	std::string path;
	std::map<std::string, GLuint*> textureIdMap;
	public:
		meshLoader(std::string filename);
		~meshLoader();
		void draw(std::map<std::string, GLuint*> textureIdMap);
		std::vector<mesh*>& getMeshes();
		const aiScene* getScene();

		std::string getPath(){
			return path;
		}
		void setTextureIdMap(std::map<std::string, GLuint*> textureIdMap){
			this->textureIdMap = textureIdMap;
			if (textureIdMap.empty()){
				cout<<"texturemap is empty"<<endl;
			}
		}
};



#endif /* MESHLOADER_H_ */
