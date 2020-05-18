#include "PlayerSystem.hpp"

extern Coordinator gCoordinator;

void PlayerSystem::Init()
{
	//glfwSetKeyCallback()
}

void PlayerSystem::Update()
{
}

void PlayerSystem::PlayerMovementCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		std::cout << "Player Moved!" << std::endl;
	}
}