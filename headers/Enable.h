#ifndef ENABLE_H_INCLUDED
#define ENABLE_H_INCLUDED

#include "SuperHeader.h"

/**
 * Initializes drawing window and openGL
 * @param hwnd HWND
 * @param hDC HDC*
 * @param hRC HGLRC*
 */
void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC);

#endif // ENABLE_H_INCLUDED


