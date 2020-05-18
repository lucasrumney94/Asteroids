#include "PlayerSystem.hpp"

extern Coordinator gCoordinator;

bool PlayerSystem::moveForward = false;
bool PlayerSystem::rotateLeft = false;
bool PlayerSystem::rotateRight = false;

void PlayerSystem::PlayerMovementCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_W) {
		if (action == GLFW_PRESS)
		{
			moveForward = true;
		}
		else if (action == GLFW_RELEASE)
		{
			moveForward = false;
		}
	}
	if (key == GLFW_KEY_A) {
		if (action == GLFW_PRESS)
		{
			rotateLeft = true;
		}
		else if (action == GLFW_RELEASE)
		{
			rotateLeft = false;
		}
	}
	if (key == GLFW_KEY_D) {
		if (action == GLFW_PRESS)
		{
			rotateRight = true;
		}
		else if (action == GLFW_RELEASE)
		{
			rotateRight = false;
		}
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
			transform.Translate(glm::vec3(
				player.speed * cos(transform.GetRotationEulerAngles().z + glm::pi<float>() / 2.0f),
				player.speed * sin(transform.GetRotationEulerAngles().z + glm::pi<float>() / 2.0f),
				0.0f)
			);
		}
		if (rotateLeft == GLFW_PRESS) {
			transform.RotateByRadians(player.turnSpeed, glm::vec3(0.0f, 0.0f, 1.0f));
		}
		if (rotateRight) {
			transform.RotateByRadians(-player.turnSpeed, glm::vec3(0.0f, 0.0f, 1.0f));
		}
	}
}