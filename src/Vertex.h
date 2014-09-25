/*
 * Vertex.h
 *
 *  Created on: 19/09/2014
 *      Author: Ervin
 */

#ifndef VERTEX_H_
#define VERTEX_H_

#include "SuperHeader.h"

class Vertex{
	public:
		Vertex(GLfloat locX, GLfloat locY, GLfloat locZ){
			x = locX;
			y = locY;
			z = locZ;
		}

		GLint getX(){
			return x;
		}

		GLint getY(){
			return y;
		}

		GLint getZ(){
			return z;
		}

	private:
		GLfloat x, y, z;

};



#endif /* VERTEX_H_ */
