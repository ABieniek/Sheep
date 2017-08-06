#include "Rocket.h"

Rocket::Rocket(glm::vec2 argPosition, glm::vec2 argSize, Texture2D argSprite, Texture2D argDetonatedSprite, Texture2D argTargetSprite,
	glm::vec4 argColor, GLfloat argRotation, GLboolean argDraw, GLfloat argWidth, GLfloat argHeight, 
	GLfloat argTimer, GLfloat argDuration, glm::vec2 argDestination, GLfloat argVelocity, GLfloat argAngularVelocity)
	: destination(argDestination), velocity(argVelocity), angularVelocity(argAngularVelocity), targetSprite(argTargetSprite)
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

void Rocket::update(GLfloat deltaTime, vector<Unit*>& argUnits)
{
	move(deltaTime);
	if ((position == destination) || (timer <= 0))
		detonate(argUnits);
	if (!detonated)
		timer -= deltaTime;
	else
		duration -= deltaTime;
}

void Rocket::setTarget(Unit* argUnit)
{
	targetUnit = argUnit;
}

void Rocket::resetDestination()
{
	if (targetUnit)
		destination = targetUnit->position;
}

void Rocket::setDestination(glm::vec2 argDestination)
{
	// if the target unit pointer is still valid, update the rocket's destination
	destination = argDestination;
}

void Rocket::move(GLfloat deltaTime)
{
	// if the rocket has detonated, don't move it
	if (detonated) return;

	GLfloat goalAngle = -atan2(destination.x - position.x, destination.y - position.y);
	GLfloat angleChange = angularVelocity * deltaTime;
	// change angle clockwise
	if (goalAngle - angle > angle - goalAngle)
	{
		angle = min(angle - angleChange, goalAngle);
	}
	// changle angle counterclockwise
	else if (goalAngle - angle < angle - goalAngle)
	{
		angle = max(angle + angleChange, goalAngle);
	}

	glm::vec2 velocityVector = glm::vec2(cos(angle), sin(angle)) * velocity * deltaTime;
	if (position.x < destination.x)
	{
		position.x = std::min(position.x + velocityVector.x, destination.x);
	}
	else if (position.x > destination.x)
	{
		position.x = std::max(position.x + velocityVector.x, destination.x);
	}
	if (position.y < destination.y)
	{
		position.y = std::min(position.y - velocityVector.y, destination.y);
	}
	else if (position.y > destination.y)
	{
		position.y = std::max(position.y - velocityVector.y, destination.y);
	}
}

void Rocket::detonate(vector<Unit*>& units)
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

GLboolean Rocket::inHitbox(Unit* argUnit)
{
	return (norm(position - argUnit->position)) < size.x;
}

void Rocket::draw(SpriteRenderer& renderer)
{
	if (bDraw)
	{
		// if not detonated, draw the rocket and draw the lazer on the target
		if (!detonated)
		{
			renderer.DrawSprite(this->sprite, this->position, this->size, this->rotation, this->color);
			renderer.DrawSprite(this->targetSprite, this->destination, this->size, this->rotation, this->color);
		}
		else
			renderer.DrawSprite(this->detonatedSprite, this->position, this->size, this->rotation, this->color);
	}
	
}