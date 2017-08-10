#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;
uniform vec2 sampleDivider;
uniform vec2 sampleOffset;
uniform bool mirrorXAxis;
uniform bool mirrorYAxis;

void main()
{
    TexCoords = vec2((vertex.z + sampleOffset.x)/ sampleDivider.x, 
					(vertex.w + sampleOffset.y) / sampleDivider.y);
	
	if (mirrorXAxis)
		TexCoords.x = (1.0 - sampleOffset.x)/sampleDivider.x - TexCoords.x;
    if (mirrorYAxis)
		TexCoords.y = (1.0 - sampleOffset.y)/sampleDivider.y - TexCoords.y;
		
	gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
}