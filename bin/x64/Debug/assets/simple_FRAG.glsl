#version 420

out vec4 fragColor;
in vec4 out_color;
in vec2 out_texCoords;

uniform sampler2D useTexture;

void main()
{
	fragColor = texture(useTexture, out_texCoords) * out_color;
}