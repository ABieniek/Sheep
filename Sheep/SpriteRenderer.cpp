/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer()
{

}

SpriteRenderer::SpriteRenderer(Shader &shader)
{
	this->shader = shader;
	this->initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
	glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRenderer::DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec4 color)
{
	DrawSprite(texture, position, size, rotate, color, glm::vec2(1.0f, 1.0f), 0, false, false);
}

void SpriteRenderer::DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec4 color,
	glm::vec2 argSampleDimensions, GLint argSampleIndex, GLboolean flipXAxis, GLboolean flipYAxis)
{
	// Prepare transformations
	this->shader.Use();
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position, 0.0f));  // First translate (transformations are: scale happens first, then rotation and finally translation happens; reversed order)

															   // model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Move origin of rotation to center of quad
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
																	 // model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back

	model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale

	this->shader.SetMatrix4("model", model);

	// Render textured quad
	this->shader.SetVector4f("spriteColor", color);

	// do math for the desired sample
	glm::vec2 sampleDivider = argSampleDimensions; // dimensions by which we divide the picture
	this->shader.SetVector2f("sampleDivider", sampleDivider); 
	// I'm gonna pretend that I've turned the image into an array, and this portion will use
	// math similar to pointer arithmetic to get the sample offset
	glm::vec2 sampleOffset = glm::vec2((argSampleIndex % (int) sampleDivider.x) * 1.f, 
										(argSampleIndex / (int) sampleDivider.y) * 1.f);
	this->shader.SetVector2f("sampleOffset", sampleOffset);

	// set the boolean values for flipping sample across vertical or horizontal axis
	this->shader.SetBoolean("mirrorXAxis", flipXAxis);
	this->shader.SetBoolean("mirrorYAxis", flipYAxis);


	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void SpriteRenderer::initRenderData()
{
	// Configure VAO/VBO
	GLuint VBO;
	GLfloat vertices[] = {
		// Pos      // Tex
		-.5f, +.5f, 0.0f, 1.0f,
		+.5f, -.5f, 1.0f, 0.0f,
		-.5f, -.5f, 0.0f, 0.0f,

		-.5f, +.5f, 0.0f, 1.0f,
		+.5f, +.5f, 1.0f, 1.0f,
		+.5f, -.5f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}