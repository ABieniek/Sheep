#include "Unit.h"
#include <iostream>

Unit::Unit()
	: velocity(5.0f)
{
	Drawable();
}

Unit::Unit(glm::vec2 argPos, glm::vec2 argSize, Texture2D argSprite, glm::vec3 argColor, GLboolean argDraw, GLuint argVelocity)
	: velocity(argVelocity)
{
	position = argPos;
	size = argSize;
	sprite = argSprite;
	color = argColor;
	bDraw = argDraw;
}

void Unit::draw(SpriteRenderer& renderer)
{
	renderer.DrawSprite(this->sprite, this->position, this->size, this->rotation, this->color);
}

void Unit::setDestination(glm::vec2 argDestination)
{
	if (position != argDestination)
	{
		destination = argDestination;
		angle = -atan2(destination.y - position.y, destination.x - position.x);
		cout << angle / 3.14159 << "pi" << endl;
		moving = true;
	}
}

void Unit::move()
{
	if (moving)
	{
		if (position.x < destination.x)
		{
			position.x = std::max(position.x - velocity*cos(angle), destination.x);
		}
		else if (position.x > destination.x)
		{
			position.x = std::min(position.x + velocity*cos(angle), destination.x);
		}
		if (position.y < destination.y)
		{
			position.y = std::max(position.y - velocity*sin(angle), destination.y);
		}
		else if (position.y > destination.y)
		{
			position.y = std::min(position.y + velocity*sin(angle), destination.y);
		}
		if (position == destination)
			moving = false;
	}	
}

void Unit::select()
{
	selected = true;
	color = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Unit::deselect()
{
	selected = false;
	color = glm::vec3(1.0f, 1.0f, 1.0f);
}
