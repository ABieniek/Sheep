#ifndef SAMPLE_RENDERER_H
#define SAMPLE_RENDERER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture2D.h"
#include "shader.h"
#include "SpriteRenderer.h"

// extension of SpriteRenderer to allow for sampling and such
// it'll probably behave fairly differently, so I'm not sure if I need to implement inheritence
// I'm also probably gonna be messing around a lot to see what works
class SampleRenderer :  public SpriteRenderer
{
	//Constructor (initializes shaders/sample vertices)
	SampleRenderer(Shader& argShader, GLint sampleColumns, GLint sampleRows);
	// destructor
	~SampleRenderer();
	// renders a quad textured with a sampled sprite, sample chosen by row and column indices
	void DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec4 color,
		GLint textureRow, GLint textureColumn);
	// initializes and configures the quad's buffer and vertex attributes
	void initRenderData();

	// sampling coordinate system
	GLint sampleColumns = -1;
	GLint sampleRows = -1;
};

#endif