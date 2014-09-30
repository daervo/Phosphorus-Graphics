/*
 * textures.h
 *
 *  Created on: 28/09/2014
 *      Author: Ervin
 */

#ifndef TEXTURES_H_
#define TEXTURES_H_

#include "SuperHeader.h"
#include "AssImpHeaders.h"
#include <IL\il.h>

class textures{
	std::map<std::string, GLuint*> textureIdMap;	// map image filenames to textureIds
	GLuint*	textureIds;							// pointer to texture Array
	int numTextures;
	ILuint* imageIds = NULL;
public:
	textures(const aiScene *scene, std::string path);
	~textures();
	bool bindTextures(char* const basepath);

	std::map<std::string, GLuint*> getTextureIdMap(){
		if (textureIdMap.empty()){
			cout<< "warning: map is empty, texture format may be unsupported"<<endl;
		}
		return textureIdMap;
	}
};


#endif /* TEXTURES_H_ */
