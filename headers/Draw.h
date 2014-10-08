#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

#include "SuperHeader.h"
#include "meshLoader.h"
#include "camera.h"

/**
 *Draws the meshes
 *@param hDC HDC
 *@param scene a collection of meshes
 *@param textureIdMap information about the textures
 *@param camera camera object
 */
void drawHandle(HDC hDC, const std::vector<meshLoader*>& scenes, std::map<std::string, GLuint*> textureIdMap, Camera* camera);

#endif // DRAW_H_INCLUDED
