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
	/**
	 * makes a Mesh object
	 * @param m mesh information
	 * @param mtl material information
	 */
	mesh(aiMesh* m, aiMaterial *mtl);
	~mesh();
	/**
	 * draws the mesh
	 * @param textureIdMap texture map
	 */
	void draw(std::map<std::string, GLuint*> textureIdMap);
};
#endif
