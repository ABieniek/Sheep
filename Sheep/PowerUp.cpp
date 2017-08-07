#include "PowerUp.h"

PowerUp::PowerUp(glm::vec2 argPosition, glm::vec2 argSize, Texture2D argSprite, 
	glm::vec4 argColor, GLboolean argDraw, GLfloat argTimer)
{
	position = argPosition;
	size = argSize;
	sprite = argSprite;
	color = argColor;
	bDraw = argDraw;
}

void PowerUp::update(GLfloat deltaTime)
{
	timer -= deltaTime;
}

GLboolean PowerUp::inHitbox(Unit* argUnit)
{
	return norm(argUnit->position - position) < (radius() + argUnit->radius());
}

void PowerUp::draw(SpriteRenderer & renderer)
{
	if (bDraw)
		renderer.DrawSprite(this->sprite, this->position, this->size, this->rotation, this->color);
}
