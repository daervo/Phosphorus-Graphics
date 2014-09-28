/*
 * Color.cpp
 *
 *  Created on: 19/09/2014
 *      Author: Ervin
 */
#include "../headers/Color.h"

void Color::setColorType(COLORTYPES ctype){
	switch (ctype){
	case RED:
		Color::setColor(1.0f, 0.0f, 0.0f);
		break;
	case GREEN:
		Color::setColor(0.0f, 1.0f, 0.0f);
		break;
	case BLUE:
		Color::setColor(0.0f, 0.0f, 1.0f);
		break;
	case YELLOW:
		Color::setColor(1.0f, 1.0f, 0.0f);
		break;
	case CYAN:
		Color::setColor(0.0f, 1.0f, 1.0f);
		break;
	case MAGENTA:
		Color::setColor(1.0f, 0.0f, 1.0f);
		break;
	case WHITE:
		Color::setColor(1.0f, 1.0f, 1.0f);
		break;
	case BLACK:
		Color::setColor(0.0f, 0.0f, 0.0f);
		break;
	case GREY:
		Color::setColor(0.5f, 0.5f, 0.5f);
		break;
	}
}



