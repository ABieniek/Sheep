#ifndef UNIT_H
#define UNIT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "Drawable.h"

#include <math.h>
#include <algorithm>

using namespace std;

class Unit : public Drawable
{
public:
	// variables
	GLfloat velocity;
	GLboolean moving = false;
	GLboolean selected = false;
	GLfloat angle = 0.0;
	glm::vec2 destination;

	// constructors
	Unit();
	Unit(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec4 color, GLboolean argDraw, GLfloat argRotation, GLfloat velocity);

	// rendering 
	virtual void draw(SpriteRenderer& Renderer);
	// movement
	void setDestination(glm::vec2 argDestination);
	void move();
	void stop();
	// selection
	void select();
	void deselect();
	// collision - will be handled as if the hurtboxes for the units are circular
	GLfloat radius(){ return size.x / 2; };
};

#endif
