#include "../headers/AssImpHeaders.h"
#include "../headers/SuperHeader.h"
#include "../headers/mesh.h"

/*
 * code samples taken from http://www.lighthouse3d.com/cg-topics/code-samples/importing-3d-models-with-assimp/
 */

mesh::mesh(aiMesh* m, aiMaterial *mtl)
{
	mMesh=m;
	mMat=mtl;

}

mesh::~mesh()
{
}

/* ---------------------------------------------------------------------------- */
void color4_to_float4(aiColor4D *c, float f[4])
{
	f[0] = c->r;
	f[1] = c->g;
	f[2] = c->b;
	f[3] = c->a;
}

/* ---------------------------------------------------------------------------- */
void set_float4(float f[4], float a, float b, float c, float d)
{
	f[0] = a;
	f[1] = b;
	f[2] = c;
	f[3] = d;
}

/* ---------------------------------------------------------------------------- */
void mesh::apply_material(const struct aiMaterial *mtl, std::map<std::string, GLuint*> textureIdMap)
{
	float c[4];

	GLenum fill_mode;
	int ret1, ret2;
	aiColor4D diffuse;
	aiColor4D specular;
	aiColor4D ambient;
	aiColor4D emission;
	float shininess, strength;
	int two_sided;
	int wireframe;
	unsigned int max;

	int texIndex = 0;
	aiString texPath;

	if (!textureIdMap.empty()){
		if(AI_SUCCESS == mtl->GetTexture(aiTextureType_DIFFUSE, texIndex, &texPath))
		{
			//bind texture
			cout << "getting texture in  " << texPath.data << endl;
			unsigned int texId = *textureIdMap[texPath.data];
			glBindTexture(GL_TEXTURE_2D, texId);
		}else{
			cout << "no texture found in " << texPath.data << endl;

		}
	}else{
		cout << "no texture map" << endl;
	}


	set_float4(c, 0.8f, 0.8f, 0.8f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
		color4_to_float4(&diffuse, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, c);

	set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
		color4_to_float4(&specular, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

	set_float4(c, 0.2f, 0.2f, 0.2f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
		color4_to_float4(&ambient, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, c);

	set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission))
		color4_to_float4(&emission, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, c);

	max = 1;
	ret1 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
	if(ret1 == AI_SUCCESS) {
		max = 1;
		ret2 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS_STRENGTH, &strength, &max);
		if(ret2 == AI_SUCCESS)
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess * strength);
		else
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	}
	else {
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
		set_float4(c, 0.0f, 0.0f, 0.0f, 0.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);
	}

	max = 1;
	if(AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_ENABLE_WIREFRAME, &wireframe, &max))
		fill_mode = wireframe ? GL_LINE : GL_FILL;
	else
		fill_mode = GL_FILL;
	glPolygonMode(GL_FRONT_AND_BACK, fill_mode);

	/*max = 1;
	if((AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_TWOSIDED, &two_sided, &max)) && two_sided)
		glDisable(GL_CULL_FACE);
	else
		glEnable(GL_CULL_FACE);*/
}

void mesh::draw(std::map<std::string, GLuint*> textureIdMap)
{
	apply_material(mMat, textureIdMap);
	int t = 0;
	for (t = 0; t < mMesh->mNumFaces; ++t) {
		aiFace* face = &mMesh->mFaces[t];
		GLenum face_mode;
		if(mMesh->mNormals == NULL) {
			glDisable(GL_LIGHTING);
		} else {
			glEnable(GL_LIGHTING);
		}

		switch(face->mNumIndices) {
		case 1: face_mode = GL_POINTS; break;
		case 2: face_mode = GL_LINES; break;
		case 3: face_mode = GL_TRIANGLES; break;
		default: face_mode = GL_POLYGON; break;
		}

		glBegin(face_mode);

		for(int i = 0; i < face->mNumIndices; i++) {
			int index = face->mIndices[i];
			if(mMesh->mColors[0] != NULL)
				glColor4fv((GLfloat*)&mMesh->mColors[0][index]);
			if(mMesh->mNormals != NULL)
				glNormal3fv(&mMesh->mNormals[index].x);
			glVertex3fv(&mMesh->mVertices[index].x);
		}

		glEnd();
	}
}
