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

void Drawable::draw(SpriteRenderer & renderer, glm::vec2 argSampleDivider, GLint argSampleIndex)
{
	if (bDraw)
		renderer.DrawSprite(this->sprite, this->position, this->size, this->rotation, this->color, 
			argSampleDivider, argSampleIndex, false, false);
}

void Drawable::drawTopLeft(SpriteRenderer & renderer)
{
	bool yNeg = false, xNeg = false;
	if (size.x < 0)
	{
		xNeg = true;
		size.x *= -1.f;
		position.x -= size.x;
	}
	if (size.y < 0)
	{
		yNeg = true;
		size.y *= -1.f;
		position.y -= size.y;
	}

	position.x += size.x / 2;
	position.y += size.y / 2;
	draw(renderer);
	position.x -= size.x / 2;
	position.y -= size.y / 2;

	if (xNeg)
	{
		size.x *= -1.f;
		position.x -= size.x;
	}
	if (yNeg)
	{
		size.y *= -1.f;
		position.y -= size.y;
	}
}