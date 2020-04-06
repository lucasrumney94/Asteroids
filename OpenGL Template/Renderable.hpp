#pragma once

#include <glm\glm.hpp>
#include <GL\glew.h>

struct Renderable
{
	GLuint VAO = 0;
	GLuint renderingProgram;
	glm::vec3 color;

	// GL options
	GLenum windingOrder = GL_CCW;
};