#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;
uniform vec2 sampleDivider;
uniform vec2 sampleOffset;

void main()
{
    TexCoords = vec2(vertex.z / sampleDivider.x + sampleOffset.x, 
					vertex.w / sampleDivider.y + sampleOffset.y);
    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
}