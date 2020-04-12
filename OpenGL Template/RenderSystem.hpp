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

class Event;

class RenderSystem : public System
{
public:
	Entity mCamera;

	void Init();

	void Update();

	void SetupShader();

private:
	GLuint mvLoc, projLoc;

	glm::mat4 pMat, vMat, mMat, mvMat;
};