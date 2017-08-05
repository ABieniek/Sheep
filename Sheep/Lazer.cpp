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
	if (!exploded)
		timer -= deltaTime;
	else
		duration -= deltaTime;
}

void Lazer::detonate(vector<Unit*> units)
{
}

GLboolean Lazer::inHitbox(Unit * argUnit)
{
	return GLboolean();
}

void Lazer::draw(SpriteRenderer& renderer)
{
	if (bDraw)
	{
		if (!exploded)
			renderer.DrawSprite(this->sprite, this->position, this->size, this->rotation, this->color);
		else
			renderer.DrawSprite(this->detonatedSprite, this->position, this->size, this->rotation, this->color);
	}
}