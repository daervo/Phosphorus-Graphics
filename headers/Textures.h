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

class Textures{
	std::map<std::string, GLuint*> textureIdMap;	// map image filenames to textureIds
	GLuint*	textureIds;							// pointer to texture Array
	int numTextures;
	ILuint* imageIds = NULL;
public:
	/**
	 * constructs texture data from scene and path
	 * @param scene scene object
	 */
	Textures(const aiScene *scene);
	~Textures();
	/**
	 * populates the textureIdMap from the texture images.
	 * Note: only currently works with single image textures
	 * @param basepath the base path of the texture images
	 * @return true if successful
	 */
	bool bindTextures(const char* const basepath);

	/**
	 * returns the textureIdMap.
	 * Warning: call bindTextures first.
	 * @return textureIdMap
	 */
	std::map<std::string, GLuint*> getTextureIdMap(){
		if (textureIdMap.empty()){
			cout<< "warning: map is empty, texture format may be unsupported"<<endl;
		}
		return textureIdMap;
	}
};


#endif /* TEXTURES_H_ */
