#include "Rocket.h"

Rocket::Rocket(glm::vec2 argPosition, glm::vec2 argSize, Texture2D argSprite, Texture2D argDetonatedSprite, Texture2D argTargetSprite,
	glm::vec4 argColor, GLfloat argRotation, GLboolean argDraw,
	GLfloat argWidth, GLfloat argHeight, GLfloat argTimer, GLfloat argDuration, glm::vec2 argDestination, GLfloat argMomentum)
	: destination(argDestination), momentum(argMomentum), targetSprite(argTargetSprite)
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

void Rocket::update(GLfloat deltaTime)
{
	if (!detonated)
		timer -= deltaTime;
	else
		duration -= deltaTime;
}

void Rocket::setTarget(Unit* argUnit)
{
	if (argUnit)
		setDestination(argUnit->position);
}

void Rocket::setDestination(glm::vec2 argDestination)
{
	
}

void Rocket::move(GLfloat deltaTime)
{

}

void Rocket::detonate(vector<Unit*>& units)
{

}

GLboolean Rocket::inHitbox(Unit* argUnit)
{
	return false;
}