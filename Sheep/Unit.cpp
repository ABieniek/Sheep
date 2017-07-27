#include "Unit.h"

Unit::Unit()
	: velocity(5.0f)
{
	Drawable();
}

Unit::Unit(glm::vec2 argPos, glm::vec2 argSize, Texture2D argSprite, glm::vec3 argColor, GLboolean argDraw, GLuint argVelocity)
	: velocity(argVelocity)
{
	position = argPos;
	size = argSize;
	sprite = argSprite;
	color = argColor;
	bDraw = argDraw;
}

void Unit::draw(SpriteRenderer& renderer)
{
	renderer.DrawSprite(this->sprite, this->position, this->size, this->rotation, this->color);
}