#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"

class Drawable
{
public:
	// variables
	glm::vec2 position, size;
	glm::vec4 color;
	GLfloat rotation;
	GLboolean bDraw;
	Texture2D sprite;
	// relationships
	GLfloat radius() { return size.x / 2; };
	glm::vec2 center() { return position + (size / glm::vec2(2.0)); }
	
	Drawable();
	Drawable(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec4 color, GLfloat argRotation, GLboolean argDraw);
	virtual void draw(SpriteRenderer &renderer);
};

#endif