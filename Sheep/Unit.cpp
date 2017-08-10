#include "Unit.h"
#include <iostream>

Unit::Unit(glm::vec2 argPos, glm::vec2 argSize, Texture2D argSprite, glm::vec4 argColor, GLboolean argDraw, GLfloat argRotation, GLfloat argVelocity)
	: velocity(argVelocity)
{
	position = argPos;
	size = argSize;
	sprite = argSprite;
	color = argColor;
	rotation = argRotation;
	bDraw = argDraw;
}

// movement
void Unit::setDestination(glm::vec2 argDestination)
{
	// argDestination -= glm::vec2(radius(), radius());
	if (position != argDestination)
	{
		destination = argDestination;
		angle = -atan2(destination.y - position.y, destination.x - position.x);
		movementVector = glm::vec2(cos(angle),sin(angle));
		moving = true;
	}
}

void Unit::move(GLfloat deltaTime)
{
	glm::vec2 velocityVector = movementVector * velocity * deltaTime;
	if (moving)
	{
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
		if ((position.x < destination.x && velocityVector.x < 0)
			|| (position.x > destination.x && velocityVector.x > 0)
			|| (position.y < destination.y && velocityVector.y > 0)
			|| (position.y > destination.y && velocityVector.y < 0))
			moving = false;
	}	
}
void Unit::stop()
{
	moving = false;
}

// selection
void Unit::select()
{
	selected = true;
	color = glm::vec4(0.7f, 0.7f, 1.0f, 1.0f);
}
void Unit::deselect()
{
	selected = false;
	color = glm::vec4(1.0f);
}

// rendering
void Unit::draw(SpriteRenderer& renderer)
{
	if (bDraw)
		renderer.DrawSprite(this->sprite, this->position, this->size, this->rotation, this->color);
}

void Unit::draw(SpriteRenderer & renderer, glm::vec2 argSampleDivider, GLint argSampleIndex)
{
	if (bDraw)
		renderer.DrawSprite(this->sprite, this->position, this->size, this->rotation, this->color, 
			argSampleDivider, argSampleIndex, (abs(angle) > M_PI /2), false);
}
