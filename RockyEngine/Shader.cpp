#include "pch.h"
#include "Shader.h"
#include "Common.h"

Shader::Shader(const std::string& fileName, SHADER_TYPE type)
{
	m_shader = LoadShaderFromFile(fileName, type);

	if (CheckForCompileErrors(fileName))
	{
		m_shader = 0;
	}
}

Shader::~Shader()
{
	if (m_shader != 0)
	{
		glDeleteShader(m_shader);
	}
}

GLuint Shader::LoadShaderFromMemory(const char* pMemory, SHADER_TYPE type)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &pMemory, NULL);
	glCompileShader(shader);
	return shader;

}
GLuint Shader::LoadShaderFromFile(const std::string& fileName, SHADER_TYPE type)
{
	std::string fileContents;
	std::ifstream file;

	file.open(fileName.c_str(), std::ios::in);

	if (!file)
	{
		LOG_WARNING("File not could not be loaded");
		return 0;
	}

	if (file.good())
	{
		file.seekg(0, std::ios::end);
		unsigned long len = (unsigned long)file.tellg();
		file.seekg(std::ios::beg);

		if (len == 0)
		{
			LOG_WARNING("File has no contents");
			return 0;
		}

		fileContents.resize(len);
		file.read(&fileContents[0], len);
		file.close();
		GLuint program = LoadShaderFromMemory(fileContents.c_str(), type);

		return program;
	}

	return 0;
}

bool Shader::CheckForCompileErrors(const std::string& fileName)
{
	GLint isCompiled = 0;
	glGetShaderiv(m_shader, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_FALSE)
	{
		GLint errorLength = 0;
		glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &errorLength);

		char* message = (char*)malloc(errorLength);

		LOG_ERROR("Error compiling a shader " + fileName + " " + message);

		free(message);

		glDeleteShader(m_shader);
		return true;
	}
	return false;
}

