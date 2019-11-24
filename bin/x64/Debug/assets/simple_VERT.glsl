#version 420
layout (location = 0) in vec3 inPos;

uniform mat4 MVP;
uniform vec3 objectColor;
out vec4 out_color;



void main()
{
	gl_Position = MVP * vec4(inPos,1.0);
	out_color = vec4(objectColor,1.0);
}