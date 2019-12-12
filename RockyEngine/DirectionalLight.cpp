#include "pch.h"
#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() : LightSource()
{
	//Setting default
	m_direction = glm::vec3(0.f, -1.f, 0.f); //default straight down
	lightProj = glm::ortho(-5.f, 5.f, -5.f, 5.f, 0.1f, 20.f);
}

DirectionalLight::DirectionalLight(float shadowWidth, float shadowHeight, glm::vec3 rgb, float ambientIntensity, float diffIntensity,glm::vec3 direction, float specIntensity,float shineStrength):LightSource(shadowWidth,shadowHeight,rgb ,ambientIntensity,diffIntensity)
{
	m_direction = direction;
	m_specularIntensity = specIntensity;
	m_shineStrength = shineStrength;
	lightProj = glm::ortho(-500.f, 500.f, -500.f, 500.f, 0.1f, 1000.f);
}

void DirectionalLight::Use(GLuint colorLocation, GLuint ambientIntensityLocation, GLuint diffIntensityLocation, GLuint directionLocation,GLuint specIntensityLocation,GLuint shineLocation)
{
	glUniform3f(colorLocation, m_color.x, m_color.y, m_color.z);
	glUniform1f(ambientIntensityLocation, m_ambientIntensity);
	glUniform1f(diffIntensityLocation, m_diffuseIntensity);
	glUniform3f(directionLocation, m_direction.x, m_direction.y, m_direction.z);
	glUniform1f(shineLocation, m_shineStrength);
	glUniform1f(specIntensityLocation, m_specularIntensity);
}
glm::mat4 DirectionalLight::CalculateLightTransform()
{
	return lightProj * glm::lookAt(-m_direction,glm::vec3(0.f,0.f,0.f),glm::vec3(0.0f,1.0f,0.0f));
}
DirectionalLight::~DirectionalLight()
{
}
