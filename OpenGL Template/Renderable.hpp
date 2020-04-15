#pragma once

#include "Component.hpp"
#include <glm\glm.hpp>
#include <GL\glew.h>

struct Renderable : Component
{
	GLuint VAO = 0;
	GLuint renderingProgram;
	glm::vec3 color;

	// GL options
	GLenum windingOrder = GL_CCW;
};