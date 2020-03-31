#include "RenderSystem.h"
#include "Components/Camera.cpp"
#include "Components/Renderable.cpp"
#include "Components/Transform.cpp"
#include "Core/Coordinator.cpp"
#include <GL\glew.h>
#include <cmath>

extern Coordinator gCoordinator;


void RenderSystem::Init()
{
	
}


void RenderSystem::Update(float dt)
{
	glClearColor(1.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

