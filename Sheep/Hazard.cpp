#include "Hazard.h"

Hazard::Hazard()
{

}

Hazard::Hazard(glm::vec2 argPosition, glm::vec2 argSize, Texture2D argSprite, Texture2D argDetonatedSprite, 
	glm::vec4 argColor, GLfloat argRotation, GLboolean argDraw,
	GLfloat argWidth, GLfloat argHeight, GLfloat argTimer, GLfloat argDuration)
	: worldWidth(argWidth), worldHeight(argHeight), timer(argTimer), duration(argDuration)
{
	position = argPosition;
	size = argSize;
	sprite = argSprite;
	detonatedSprite = argDetonatedSprite;
	color = argColor;
	rotation = argRotation;
	bDraw = argDraw;
}

void Hazard::update(GLfloat deltaTime)
{
	if (!detonated)
		timer -= deltaTime;
	else
		duration -= deltaTime;
}

void Hazard::detonate(vector<Unit*>& units)
{
	detonated = true;
	for (unsigned int i = 0; i < units.size(); i++)
	{
		// if the unit is within the hitbox, delete the memory and delete the pointer in the array
		if (this->inHitbox(units[i]))
		{
			delete units[i];
			units.erase(units.begin() + i);
		}
	}
}

GLboolean Hazard::inHitbox(Unit* argUnit)
{
	return false;
}

void Hazard::draw(SpriteRenderer& renderer)
{
	if (bDraw)
	{
		if (!detonated)
			renderer.DrawSprite(this->sprite, this->position, this->size, this->rotation, this->color);
		else
			renderer.DrawSprite(this->detonatedSprite, this->position, this->size, this->rotation, this->color);
	}
}