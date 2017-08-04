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
	GLboolean exploded; // holds whether the hazard has blown up or not, used for rendering purposes
	Texture2D detonatedSprite; // the texture to be drawn when the object explodes

	// constructors and destructors
	Hazard();
	Hazard(GLfloat timer, GLfloat duration);
	~Hazard();

	// timer - handles duration that hazard exists
	void decreaseTime(GLfloat deltaTime); // will bring hazard closer to explosion or destruction
	// explosion - kills units
	void detonate(vector<Unit*> units);
	virtual GLboolean inHitbox(Unit* argUnit);
	// rendering
	void draw(SpriteRenderer& renderer);
};

#endif