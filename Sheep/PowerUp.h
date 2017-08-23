#ifndef POWER_UP
#define POWER_UP

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "Drawable.h"
#include "Unit.h"
#include "CollisionUtil.h"

#include <math.h>
#include <algorithm>
#include <vector>

class PowerUp : public Drawable
{
public:
	GLfloat timer;

	// constructor
	PowerUp(glm::vec2 argPosition, glm::vec2 argSize, Texture2D argSprite,
		glm::vec4 argColor, GLboolean argDraw, GLfloat argTimer);

	// updating
	void update(GLfloat deltaTime);

	// collision
	GLboolean inHitbox(Unit* argUnit);

	// rendering
	void draw(SpriteRenderer& renderer);
};

#endif