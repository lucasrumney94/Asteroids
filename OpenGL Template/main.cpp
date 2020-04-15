// TODO: Organize ECS files into namespaces
#include "Camera.hpp"
#include "Renderable.hpp"
#include "Transform.hpp"

#include "Coordinator.hpp"
#include "MeshUtils.h"

#include "RenderSystem.hpp"

#include "main.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>

using namespace std;

Coordinator gCoordinator;
int width;
int height;
float aspect;
glm::mat4 pMat;

std::shared_ptr<RenderSystem> renderSystem;

void window_size_callback(GLFWwindow* win, int newWidth, int newHeight) {
	aspect = (float)newWidth / (float)newHeight;
	glViewport(0, 0, newWidth, newHeight);
	renderSystem->SetProjection(glm::perspective(1.0472f, aspect, 0.1f, 1000.0f));
}

void init(GLFWwindow* window)
{
	glfwGetFramebufferSize(window, &width, &height);
	glfwSetWindowSizeCallback(window, window_size_callback);
}

int main(void) {
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter 2 - program 1", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		exit(EXIT_FAILURE);
	}
	glfwSwapInterval(1);

	init(window);
	gCoordinator.Init();

	gCoordinator.RegisterComponent<Camera>();
	gCoordinator.RegisterComponent<Transform>();
	gCoordinator.RegisterComponent<Renderable>();

	renderSystem = gCoordinator.RegisterSystem<RenderSystem>();
	{
		Signature signature;
		signature.set(gCoordinator.GetComponentType<Renderable>());
		signature.set(gCoordinator.GetComponentType<Transform>());
		gCoordinator.SetSystemSignature<RenderSystem>(signature);
	}

	renderSystem->Init();

	Transform cubeTransform = Transform();
	cubeTransform.SetPosition(0.0f, -2.0f, 0.0f);

	Transform pyramidTransform = Transform();
	pyramidTransform.SetPosition(0.0f, 2.0f, 0.0f);

	Entity* cube = gCoordinator.CreateEntity("cube");
	gCoordinator.AddComponent<Transform>(
		cube,
		cubeTransform
		);

	Entity* pyramid = gCoordinator.CreateEntity("pyramid");
	gCoordinator.AddComponent<Transform>(
		pyramid,
		pyramidTransform
		);

	// 2x2x2 cube at origin LEN 108
	float cubePositions[] = {
		-1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f, 1.0f,  1.0f, -1.0f, -1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f, 1.0f, -1.0f,  1.0f, 1.0f,  1.0f, -1.0f,
		1.0f, -1.0f,  1.0f, 1.0f,  1.0f,  1.0f, 1.0f,  1.0f, -1.0f,
		1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f, 1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f, -1.0f,  1.0f,  1.0f, 1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f, 1.0f,  1.0f, -1.0f, 1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f, -1.0f
	};

	//Pyramid with 18 vertices comprising 6 triangles (4 tri sides + 2 tri on bottom) LEN 54
	float pyramidPositions[] = {
		-1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f,    //front
		1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f,    //right
		1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f,  //back
		-1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f,  //left
		-1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, //LF
		1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f  //RR
	};

	Renderable cubeRenderable = Renderable();
	cubeRenderable.VAO = MeshUtils::LoadFromArray(cubePositions, 108);
	cubeRenderable.windingOrder = GL_CW;

	gCoordinator.AddComponent<Renderable>(
		cube,
		cubeRenderable
		);

	Renderable pyramidRenderable = Renderable();
	pyramidRenderable.VAO = MeshUtils::LoadFromArray(pyramidPositions, 54);
	pyramidRenderable.windingOrder = GL_CCW;

	gCoordinator.AddComponent<Renderable>(
		pyramid,
		pyramidRenderable
		);

	renderSystem->SetupShader();

	Transform* camTrans = &gCoordinator.GetComponent<Transform>(renderSystem->mCamera);
	camTrans->Translate(glm::vec3(0, 0, 15));

	int frame = 0;

	while (!glfwWindowShouldClose(window)) {
		
		// TODO: Add universal update for systems to the system manager
		renderSystem->Update();
		glfwSwapBuffers(window);
		glfwPollEvents();

		// RAVE
		if (frame % 20 <= 10)
		{
			gCoordinator.EnableEntity(cube);
			gCoordinator.DisableEntity(pyramid);
		}
		else
		{
			gCoordinator.EnableEntity(pyramid);
			gCoordinator.DisableEntity(cube);
		}
		frame++;

		float sinTime = sin(glfwGetTime());
		float cosTime = cos(glfwGetTime());
		Transform* CubeTrans = &gCoordinator.GetComponent<Transform>(cube);
		CubeTrans->Translate(glm::vec3(cosTime * 0.02f, sinTime * 0.02f, 0.0f));
		//CubeTrans->SetRotationEulerAngles(glm::vec3(0.0f, glm::pi<float>() / 4.0f, 0.0f));
		CubeTrans->RotateByDegrees(2.0f, glm::vec3(sinTime, cosTime, 0.0f));

		if (glfwGetKey(window, GLFW_KEY_W)) {
			camTrans->Translate(glm::vec3(0, 0, -0.1f));
		}
		if (glfwGetKey(window, GLFW_KEY_A)) {
			camTrans->Translate(glm::vec3(-0.1f, 0, 0));
		}
		if (glfwGetKey(window, GLFW_KEY_S)) {
			camTrans->Translate(glm::vec3(0, 0, 0.1f));
		}
		if (glfwGetKey(window, GLFW_KEY_D)) {
			camTrans->Translate(glm::vec3(0.1f, 0, 0));
		}
		if (glfwGetKey(window, GLFW_KEY_Z)) {
			camTrans->Translate(glm::vec3(0, 0.1f, 0));
		}
		if (glfwGetKey(window, GLFW_KEY_X)) {
			camTrans->Translate(glm::vec3(0, -0.1f, 0));
		}
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}