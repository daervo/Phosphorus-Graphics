/*
 * Triangle.h
 *
 *  Created on: 19/09/2014
 *      Author: Ervin
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "SuperHeader.h"
#include "Color.h"
#include "Vertex.h"

class Triangle{
public:
	Triangle(Vertex *vert1, Vertex *vert2, Vertex *vert3, Color color){
		this->vert1 = vert1;
		this->vert2 = vert2;
		this->vert3 = vert3;

		this->red = color.getRed();
		this->blue = color.getBlue();
		this->green = color.getGreen();
	}

	GLfloat getRed(){
		return red;
	}

	GLfloat getGreen(){
		return green;
	}

	GLfloat getBlue(){
		return blue;
	}
private:
	GLfloat red, green, blue;

	Vertex *vert1, *vert2, *vert3;

};



#endif /* TRIANGLE_H_ */
