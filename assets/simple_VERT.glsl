#version 420
layout (location = 0) in vec3 inPos;
layout (location = 2) in vec2 inTexcoords;

uniform mat4 MVP;
uniform vec3 objectColor;
out vec4 out_color;
out vec2 out_texCoords;


void main()
{
	gl_Position = MVP * vec4(inPos,1.0);
	out_color = vec4(objectColor,1.0);
	out_texCoords = inTexcoords;
}