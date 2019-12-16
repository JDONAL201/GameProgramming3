#pragma once
#include "LightSource.h"

class DirectionalLight : public LightSource
{

public:
	DirectionalLight();
	~DirectionalLight();
	DirectionalLight(float shadowWidth, float shadowHeight, glm::vec3 rgb, float ambientIntensity, float diffuseIntensity, glm::vec3 direction, float specIntensity, float shineStrength);
	void Use(GLuint colorLocation, GLuint ambientIntensityLocation, GLuint diffIntensityLocation, GLuint directionLocation,GLuint specIntensityLocation, GLuint shineLocation);
	glm::mat4 CalculateLightTransform();

protected: //access by subclasses but not anything else
	glm::vec3 m_direction;
	float m_specularIntensity;
	float m_shineStrength;


};

