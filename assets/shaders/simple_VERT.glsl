#version 420

layout (location = 0) in vec3 inPosition;
layout (location = 2) in vec2 inTexCoords;
layout (location = 3) in vec3 inNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform mat4 lightSpaceTransform;


out vec4 vColor;
out vec2 texCoords;
out vec3 normal;
out vec3 fragPosition;
out vec4 lightSpacePosition;

void main()
{

	gl_Position = proj * view * model * vec4(inPosition,1.0);
	lightSpacePosition = lightSpaceTransform * model * vec4(inPosition,1.0);

	vColor = vec4(clamp(inPosition, 0.0f,1.0f),1.0f);
	texCoords = inTexCoords;
	normal = mat3(transpose(inverse(model)))*inNormal;
	fragPosition = (model * vec4(inPosition,1.0f)).xyz;

}