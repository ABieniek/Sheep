#ifndef TEXT_UTIL_H
#define TEXT_UTIL_H

#include <iostream>
#include <map>
#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// GL includes
#include "Shader.h"

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
	GLuint TextureID;   // ID handle of the glyph texture
	glm::ivec2 Size;    // Size of glyph
	glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
	GLuint Advance;    // Horizontal offset to advance to next glyph
};

class TextUtil
{
public:
	static GLuint VAO, VBO;
	static std::map<GLchar, Character> Characters;

	static void init();

	static void RenderText(Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec4 color);
};

#endif
