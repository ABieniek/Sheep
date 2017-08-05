#ifndef HAZARD_H
#define HAZARD_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "Drawable.h"
#include "Unit.h"

#include <math.h>
#include <vector>
#include <algorithm>



class Hazard : public Drawable
{
public:
	GLfloat timer; // time until the hazard will detonate
	GLfloat duration; // holds duration that the texture will display after blowing up
	GLboolean detonated = false; // holds whether the hazard has blown up or not
	Texture2D detonatedSprite; // the texture to be drawn when the object explodes
	GLfloat worldWidth, worldHeight;

	// constructors
	Hazard();
	Hazard(glm::vec2 argPosition, glm::vec2 argSize, Texture2D argSprite, Texture2D argDetonatedSprite,
		glm::vec4 argColor, GLfloat argRotation, GLboolean argDraw,
		GLfloat argWidth, GLfloat argHeight, GLfloat argTimer, GLfloat argDuration);

	// behavior
	void decreaseTime(GLfloat deltaTime); // will bring hazard closer to explosion or destruction
	// explosion
	void detonate(vector<Unit*>& units);
	virtual GLboolean inHitbox(Unit* argUnit);
	// rendering
	void draw(SpriteRenderer& renderer);
};

#endif