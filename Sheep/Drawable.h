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
	glm::vec4 color = glm::vec4(1.0f);
	GLfloat rotation;
	GLboolean bDraw;
	Texture2D sprite;
	// relationships
	GLfloat radius() { return size.x / 2; };
	// rendering stuff
	GLint sampleFrame = 0;
	
	Drawable();
	Drawable(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec4 color, GLfloat argRotation, GLboolean argDraw);
	virtual void draw(SpriteRenderer &renderer);
	virtual void draw(SpriteRenderer& renderer, glm::vec2 argSampleDivider, GLint argSampleIndex);
	virtual void drawTopLeft(SpriteRenderer& renderer);
};

#endif