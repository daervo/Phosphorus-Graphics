#include "../headers/SuperHeader.h"
#include "../headers/Triangle.h"

void drawTriangle(Triangle *triangle){
	glColor3f(triangle->getRed(), triangle->getGreen(), triangle->getBlue());
}
