#ifndef MESH_H
#define MESH_H
#include <scene.h>
#include "SuperHeader.h"
#include "AssImpHeaders.h"

class mesh{
	aiMesh* mMesh;
	aiMaterial *mMat;
private:
	void apply_material(const struct aiMaterial *mtl, std::map<std::string, GLuint*> textureIdMap);
public:
	mesh(aiMesh* m, aiMaterial *mtl);
	~mesh();
	void draw(std::map<std::string, GLuint*> textureIdMap);
};
#endif
