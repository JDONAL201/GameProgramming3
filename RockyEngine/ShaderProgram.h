#pragma once
#include "Shader.h"
class ShaderProgram
{
private:
	//TODO: TRACK CURRENTLY ACTIVE SHADER
	GLuint m_activeProgram;
	GLuint m_program;
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
	void  SetFloat(const std::string& name, float value) const;
	void SetUniformBoolean(const std::string& name, bool value);
};
