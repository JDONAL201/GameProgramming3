#include "pch.h"
#include "ShaderProgram.h"
#include "Common.h"

ShaderProgram::ShaderProgram(const std::string& vShaderFile, const std::string& fShaderFiler)
{
	m_vertexShader = new Shader(vShaderFile, VERTEX_SHADER);
	m_fragmentShader = new Shader(fShaderFiler, FRAGEMENT_SHADER);
	CHECK_GL_ERROR();

	m_program = glCreateProgram();
	glAttachShader(m_program, m_vertexShader->Get());
	glAttachShader(m_program, m_fragmentShader->Get());

	Link();
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_program);
}

void ShaderProgram::BindAttribLocation(GLuint location, const char* name)
{
	glBindAttribLocation(m_program, location, name);
	CHECK_GL_ERROR();
}

void ShaderProgram::Link()
{
	glLinkProgram(m_program);
	CheckForLinkErrors();
	CHECK_GL_ERROR();

	//once linked no longer needed
	delete m_vertexShader;
	delete m_fragmentShader;
}

void ShaderProgram::Use()
{
	//TODO:: Only bind program if it isnt already bound ( keep track of currently in use, if this is currently in use no need to )
	glUseProgram(m_program);
}

bool ShaderProgram::CheckForLinkErrors()
{
	GLint isLinked = 0;
	glGetProgramiv(m_program, GL_LINK_STATUS, &isLinked);

	if (isLinked == GL_FALSE)
	{
		GLint length = 0;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &length);

		char* message = (char*)malloc(length);
		glGetProgramInfoLog(m_program, length, &length, message);

		printf("Shader linking error: %s\n", message);
		//LOG_ERROR("Shader linking error: {0}" ,message);
		free(message);
		glDeleteProgram(m_program);

		return true;
	}
	return false;
}