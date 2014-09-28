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

class meshLoader{
	std::vector<mesh*> meshes;
	void recursiveProcess(aiNode* node,const aiScene* scene);
	void processMesh(aiMesh* mesh,const aiScene* scene);
	unsigned int loadTexture(const char* filename);
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
