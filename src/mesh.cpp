#include "mesh.h"
#include <scene.h>

mesh::mesh(aiMesh* m, std::vector<vertexData>* vd,std::vector<unsigned int>* id,std::vector<textureData>* td)
{
	data=*vd;
	indices=*id;
	mMesh=m;
	if(td)
		textures=*td;

	/*glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,data.size()*sizeof(vertexData),
	&data[0],GL_STATIC_DRAW);


	glGenBuffers(1,&IND);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IND);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size()*sizeof(unsigned int),&indices[0],GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);*/

}

mesh::~mesh()
{
	/*glDeleteBuffers(1,&VBO);
	glDeleteBuffers(1,&IND);*/
}

void mesh::draw(unsigned int programId)
{
	/*//attribute vec3 vertex
	int vertex=glGetAttribLocation(programId,"vertex"); //0
	int normal=glGetAttribLocation(programId,"normal"); //1
	int tangent=glGetAttribLocation(programId,"tangent"); //2
	int color=glGetAttribLocation(programId,"color"); //3
	int UV=glGetAttribLocation(programId,"UV"); //4

	//texture0
	//texture1...
	std::string str="texture";
	for(int i=0;i<textures.size();i++)
	{
		glActiveTexture(GL_TEXTURE0+i);
		glBindTexture(GL_TEXTURE_2D,textures[i].id);
		glUniform1i(glGetUniformLocation(programId,(str+(char)(i+'0')).c_str()),i);
	}

	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IND);

	glEnableVertexAttribArray(vertex);
	glVertexAttribPointer(vertex,3,GL_FLOAT,GL_FALSE,sizeof(vertexData),0);

	glEnableVertexAttribArray(normal);
	glVertexAttribPointer(normal,3,GL_FLOAT,GL_FALSE,sizeof(vertexData),(void*)(3*sizeof(float)));

	glEnableVertexAttribArray(tangent);
	glVertexAttribPointer(tangent,3,GL_FLOAT,GL_FALSE,sizeof(vertexData),(void*)(6*sizeof(float)));

	glEnableVertexAttribArray(color);
	glVertexAttribPointer(color,3,GL_FLOAT,GL_FALSE,sizeof(vertexData),(void*)(9*sizeof(float)));

	glEnableVertexAttribArray(UV);
	glVertexAttribPointer(UV,2,GL_FLOAT,GL_FALSE,sizeof(vertexData),(void*)(12*sizeof(float)));

	glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_INT,0);*/
	int t = 0;
	for (t = 0; t < mMesh->mNumFaces; ++t) {
				aiFace* face = &mMesh->mFaces[t];
				GLenum face_mode;

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


	/*glDisableVertexAttribArray(vertex);
	glDisableVertexAttribArray(normal);
	glDisableVertexAttribArray(tangent);
	glDisableVertexAttribArray(color);
	glDisableVertexAttribArray(UV);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);*/
}
