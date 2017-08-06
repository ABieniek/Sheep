#ifndef LAZER_H
#define LAZER_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "Drawable.h"
#include "Hazard.h"
#include "Unit.h"
#include "CollisionUtil.h"

#include <math.h>
#include <vector>
#include <algorithm>

class Lazer : public Hazard
{
public:
	// I'm probably gonna need to get creative with rendering these
	// the lazer will stretch across the screen, so I'm probably gonna need to repeat the texture across the sprite
	glm::vec2 chunkSize;

	// constructors
	Lazer(glm::vec2 argPosition, glm::vec2 argSize, Texture2D argSprite, Texture2D argDetonatedSprite,
		glm::vec4 argColor, GLfloat argRotation, GLboolean argDraw,
		GLfloat argWidth, GLfloat argHeight, GLfloat argTimer, GLfloat argDuration, glm::vec2 argChunkSize);

	// behavior
	void update(GLfloat deltaTime, vector<Unit*>& argUnits); // this function will decrease time and handle rocket travel
	// explosion
	void detonate(vector<Unit*>& units);
	GLboolean inHitbox(Unit* argUnit);
	// rendering
	void draw(SpriteRenderer& renderer);
};

#endif