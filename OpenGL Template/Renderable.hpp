#pragma once

#include <glm\glm.hpp>
#include <GL\glew.h>

struct Renderable
{
	float vertexPositions[108];
	GLuint VAO = 0;
	GLuint renderingProgram;
	glm::vec3 color;
};