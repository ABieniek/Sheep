#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Game.h"
#include "ResourceManager.h"
#include "InputHandler.h"

/*#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>*/

using namespace std;

const GLuint SCREEN_WIDTH = 800;
const GLuint SCREEN_HEIGHT = 600;

int main(int argc, char *argv[]) 
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sheep", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();
	if (glGetError())
		exit(glGetError());

	glfwSetKeyCallback(window, InputHandler::key_callback);
	glfwSetCursorPosCallback(window, InputHandler::mouse_callback);

	// OpenGL configuration
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Game::InitVariables(SCREEN_WIDTH, SCREEN_HEIGHT);
	Game::InitGraphics();
	Game::InitMenu();

	// DeltaTime variables
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		InputHandler::update(window);

		if (Game::State == GAME_START)
		{
			// initialization
			Game::UpdateMenu(deltaTime);
			Game::RenderMenu(deltaTime);
		}
		else if (Game::State == GAME_PLAYING)
		{
			// initialization
			if (!Game::gamestateInitialized)
				Game::InitGamestate();
			// Calculate delta time
			GLfloat currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			// Manage user input
			Game::ProcessInput(deltaTime);
			// Update Game state
			Game::UpdateGame(deltaTime);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			Game::RenderGame(deltaTime);
		}
		else if (Game::State == GAME_END)
		{
			Game::UpdateMenu(deltaTime);
			Game::RenderMenu(deltaTime);
		}
		glfwSwapBuffers(window);
	}

	// Delete all resources as loaded using the resource manager
	ResourceManager::Clear();

	glfwTerminate();
	return 0;
}