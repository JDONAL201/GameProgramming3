#version 420

in vec4 vColor;
in vec2 texCoords;
in vec3 normal;
in vec3 fragPosition;



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

uniform Directional directional;
uniform Material material;

uniform vec3 viewPosition;
uniform bool blinn;

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
	

	fragColor = texture(m_texture,texCoords) * (ambient_Color + diffuse_Color + specular_Color);
	
	
}
