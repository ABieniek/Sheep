#include "Hazard.h"

Hazard::Hazard()
{

}

Hazard::Hazard(GLfloat argTimer, GLfloat argDuration)
{

}

Hazard::~Hazard()
{

}

void Hazard::decreaseTime(GLfloat deltaTime)
{
	if (!exploded)
		timer -= deltaTime;
	else
		duration -= deltaTime;
}

void Hazard::detonate(vector<Unit*> units)
{
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
		if (!exploded)
			renderer.DrawSprite(this->sprite, this->position, this->size, this->rotation, this->color);
		else
			renderer.DrawSprite(this->detonatedSprite, this->position, this->size, this->rotation, this->color);
	}
}