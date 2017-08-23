#include "Lazer.h"

Lazer::Lazer(glm::vec2 argPosition, glm::vec2 argSize, Texture2D argSprite, Texture2D argDetonatedSprite, glm::vec4 argColor, 
	GLfloat argRotation, GLboolean argDraw, GLfloat argWidth, GLfloat argHeight,
	GLfloat argTimer, GLfloat argDuration, glm::vec2 argChunkSize)
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

void Lazer::update(GLfloat deltaTime, vector<Unit*>& argUnits)
{
	if (timer <= 0)
		detonate(argUnits);
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
		// check if the line will intersect with the x-axis
		// if it doesn't intersect with the X-axis, then it must intersect with the y-axis
		GLboolean bXAxis = abs(atan2(position.y, position.x)) < abs(rotation);
		glm::vec2 farPoint;
		GLfloat hypotenuse;
		if (bXAxis)
		{
			if (rotation != M_PI / 2 && rotation != -M_PI / 2)
			{
				hypotenuse = (worldWidth - position.x) / cos(rotation);
				farPoint = glm::vec2(worldWidth, position.y + hypotenuse * sin(rotation));
			}
			else farPoint = glm::vec2(worldWidth, position.y);
		}
		else
		{
			if (rotation != 0 && rotation != -M_PI && rotation != M_PI)
			{
				hypotenuse = (worldHeight - position.y) / sin(rotation);
				farPoint = glm::vec2(position.x + hypotenuse * cos(rotation), worldHeight);
			}
			else farPoint = glm::vec2(position.x, worldHeight);
		}
		while (farPoint.x > -chunkSize.x && farPoint.y > -chunkSize.y)
		{
			if (!detonated)
				renderer.DrawSprite(this->sprite, farPoint, this->chunkSize, this->rotation, 
					this->color, glm::vec2(4, 1), sampleFrame, false, false);
			else
				renderer.DrawSprite(this->detonatedSprite, farPoint, this->chunkSize, this->rotation, 
					this->color, glm::vec2(4, 1), sampleFrame, false, false);
			farPoint -= glm::vec2(chunkSize.x * cos(rotation), chunkSize.x * sin(rotation));
		}
	}
}