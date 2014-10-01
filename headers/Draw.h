#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

#include "SuperHeader.h"
#include "Triangle.h"
#include "meshLoader.h"
#include "camera.h"
#include "mat4.h"
#include "vector3d.h"

void drawHandle(HDC hDC, std::vector<meshLoader*> scenes, std::map<std::string, GLuint*> textureIdMap, mat4* viewMatrix, vector3d* position);
void draw();

void drawTriangle(Triangle *triangle);
void drawSquare();
void drawCube();
#endif // DRAW_H_INCLUDED
