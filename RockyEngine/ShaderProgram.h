#pragma once
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Shader.h"
class ShaderProgram
{
private:

	GLuint m_activeProgram;
	GLuint m_program;
	GLuint u_ambientColor, u_ambientIntensity, u_diffIntensity, u_direction, u_specular, u_shine,u_model;
	Shader* m_vertexShader, * m_fragmentShader;

	bool CheckForLinkErrors();

public:
	ShaderProgram(const std::string& vShaderFile, const std::string& fShaderFile);
	~ShaderProgram();

	void BindAttribLocation(GLuint location, const char* name);
	void Link();
	void Use();
	GLuint Get() { return m_program; }

	void SetUniformVec3(const std::string& name, const glm::vec3& value)const;
	void SetUniformMat4(const std::string& name, const glm::mat4& value)const;
	void  SetUniformFloat(const std::string& name, float value) const;
	void SetUniformInt(const std::string& name, bool value);
	GLuint GetUniformLocation(std::string uniformName);
	void SetDirectionalLight(DirectionalLight* directionalLight);


};
