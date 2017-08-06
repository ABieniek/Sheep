#ifndef ROCKET_H
#define ROCKET_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "Drawable.h"
#include "Hazard.h"
#include "Unit.h"
#include "CollisionUtil.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <algorithm>

class Rocket : public Hazard
{
public:
	glm::vec2 destination; // the destination that the rocket approaches to explode
	glm::vec2 trajectory;
	GLfloat velocity;
	GLfloat angle = 0;
	GLfloat angularVelocity;
	Unit* targetUnit = NULL;
	Texture2D targetSprite;

	// constructors
	Rocket(glm::vec2 argPosition, glm::vec2 argSize, Texture2D argSprite, Texture2D argDetonatedSprite, Texture2D argTargetSprite,
		glm::vec4 argColor, GLfloat argRotation, GLboolean argDraw, GLfloat argWidth, GLfloat argHeight, 
		GLfloat argTimer, GLfloat argDuration, glm::vec2 argDestination, GLfloat argVelocity, GLfloat argAngularVelocity);

	// behavior and movement
	void update(GLfloat deltaTime, vector<Unit*>& argUnits); // this function will decrease time and handle rocket travel
	void setTarget(Unit* argUnit);
	void setDestination(glm::vec2 argDestination);
	void move(GLfloat deltaTime);
	// explosion
	void detonate(vector<Unit*>& units);
	GLboolean inHitbox(Unit* argUnit);
	// rendering
	void draw(SpriteRenderer& renderer);
};

#endif