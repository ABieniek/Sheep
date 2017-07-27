#ifndef UNIT_H
#define UNIT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "Drawable.h"

class Unit : public Drawable
{
public:
	GLfloat velocity;

	Unit();
	Unit(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, GLboolean argDraw, GLuint velocity);

	virtual void draw(SpriteRenderer& Renderer);
};

#endif
