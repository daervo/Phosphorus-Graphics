#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

#include "SuperHeader.h"
#include "Triangle.h"
#include "meshLoader.h"
#include "camera.h"

void drawHandle(HDC hDC, meshLoader* scene, std::map<std::string, GLuint*> textureIdMap, Camera* camera);
void draw();

void drawTriangle(Triangle *triangle);
void drawSquare();
void drawCube();
#endif // DRAW_H_INCLUDED
