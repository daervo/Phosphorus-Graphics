/*
 * Textures.cpp
 *
 *  Created on: 28/09/2014
 *      Author: Ervin
 */
#include "../headers/Textures.h"
#include "../headers/SuperHeader.h"


textures::textures(const aiScene *scene){



	/* Before calling ilInit() version should be checked. */
	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
	{
		//ILint test = ilGetInteger(IL_VERSION_NUM);
		/// wrong DevIL version ///
		std::string err_msg = "Wrong DevIL version. Old devil.dll in system32/SysWow64?";
		char* cErr_msg = (char *) err_msg.c_str();
		cout << cErr_msg << endl;
		return ;
	}

	ilInit(); /* Initialization of DevIL */

	if (scene->HasTextures()) cout<< "Support for meshes with embedded textures is not implemented" << endl;

	/* getTexture Filenames and Numb of Textures */
	for (unsigned int m=0; m<scene->mNumMaterials; m++)
	{
		int texIndex = 0;
		aiReturn texFound = AI_SUCCESS;
		bool exit = FALSE;

		aiString path;	// filename

		while (!exit)
		{
			cout << "m: " << m <<" "<<  texIndex <<": checking" << endl;
			texFound = scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
			if (texFound == AI_SUCCESS){
				textureIdMap[path.data] = NULL; //fill map with textures, pointers still NULL yet
				cout << "path data is  "<<  path.C_Str() << " adding " << endl;
			}else{
				cout<<"not found"<<endl;
				exit = TRUE;
			}
			texIndex++;
		}
	}

	numTextures = textureIdMap.size() ;
	cout << "there are  " << numTextures  << " textures." << endl;

	/* array with DevIL image IDs */
	imageIds = new ILuint[numTextures];

	/* generate DevIL Image IDs */
	ilGenImages(numTextures, imageIds); /* Generation of numTextures image names */

	/* create and fill array with GL texture ids */
	textureIds = new GLuint[numTextures];
	glGenTextures(numTextures, textureIds); /* Texture name generation */

	/* define texture path */
	//std::string texturepath = "../../../test/models/Obj/";




}


textures::~textures(){
	ilDeleteImages(numTextures, imageIds); /* Because we have already copied image data into texture data
			we can release memory used by image. */

	//Cleanup
	delete [] imageIds;
	imageIds = NULL;
}

bool textures::bindTextures(char* const basepath)
{

	ILboolean success = TRUE;
	/* get iterator */
	std::map<std::string, GLuint*>::iterator itr = textureIdMap.begin();

	for (int i=0; i<numTextures; i++)
	{
		cout<<"i is now "<<i<<endl;

		//save IL image ID
		cout<<"setting map"<<endl;
		std::string filename = (*itr).first;  // get filename
		(*itr).second =  &textureIds[i];	  // save texture id for filename in map
		cout<<"successfully set map"<<endl;
		itr++;
		cout<<"incremented itr"<<endl;



		ilBindImage(imageIds[i]); /* Binding of DevIL image name */
		cout<< "finished binding "<<imageIds[i]<< endl;
		std::string fileloc (basepath + filename);	/* Loading of image */
		cout<< "base is "<<basepath<< endl;
		cout<< "fileName is "<<filename<< endl;
		success = ilLoadImage(fileloc.c_str());
		cout<< "looking at "<<fileloc<< endl;
		cout<<"with id "<<textureIds[i]<<endl;
		if (success) /* If no error occured: */
		{
			success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE); /* Convert every colour component into
					unsigned byte. If your image contains alpha channel you can replace IL_RGB with IL_RGBA */
			if (!success)
			{
				/* Error occured */
				cout<< "Couldn't convert image" <<endl;
				return FALSE;
			}
			glGenTextures(numTextures, &textureIds[i]); /* Texture name generation */
			glBindTexture(GL_TEXTURE_2D, textureIds[i]); /* Binding of texture name */
			//redefine standard texture values
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /* We will use linear
					interpolation for magnification filter */
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /* We will use linear
					interpolation for minifying filter */
			glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH),
					ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE,
					ilGetData()); /* Texture specification */
			cout<<"binded image"<<endl;
		}else{
			/* Error occured */
			MessageBox(NULL, ("Couldn't load Image: " + fileloc).c_str() , "ERROR", MB_OK | MB_ICONEXCLAMATION);
		}

	}
	cout<<"finished"<<endl;
	return success;
}
