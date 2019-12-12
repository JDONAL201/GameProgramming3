#pragma once
#include "ShadowMapping.h"
class LightSource
{
public:
	LightSource();
	LightSource(float shadowWidth,float shadowHeight, glm::vec3 rgb, float ambientIntensity,float diffuseIntensity);
	~LightSource();

	ShadowMapping* GetShadowMap() { return m_shadowMap; }
protected:
	glm::vec3 m_color;
	float m_ambientIntensity;
	float m_diffuseIntensity;

	glm::mat4 lightProj;
	ShadowMapping* m_shadowMap;
};

