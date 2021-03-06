#include "PlayerSystem.hpp"

extern Coordinator gCoordinator;
extern std::shared_ptr <BoxColliderSystem> boxColliderSystem;

bool PlayerSystem::moveForward = false;
bool PlayerSystem::rotateLeft = false;
bool PlayerSystem::rotateRight = false;
bool PlayerSystem::firing = false;

void PlayerSystem::PlayerInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
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
	if (key == GLFW_KEY_SPACE)
	{
		if (action == GLFW_PRESS)
		{
			firing = true;
		}
		else if (action == GLFW_RELEASE)
		{
			firing = false;
		}
	}
}


void PlayerSystem::Init()
{
	glfwSetKeyCallback(gCoordinator.GetWindow(), PlayerInputCallback);
}

void PlayerSystem::Update(float deltaTime)
{
	for (auto const& entity : mEntities)
	{
		auto& transform = gCoordinator.GetComponent<Transform>(entity);
		auto& player = gCoordinator.GetComponent<Player>(entity);

		float scaledSpeed = player.speed * deltaTime;
		float scaledTurnSpeed = player.turnSpeed * deltaTime;

		if (moveForward)
		{
			transform.Translate(glm::vec3(
				scaledSpeed * cos(transform.GetRotationEulerAngles().z + glm::pi<float>() / 2.0f),
				scaledSpeed * sin(transform.GetRotationEulerAngles().z + glm::pi<float>() / 2.0f),
				0.0f)
			);
		}
		if (rotateLeft == GLFW_PRESS) {
			transform.RotateByRadians(scaledTurnSpeed, glm::vec3(0.0f, 0.0f, 1.0f));
		}
		if (rotateRight) {
			transform.RotateByRadians(-scaledTurnSpeed, glm::vec3(0.0f, 0.0f, 1.0f));
		}


		player.fireTimer += deltaTime;
		if (firing && player.fireTimer>player.firePeriod)
		{
			FireBullet(transform);
			player.fireTimer = 0.0f;
		}
	}
}

void PlayerSystem::FireBullet(Transform& transform)
{
	// TODO: Restrain the fire rate

	//std::cout << "Bullet Fired!" << std::endl;

	// make bullet Entity
	Entity bullet = gCoordinator.CreateEntity();
	
	// Setup Transform
	Transform bulletTransform = Transform();	
	// set position
	bulletTransform.SetPosition(transform.GetPosition());
	bulletTransform.SetRotationEulerAngles(transform.GetRotationEulerAngles());
	bulletTransform.SetScale(transform.GetScale() * 0.3f);
	
	gCoordinator.AddComponent<Transform>(
		bullet,
		bulletTransform
	);

	// Setup Renderable
	Renderable bulletRenderable = Renderable();
	bulletRenderable.VAO = MeshUtils::LoadFromArray(bulletVertexPositions, 54);
	bulletRenderable.windingOrder = GL_CCW;
	bulletRenderable.renderingProgram = ShaderUtils::ShaderMap["Bullet"];
	bulletRenderable.tint = glm::vec3(.6, .6, .6);
	gCoordinator.AddComponent<Renderable>(
		bullet,
		bulletRenderable
	);

	// attach a BoxCollider
	BoxCollider bulletBoxCollider = BoxCollider();
	bulletBoxCollider.boundingBox = glm::vec3(0.3);
	gCoordinator.AddComponent<BoxCollider>(
		bullet,
		bulletBoxCollider
	);

	// Attach a bullet component
	Bullet bulletComponent = Bullet();
	gCoordinator.AddComponent<Bullet>(
		bullet,
		bulletComponent
	);

	boxColliderSystem->Subscribe(bullet, BulletSystem::CollisionCallback);

}