#include "Unit.h"
#include <iostream>

Unit::Unit()
	: velocity(5.0f)
{
	Drawable();
}

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

void Unit::draw(SpriteRenderer& renderer)
{
	if (bDraw)
		renderer.DrawSprite(this->sprite, this->position, this->size, this->rotation, this->color);
}

// selection
void Unit::setDestination(glm::vec2 argDestination)
{
	argDestination -= glm::vec2(radius(), radius());
	if (position != argDestination)
	{
		destination = argDestination;
		angle = -atan2(destination.y - position.y, destination.x - position.x);
		movementVector = glm::vec2(velocity * cos(angle), velocity * sin(angle));
		cout << movementVector.x << ", " << movementVector.y << endl;
		moving = true;
	}
}
void Unit::move()
{
	if (moving)
	{
		if (position.x < destination.x)
		{
			position.x = std::min(position.x + movementVector.x, destination.x);
		}
		else if (position.x > destination.x)
		{
			position.x = std::max(position.x + movementVector.x, destination.x);
		}
		if (position.y < destination.y)
		{
			position.y = std::min(position.y - movementVector.y, destination.y);
		}
		else if (position.y > destination.y)
		{
			position.y = std::max(position.y - movementVector.y, destination.y);
		}
		if ((position.x < destination.x && movementVector.x < 0)
			|| (position.x > destination.x && movementVector.x > 0)
			|| (position.y < destination.y && movementVector.y > 0)
			|| (position.y > destination.y && movementVector.y < 0))
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
