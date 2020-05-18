#pragma once

#include "System.hpp"
#include "Coordinator.hpp"

#include <GLFW\glfw3.h>

class PlayerSystem : public System
{
public:
	void Init() override;
	void Update() override;
private:
	void PlayerMovementCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

