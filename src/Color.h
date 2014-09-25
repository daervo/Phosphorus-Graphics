/*
 * Color.h
 *
 *  Created on: 19/09/2014
 *      Author: Ervin
 */

#ifndef COLOR_H_
#define COLOR_H_

#include "SuperHeader.h"
enum COLORTYPES{
	RED, GREEN, BLUE, YELLOW, CYAN, MAGENTA, WHITE, GREY, BLACK
};
class Color{

public:
	Color (GLfloat red, GLfloat green, GLfloat blue){
		setColor(red, green, blue);
	}

	Color(COLORTYPES cType){
		setColorType (cType);
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
	void setColorType(COLORTYPES type);
	void setColor(GLfloat red, GLfloat green, GLfloat blue){
		this->red = red;
		this->blue = blue;
		this->green = green;

	}
	GLfloat red, green, blue;
};


#endif /* COLOR_H_ */
