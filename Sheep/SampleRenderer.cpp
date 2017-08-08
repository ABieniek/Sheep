#include "SampleRenderer.h"

SampleRenderer::SampleRenderer(Shader& argShader, GLint argSampleColumns, GLint argSampleRows)
	: sampleRows(argSampleRows), sampleColumns(argSampleColumns)
{
	this->shader = shader;
	this->initRenderData();
}

SampleRenderer::~SampleRenderer()
{

}

void SampleRenderer::DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec4 color,
	GLint textureRow, GLint textureColumn)
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
}

void SampleRenderer::initRenderData()
{
	
}