#include "Drawable.h"
#include <iostream>

Drawable::Drawable()
	: position(0, 0), size(1, 1), color(1.0f), rotation(0.0f), sprite(), bDraw(false)
{}

Drawable::Drawable(glm::vec2 argPosition, glm::vec2 argSize, Texture2D argSprite, glm::vec4 argColor, GLfloat argRotation, GLboolean argDraw)
	: position(argPosition), size(argSize), sprite(argSprite), color(argColor), rotation(argRotation), bDraw(argDraw)
{}

void Drawable::draw(SpriteRenderer& renderer)
{
	if (bDraw)
		renderer.DrawSprite(this->sprite, this->position, this->size, this->rotation, this->color);
}