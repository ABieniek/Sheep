#ifndef ROCKET_H
#define ROCKET_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "Drawable.h"
#include "Hazard.h"
#include "Unit.h"

#include <math.h>
#include <vector>
#include <algorithm>

class Rocket : public Hazard
{
public:
	glm::vec2 destination; // the destination that the rocket approaches to explode
	glm::vec2 trajectory;
	GLfloat velocity;
	GLfloat momentum;

	// constructors
	Rocket(glm::vec2 argPosition, glm::vec2 argSize, Texture2D argSprite, Texture2D argDetonatedSprite,
		glm::vec4 argColor, GLfloat argRotation, GLboolean argDraw,
		GLfloat argWidth, GLfloat argHeight, GLfloat argTimer, GLfloat argDuration, glm::vec2 argDestination, GLfloat argMomentum);

	// behavior
	void decreaseTime(GLfloat deltaTime); // this function will decrease time and handle rocket travel
	void setDestination(glm::vec2 argDestination);
	// explosion
	void detonate(vector<Unit*>& units);
	GLboolean inHitbox(Unit* argUnit);
};

#endif