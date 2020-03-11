/*
 * GLCall.h
 * Author: Caleb Geyer
 * Description: Displays OpenGL errors when calling OpenGL functions.
 * Credit: The Cherno
 */
#pragma once
#include <GL/glew.h>
#include <iostream>

#define GLCall(x) GLClearError();\
    x;\
    GLLogCall(#x, __FILE__, __LINE__)

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);
