#include "../headers/meshLoader.h"
using namespace std;




void meshLoader::recursiveProcess(aiNode* node,const aiScene* scene)
{
	//process
	for(int i=0;i<node->mNumMeshes;i++)
	{
		aiMesh* mesh=scene->mMeshes[node->mMeshes[i]];
		processMesh(mesh,scene);
	}



	//recursion
	for(int i=0;i<node->mNumChildren;i++)
	{
		recursiveProcess(node->mChildren[i],scene);
	}
}

void meshLoader::processMesh(aiMesh* m,const aiScene* scene)
{
	meshes.push_back(new mesh(m, scene->mMaterials[m->mMaterialIndex]));
}

meshLoader::meshLoader(std::string filename)
{//loads data from the file using assimp
	path = filename;
	const aiScene* scene=aiImportFile(filename.data(), aiProcess_GenSmoothNormals | aiProcess_Triangulate | aiProcess_CalcTangentSpace | aiProcess_FlipUVs);
	if(scene/*aiGetErrorString()*/==NULL)
	{
		std::cout << "The file wasn't successfuly opened " << aiGetErrorString() << std::endl;
		return;
	}else{
		std::cout << "The file was successfuly opened " << filename << std::endl;
		mScene = scene;
	}

	recursiveProcess(scene->mRootNode,scene);
}

const aiScene* meshLoader::getScene(){
	return mScene;
}

meshLoader::~meshLoader()
{
	for(int i=0;i<meshes.size();i++)
		delete meshes[i];
}

void meshLoader::draw(std::map<std::string, GLuint*> textureIdMap)
{
	for(int i=0;i<meshes.size();i++)
		meshes[i]->draw(textureIdMap);
}

std::vector<mesh*>& meshLoader::getMeshes()
{
	return meshes;
}
