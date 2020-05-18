#include "PlayerSystem.hpp"

extern Coordinator gCoordinator;

bool PlayerSystem::moveForward = false;

void PlayerSystem::PlayerMovementCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		std::cout << "Player Moved!" << std::endl;
		moveForward = true;
	}
	if (key == GLFW_KEY_W && action == GLFW_RELEASE)
	{
		std::cout << "Player Stopped!" << std::endl;
		moveForward = false;
	}
}

void PlayerSystem::Init()
{
	glfwSetKeyCallback(gCoordinator.GetWindow(), PlayerMovementCallback);
}

void PlayerSystem::Update()
{
	for (auto const& entity : mEntities)
	{
		auto& transform = gCoordinator.GetComponent<Transform>(entity);
		auto& player = gCoordinator.GetComponent<Player>(entity);
		if (moveForward)
		{
			transform.Translate(glm::vec3(0.0f, player.speed * 0.01, 0.0f));
		}
	}
}