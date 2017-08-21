#include "Button.h"

Button::Button(glm::vec2 argPosition, glm::vec2 argSize, Texture2D argSprite, glm::vec4 argColor,
	GLfloat argRotation, GLboolean argDraw, void((Game::*argCallback)()))
{
	position = argPosition;
	size = argSize;
	sprite = argSprite;
	color = argColor;
	rotation = argRotation;
	bDraw = argDraw;
	callbackFunction = argCallback;

}

GLboolean Button::cursorOnButton(GLfloat x, GLfloat y)
{
	return ((x > (position.x - size.x / 2.0)) &&  (x < (position.x + size.x / 2.0)) && (y > (position.y - size.y / 2.0)) && (y < (position.y + size.y / 2.0)));
}

void Button::render(SpriteRenderer & renderer, glm::vec2 argSampleDivider, GLint argSampleIndex)
{
	if (bDraw)
		renderer.DrawSprite(this->sprite, this->position, this->size, this->rotation, this->color,
			argSampleDivider, argSampleIndex, false, false);
}
