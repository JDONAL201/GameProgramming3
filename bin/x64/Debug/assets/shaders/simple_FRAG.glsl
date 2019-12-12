#version 420

in vec4 vColor;
in vec2 texCoords;
in vec3 normal;
in vec3 fragPosition;
in vec4 lightSpacePosition;


out vec4 fragColor;

struct Directional
{
	vec3 color;
	float ambient_Intensity;
	vec3 direction;
	float diffuse_Intensity;

};

struct Material
{
	float specular_Intensity;
	float shine_Strength;
	
};
uniform sampler2D m_texture;
uniform sampler2D m_shadowMap;

uniform Directional directional;
uniform Material material;

uniform vec3 viewPosition;
uniform bool blinn;


float CalculateShadowFactor()
{
	vec3 projCoords = lightSpacePosition.xyz / lightSpacePosition.w;
	projCoords = (projCoords * 0.5) + 0.5;
	
	//float closest = texture(m_shadowMap, projCoords.xy).r;
	float current = projCoords.z;
	
	vec3 nNormal = normalize(normal);
	vec3 lightDirection = normalize(directional.direction);

	float bias = max(0.01 * (1 - dot(nNormal,lightDirection)),0.0005);
	//float shadow = current - bias > closest ? 1.0 : 0.0;
	float shadow = 0.0;

	vec2 texelSize = 1.0 / textureSize(m_shadowMap, 0);
	for (int i = -1; i <= 1; ++i)
	{
		for (int j = -1; j <= 1; ++j)
		{
			float pcfDepth = texture(m_shadowMap, projCoords.xy + vec2(i, j) * texelSize).r;
			shadow += current - bias > pcfDepth ? 1.0 : 0.0;
		}
	}

	shadow /= 9.0;

	if(projCoords.z >1.0)
	{
		shadow = 0.0;
	}
	return shadow;

}

void main()
{
	vec4 ambient_Color = vec4(directional.color,1.0f) * directional.ambient_Intensity;
	
	float diffuseFactor = max(dot(normalize(normal),normalize(directional.direction)),0.0f);
	vec4 diffuse_Color = vec4(directional.color , 1.0f) * directional.diffuse_Intensity * diffuseFactor;
	
	
	vec4 specular_Color = vec4(0,0,0,0);
	
	if(diffuseFactor > 0.0f)
	{
		vec3 viewDirection = normalize(viewPosition - fragPosition);
		
		float specularFactor = 0.0f;
		
		if(blinn)
		{
			vec3 halfwayDirection = normalize(directional.direction + viewDirection);
			specularFactor = dot(normal,halfwayDirection);
		}
		else
		{
			vec3 reflectDirection = normalize(reflect(directional.direction, normalize(normal)));
			specularFactor = dot(viewDirection,reflectDirection);
		}
		
		if(specularFactor > 0.0f)
		{
			specularFactor = pow(specularFactor,material.shine_Strength);
			specular_Color = vec4(directional.color * material.specular_Intensity * specularFactor , 1.0f);
		}
	}
	
	fragColor = texture(m_texture,texCoords) * (ambient_Color + ( 1.0 - CalculateShadowFactor()) * (diffuse_Color + specular_Color));
	
	
}
