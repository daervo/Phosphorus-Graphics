#include "../headers/meshLoader.h"
#include "../headers/Textures.h"
using namespace std;




void MeshLoader::recursiveProcess(const aiScene* sc, aiNode* nd,  float scale)
{
	unsigned int i;
	unsigned int n=0, t;
	glm::vec3 toAdd;
	aiMatrix4x4 m = nd->mTransformation;

	m.Scaling(aiVector3D(scale, scale, scale), m);

	// update transform
	m.Transpose();
	glPushMatrix();
	glMultMatrixf((float*)&m);


	// draw all meshes assigned to this node
	for (; n < nd->mNumMeshes; ++n)
	{
		const struct aiMesh* mesh = sc/*mScene*/->mMeshes[nd->mMeshes[n]];

		apply_material(sc->mMaterials[mesh->mMaterialIndex]);


		if(mesh->mNormals == NULL)
		{
			glDisable(GL_LIGHTING);
		}
		else
		{
			glEnable(GL_LIGHTING);
		}

		if(mesh->mColors[0] != NULL)
		{
			glEnable(GL_COLOR_MATERIAL);
		}
		else
		{
			glDisable(GL_COLOR_MATERIAL);
		}



		for (t = 0; t < mesh->mNumFaces; ++t) {
			const struct aiFace* face = &mesh->mFaces[t];
			GLenum face_mode;

			switch(face->mNumIndices)
			{
				case 1: face_mode = GL_POINTS; break;
				case 2: face_mode = GL_LINES; break;
				case 3: face_mode = GL_TRIANGLES; break;
				default: face_mode = GL_POLYGON; break;
			}

			glBegin(face_mode);

			for(i = 0; i < face->mNumIndices; i++)		// go through all vertices in face
			{
				int vertexIndex = face->mIndices[i];	// get group index for current index
				if(mesh->mColors[0] != NULL)
					Color4f(&mesh->mColors[0][vertexIndex]);
				if(mesh->mNormals != NULL)

					if(mesh->HasTextureCoords(0))		//HasTextureCoords(texture_coordinates_set)
					{
						glTexCoord2f(mesh->mTextureCoords[0][vertexIndex].x, 1 - mesh->mTextureCoords[0][vertexIndex].y); //mTextureCoords[channel][vertex]
					}

					glNormal3fv(&mesh->mNormals[vertexIndex].x);
					glVertex3fv(&mesh->mVertices[vertexIndex].x);
					toAdd = glm::vec3(mesh->mVertices[vertexIndex].x, mesh->mVertices[vertexIndex].y, mesh->mVertices[vertexIndex].z);
					toAdd = glm::rotate(toAdd, xRot, glm::vec3(1, 0, 0));
					toAdd = glm::rotate(toAdd, yRot, glm::vec3(0, 1, 0));
					toAdd = glm::rotate(toAdd, zRot, glm::vec3(0, 0, 1));
					toAdd = glm::vec3(glm::scale(glm::vec3(scale, scale, scale))*glm::vec4(toAdd, 1));
					toAdd = glm::vec3(glm::translate(glm::vec3(x, y, z))*glm::vec4(toAdd, 1));
					vertices.push_back(toAdd);
			}

			glEnd();

		}

	}

	// draw all children
	for (n = 0; n < nd->mNumChildren; ++n)
	{
		recursiveProcess(sc, nd->mChildren[n], scale);
	}

	glPopMatrix();
}

void MeshLoader::apply_material(const struct aiMaterial *mtl)
{
	float c[4];

	GLenum fill_mode;
	int ret1, ret2;
	aiColor4D diffuse;
	aiColor4D specular;
	aiColor4D ambient;
	aiColor4D emission;
	float shininess, strength;
//	int two_sided;
	int wireframe;
	unsigned int max;

	int texIndex = 0;
	aiString texPath;

	if (!textureIdMap.empty()){
		if(AI_SUCCESS == mtl->GetTexture(aiTextureType_DIFFUSE, texIndex, &texPath))
		{
			//bind texture
            unsigned int texId = *textureIdMap[texPath.data];
            glBindTexture(GL_TEXTURE_2D, texId);
		}else{
			//cout << "no texture found in " << texPath.data << endl;

		}
	}else{
		//cout << "no texture map" << endl;
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

MeshLoader::MeshLoader(std::string const filename, std::string const textureBasePath)
{//loads data from the file using assimp
	path = filename;
	//vertices = new std::vector<glm::vec3>;
	const aiScene* scene=aiImportFile(filename.data(),
			aiProcess_GenSmoothNormals |
			aiProcess_Triangulate      |
			aiProcess_CalcTangentSpace |
			aiProcess_FlipUVs          |
			aiProcess_PreTransformVertices);
	if(scene==NULL)
	{
		std::cout << "The file wasn't successfuly opened " << aiGetErrorString() << std::endl;
		return;
	}else{
		std::cout << "The file was successfuly opened " << filename << std::endl;
		mScene = scene;
		if (!textureBasePath.empty()){
			Textures textureLoader(scene);
			textureLoader.bindTextures(textureBasePath.c_str());
			textureIdMap = textureLoader.getTextureIdMap();
		}else{
			cout<<"string is empty"<<endl;
		}
	}
}

const aiScene* MeshLoader::getScene(){
	return mScene;
}

MeshLoader::~MeshLoader()
{
}

void MeshLoader::draw()
{
	vertices.clear();
	glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(zRot, 0.0f, 0.0f, 1.0f);
		glRotatef(yRot, 0.0f, 1.0f, 0.0f);
		glRotatef(xRot, 1.0f, 0.0f, 0.0f);
		recursiveProcess(mScene, mScene->mRootNode, scale);
	glPopMatrix();
}

void MeshLoader::Color4f(const aiColor4D *color)
{
	glColor4f(color->r, color->g, color->b, color->a);
}


/* ---------------------------------------------------------------------------- */
void MeshLoader::color4_to_float4(aiColor4D *c, float f[4])
{
	f[0] = c->r;
	f[1] = c->g;
	f[2] = c->b;
	f[3] = c->a;
}

/* ---------------------------------------------------------------------------- */
void MeshLoader::set_float4(float f[4], float a, float b, float c, float d)
{
	f[0] = a;
	f[1] = b;
	f[2] = c;
	f[3] = d;
}
