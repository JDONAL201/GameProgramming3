#pragma once
#include "Shader.h"
class ShaderProgram
{
private:
	//TODO: TRACK CURRENTLY ACTIVE SHADER
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
};

