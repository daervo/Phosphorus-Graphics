#include "SuperHeader.h"
#include "Triangle.h"

void drawTriangle(Triangle *triangle){
	glColor3f(triangle->getRed(), triangle->getGreen(), triangle->getBlue());
}
