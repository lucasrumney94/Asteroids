#pragma once

#include "Utils.h"

#include "System.hpp"
#include "Renderable.hpp"
#include "Camera.hpp"
#include "Renderable.hpp"
#include "Transform.hpp"
#include "Coordinator.hpp"

#include <memory>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtx\quaternion.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <cmath>

class BoxColliderSystem : public System
{
public:

	bool DrawBoundingBox; //maybe for debug purposes.

	void Update() override;
};

