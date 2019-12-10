#version 330

attribute vec3 position;

out vec3 texCoords;
															  
uniform mat4 projection;
uniform mat4 view;	

void main()
{
	gl_Position = projection * view * vec4(position,1.0f);
	texCoords = position;
};