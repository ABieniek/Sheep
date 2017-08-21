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
	if ((norm(position - destination) < 25) || (timer <= 0))
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
	destination = targetUnit->position;
}

void Rocket::setDestination(glm::vec2 argDestination)
{
	destination = argDestination;
}

void Rocket::move(GLfloat deltaTime)
{
	// if the rocket has detonated, don't move it
	if (detonated) return;

	GLfloat goalAngle = -atan2(destination.y - position.y, destination.x - position.x);
	GLfloat angleDifference = AngleDiff(goalAngle, rotation);
	GLfloat angleChange = (angularVelocity + abs(angleDifference)/2.f) * deltaTime;
	// change angle clockwise
	if (angleDifference < 0)
	{
		rotation = rotation + angleChange;
	}
	// changle angle counterclockwise
	else if (angleDifference > 0)
	{
		rotation = rotation - angleChange;
	}

	glm::vec2 velocityVector = glm::vec2(cos(rotation), sin(rotation)) * velocity * deltaTime / (1 + abs(angleDifference));
	position += glm::vec2(velocityVector.x, -velocityVector.y);
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
			renderer.DrawSprite(this->sprite, this->position, this->size, -(this->rotation), this->color);
			renderer.DrawSprite(this->targetSprite, this->destination, this->size, 0, this->color);
		}
		else
			renderer.DrawSprite(this->detonatedSprite, this->position, this->size, 0, this->color);
	}	
}

