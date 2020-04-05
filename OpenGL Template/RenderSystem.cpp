#include "RenderSystem.hpp"

#include "Utils.h"
#include "Camera.hpp"
#include "Renderable.hpp"
#include "Transform.hpp"
#include "Coordinator.hpp"
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <cmath>

extern Coordinator gCoordinator;

void RenderSystem::Init()
{
	mCamera = gCoordinator.CreateEntity();

	Transform camTransform = Transform();
	camTransform.position = glm::vec3(0.0f, 0.0f, 8.0f);

	gCoordinator.AddComponent(
		mCamera,
		camTransform
		);

	Camera cam = Camera();
	cam.projectionTransform = Camera::MakeProjectionTransform(1.0472f, 0.1f, 1000.0f, 600, 600); // 60 degress vertical FoV

	gCoordinator.AddComponent(
		mCamera,
		cam
		);
}

void RenderSystem::Update()
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 1.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	for (auto const& entity : mEntities)
	{
		auto& transform = gCoordinator.GetComponent<Transform>(entity);
		auto& renderable = gCoordinator.GetComponent<Renderable>(entity);

		Camera camera = gCoordinator.GetComponent<Camera>(mCamera);
		Transform camTransform = gCoordinator.GetComponent<Transform>(mCamera);

		glUseProgram(renderable.renderingProgram);

		mvLoc = glGetUniformLocation(renderable.renderingProgram, "mv_matrix");
		projLoc = glGetUniformLocation(renderable.renderingProgram, "proj_matrix");

		pMat = camera.projectionTransform;

		vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-camTransform.position.x, -camTransform.position.y, -camTransform.position.z));
		mMat = glm::translate(glm::mat4(1.0f), glm::vec3(transform.position.x, transform.position.y, transform.position.z));
		mvMat = vMat * mMat;

		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glBindVertexArray(renderable.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		Utils::checkOpenGLError();
	}
}

void RenderSystem::SetupShader()
{
	for (auto const& entity : mEntities)
	{
		auto& renderable = gCoordinator.GetComponent<Renderable>(entity);
		renderable.renderingProgram = Utils::createShaderProgram("vertShader.glsl", "fragShader.glsl");
	}
}

void RenderSystem::SetupVertices() 
{
	for (auto const& entity : mEntities)
	{
		auto& renderable = gCoordinator.GetComponent<Renderable>(entity);
		if (renderable.VAO == 0)
		{
			glGenVertexArrays(1, &renderable.VAO);
			glBindVertexArray(renderable.VAO);
			GLuint vbo;
			glGenBuffers(1, &vbo);

			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(renderable.vertexPositions), renderable.vertexPositions, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
			glEnableVertexAttribArray(0);
			glBindVertexArray(0);
		}
	}
}