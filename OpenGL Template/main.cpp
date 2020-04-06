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

void init(GLFWwindow* window) {}


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

	auto renderSystem = gCoordinator.RegisterSystem<RenderSystem>();
	{
		Signature signature;
		signature.set(gCoordinator.GetComponentType<Renderable>());
		signature.set(gCoordinator.GetComponentType<Transform>());
		gCoordinator.SetSystemSignature<RenderSystem>(signature);
	}

	renderSystem->Init();

	Transform cubeTransform = Transform();
	cubeTransform.position = glm::vec3(0.0f, -2.0f, 0.0f);

	Transform pyramidTransform = Transform();
	pyramidTransform.position = glm::vec3(0.0f, 2.0f, 0.0f);

	Entity cube = gCoordinator.CreateEntity();
	gCoordinator.AddComponent<Transform>(
		cube,
		cubeTransform
		);

	Entity pyramid = gCoordinator.CreateEntity();
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

	gCoordinator.AddComponent<Renderable>(
		pyramid,
		pyramidRenderable
		);

	renderSystem->SetupShader();

	while (!glfwWindowShouldClose(window)) {
		
		// TODO: Add universal update for systems to the system manager
		renderSystem->Update();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}