/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture2D.h"
#include "shader.h"

#include <iostream>
using namespace std;


class SpriteRenderer
{
public:
	// Constructor (inits shaders/shapes)
	SpriteRenderer();
	SpriteRenderer(Shader &shaderglm);
	// Destructor
	~SpriteRenderer();
	// Renders a defined quad textured with given sprite
	void DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec4 color = glm::vec4(1.0f));
	void DrawSprite(Texture2D & texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec4 color,
		glm::vec2 argSampleDimensions, GLint argSampleIndex, GLboolean flipXAxis, GLboolean flipYAxis);
	// Render state
	Shader shader;
	GLuint quadVAO;
	// Initializes and configures the quad's buffer and vertex attributes
	void initRenderData();
};

#endif
