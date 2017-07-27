#include "Drawable.h"

Drawable::Drawable()
	: position(0, 0), size(1, 1), color(1.0f), rotation(0.0f), sprite(), bDraw(false)
{}

Drawable::Drawable(glm::vec2 argPosition, glm::vec2 argSize, Texture2D argSprite, glm::vec3 argColor, GLboolean argDraw)
	: position(argPosition), size(argSize), sprite(argSprite), color(argColor), bDraw(argDraw)
{}

void Drawable::draw(SpriteRenderer& renderer)
{
	renderer.DrawSprite(this->sprite, this->position, this->size, this->rotation, this->color);
}