#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"

class Drawable
{
public:
	glm::vec2 position, size;
	glm::vec3 color;
	GLfloat rotation;
	GLboolean bDraw;

	Texture2D sprite;

	Drawable();
	Drawable(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, GLboolean argDraw);
	virtual void draw(SpriteRenderer &renderer);
};

#endif