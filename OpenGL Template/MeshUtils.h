#pragma once

#include <GL\glew.h>

class MeshUtils
{
public:
	static GLuint LoadFromFile(char* filename);
	static GLuint LoadFromArray(float* vertices, int size);
};

