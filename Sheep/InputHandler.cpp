#include "InputHandler.h"

// key
GLboolean InputHandler::keys[1024];
GLint InputHandler::scancode;
GLint InputHandler::action;
GLint InputHandler::mode;
// mouse
GLint InputHandler::leftClickState;
GLint InputHandler::midClickState;
GLint InputHandler::rightClickState;
GLint InputHandler::leftClickStatePrev;
GLint InputHandler::midClickStatePrev;
GLint InputHandler::rightClickStatePrev;
GLint InputHandler::leftMod;
GLint InputHandler::midMod;
GLint InputHandler::rightMod;
GLfloat InputHandler::mXpos;
GLfloat InputHandler::mYpos;

InputHandler::InputHandler()
{
}

void InputHandler::init()
{
	leftClickState = midClickState = rightClickState = leftClickStatePrev = midClickStatePrev = rightClickStatePrev = GLFW_RELEASE;
	leftMod = midMod = rightMod = 0;
}

void InputHandler::key_callback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
			keys[key] = GL_FALSE;
	}
}

void InputHandler::mouse_callback(GLFWwindow * window, double xpos, double ypos)
{
	mXpos = xpos;
	mYpos = ypos;
}

void InputHandler::mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		leftClickStatePrev = leftClickState;
		leftClickState = action;
		leftMod = mods;
	}
	else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
	{
		midClickStatePrev = midClickState;
		midClickState = action;
		midMod = mods;
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		rightClickStatePrev = rightClickState;
		rightClickState = action;
		rightMod = mods;
	}
}

