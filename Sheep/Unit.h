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
	glm::vec2 movementVector; 
	GLfloat angle = 0.0;
	glm::vec2 destination;

	// constructors
	Unit(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec4 color, GLboolean argDraw, GLfloat argRotation, GLfloat velocity);

	// movement
	void setDestination(glm::vec2 argDestination);
	void move(GLfloat deltaTime);
	void stop();
	// selection
	void select();
	void deselect();
	// rendering 
	virtual void draw(SpriteRenderer& Renderer);
	void draw(SpriteRenderer & renderer, glm::vec2 argSampleDivider, GLint argSampleIndex);
};

#endif
