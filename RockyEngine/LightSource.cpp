#include "pch.h"
#include "LightSource.h"

LightSource::LightSource()
{
	//Setting default
	m_color = glm::vec3(1.f, 1.f, 1.f); //default white light
	m_ambientIntensity = 1.0f; //full strength;
	m_diffuseIntensity = 0.5f; 
}

LightSource::LightSource(float shadowWidth, float shadowHeight, glm::vec3 rgb, float ambientIntensity, float diffuseIntensity)
{
	m_shadowMap = new ShadowMapping();
	m_shadowMap->Init(shadowWidth,shadowHeight);

	m_color = rgb;
	m_ambientIntensity = ambientIntensity;
	m_diffuseIntensity = diffuseIntensity;
}

LightSource::~LightSource()
{
}

