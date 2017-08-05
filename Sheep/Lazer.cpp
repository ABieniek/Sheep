#include "Lazer.h"

Lazer::Lazer(glm::vec2 argPosition, glm::vec2 argSize, Texture2D argSprite, Texture2D argDetonatedSprite, glm::vec4 argColor, GLfloat argRotation, GLboolean argDraw, GLfloat argWidth, GLfloat argHeight, GLfloat argTimer, GLfloat argDuration, glm::vec2 argChunkSize)
	: chunkSize(argChunkSize)
{
	worldWidth = argWidth;
	worldHeight = argHeight;
	timer = argTimer;
	duration = argDuration;
	position = argPosition;
	size = argSize;
	sprite = argSprite;
	detonatedSprite = argDetonatedSprite;
	color = argColor;
	rotation = argRotation;
	bDraw = argDraw;
}

void Lazer::decreaseTime(GLfloat deltaTime)
{
	if (!detonated)
		timer -= deltaTime;
	else
		duration -= deltaTime;
}

void Lazer::detonate(vector<Unit*>& units)
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

GLboolean Lazer::inHitbox(Unit * argUnit)
{
	// distance from Q to PS
	// = ||PS x PQ|| / ||PQ||
	glm::vec2 PS = argUnit->position - position;
	glm::vec2 PQ = glm::vec2(cos(rotation), sin(rotation));
	glm::vec3 cross = glm::cross(glm::vec3(PS, 0), glm::vec3(PQ, 0));
	GLfloat distance = norm(cross) / norm(PQ);
	return argUnit->radius() >= distance;

}

void Lazer::draw(SpriteRenderer& renderer)
{
	if (bDraw)
	{
		if (!detonated)
			renderer.DrawSprite(this->sprite, this->position, this->size, this->rotation, this->color);
		else
			renderer.DrawSprite(this->detonatedSprite, this->position, this->size, this->rotation, this->color);
	}
}