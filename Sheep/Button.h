#ifndef BUTTON_H
#define BUTTON_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Drawable.h"

enum ButtonState {
	BUTTON_CLEAR = 0,
	BUTTON_HOVERED = 1,
	BUTTON_PRESSED = 2
};

class Button : public Drawable
{
public:
	void(*callbackFunction)();
	GLboolean pressed;
	Button(glm::vec2 argPosition, glm::vec2 argSize, Texture2D argSprite,
		glm::vec4 argColor, GLfloat argRotation, GLboolean argDraw, void(*argCallback)());
	GLboolean cursorOnButton(GLfloat x, GLfloat y);
	void render(SpriteRenderer& renderer, glm::vec2 argSampleDivider, GLint argSampleIndex);
	void Button::process(GLfloat mXpos, GLfloat mYpos, GLint argAction, GLint argActionPrev);
};

#endif