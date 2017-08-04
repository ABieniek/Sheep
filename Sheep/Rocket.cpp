#include "Rocket.h"

Rocket::Rocket(glm::vec2 argPosition, glm::vec2 argSize, Texture2D argSprite, Texture2D argDetonatedSprite,
	glm::vec4 argColor, GLfloat argRotation, GLboolean argDraw,
	GLfloat argWidth, GLfloat argHeight, GLfloat argTimer, GLfloat argDuration, glm::vec2 argDestination, GLfloat argMomentum)
	: destination(argDestination), momentum(argMomentum)
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

void Rocket::decreaseTime(GLfloat deltaTime)
{

}

void Rocket::setDestination(glm::vec2 argDestination)
{

}

void Rocket::detonate(vector<Unit*> units)
{

}

GLboolean Rocket::inHitbox(Unit* argUnit)
{
	return false;
}