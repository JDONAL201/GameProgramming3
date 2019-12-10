#version 420
layout (location = 0) in vec3 inPosition;

uniform mat4 model;
uniform mat4 lightSpaceTransform;



void main()
{

	gl_Position = lightSpaceTransform * model *vec4(inPosition,1.0);

}