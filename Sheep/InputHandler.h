#ifndef MOUSE_HANDLER_H
#define MOUSE_HANDLER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class InputHandler
{
public:
	// key
	static GLboolean keys[1024];
	static GLint scancode;
	static GLint action;
	static GLint mode;
	// mouse
	static GLint leftClickState, midClickState, rightClickState,
		leftClickStatePrev, midClickStatePrev, rightClickStatePrev;
	static GLint leftMod, midMod, rightMod;
	static GLfloat mXpos, mYpos;
	
	// GLFW Input Guide: http://www.glfw.org/docs/latest/input_guide.html

	InputHandler();
	void init();
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

};

#endif