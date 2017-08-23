 #version 330 core
in vec4 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec4 spriteColor;

void main()
{
    color = vec4(spriteColor) * texture(image, TexCoords.zw);
	if (TexCoords.x < -.495f || TexCoords.x > 0.495f)
		color.a = .75;
}  