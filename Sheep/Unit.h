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
	GLfloat velocity;
	GLboolean moving = false;
	GLboolean selected = false;
	GLfloat angle = 0.0;
	glm::vec2 destination;

	Unit();
	Unit(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, GLboolean argDraw, GLfloat velocity);

	virtual void draw(SpriteRenderer& Renderer);
	void setDestination(glm::vec2 argDestination);
	void move();
	void select();
	void deselect();
};

#endif