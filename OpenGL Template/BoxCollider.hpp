#pragma once

#include "Component.hpp"
#include <glm\glm.hpp>
#include <GL\glew.h>

struct BoxCollider : Component {
	glm::vec3 boundingBox;
};