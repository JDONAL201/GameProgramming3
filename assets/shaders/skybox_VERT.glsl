#version 420
layout(location = 0) in vec3 inPosition;
layout(location = 2) in vec2 inCoords;
out vec3 texCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
	gl_Position = projection * view * vec4(inPosition, 1.0f);
	texCoords = inPosition;
};