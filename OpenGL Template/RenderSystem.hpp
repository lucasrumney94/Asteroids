#pragma once

#include "System.hpp"
#include "Renderable.hpp"
#include "glm/glm.hpp"
#include <memory>

class Event;

class RenderSystem : public System
{
public:
	void Init();

	void Update();

	void SetupShader();

private:
	Entity mCamera;

	GLuint mvLoc, projLoc;

	glm::mat4 pMat, vMat, mMat, mvMat;
};