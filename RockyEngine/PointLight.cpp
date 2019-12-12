//#include "pch.h"
//#include "LightSource.h"
//#include "PointLight.h"
//
//PointLight::PointLight() : LightSource()
//{
//	m_position = glm::vec3(0.f, 0.f, 0.f);
//	m_constant = 1.0f;
//	m_linear = 0.0f;
//	m_exponent = 0.0f;
//}
//
//PointLight::PointLight(glm::vec3 rgb, float ambientIntensity, float diffuseIntensity, glm::vec3 position, float constant, float linear, float exponent) : LightSource(rgb,ambientIntensity,diffuseIntensity)
//{
//	m_position = position;
//	m_constant = constant;
//	m_exponent = exponent;
//	m_linear = linear;
//}
//
//PointLight::~PointLight()
//{
//}
//
//void PointLight::Use(GLuint colorLocation, GLuint ambientIntensityLocation, GLuint diffIntensityLocation, GLuint positionLocation, GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation)
//{
//	glUniform3f(colorLocation, m_color.x, m_color.y, m_color.z);
//	glUniform1f(ambientIntensityLocation, m_ambientIntensity);
//	glUniform1f(diffIntensityLocation, m_diffuseIntensity);
//	glUniform3f(positionLocation, m_position.x, m_position.y, m_position.z);
//	glUniform1f(constantLocation, m_constant);
//	glUniform1f(linearLocation, m_linear);
//	glUniform1f(constantLocation, m_exponent);
//}
