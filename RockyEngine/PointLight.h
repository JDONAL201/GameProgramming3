#pragma once
class PointLight : public LightSource
{

public:
	PointLight();
	PointLight(glm::vec3 rgb, float ambientIntensity, float diffuseIntensity, glm::vec3 position, float constant, float linear, float exponent);
	~PointLight();
	
	void Use(GLuint colorLocation, GLuint ambientIntensityLocation, GLuint diffIntensityLocation, GLuint positionLocation, 
			GLuint constantLocation,GLuint linearLocation,GLuint exponentLocation);
private:
	glm::vec3 m_position;
	float m_constant, m_linear, m_exponent;

};

