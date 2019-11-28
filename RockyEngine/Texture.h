#pragma once
#include "pch.h"
#include "Common.h"
class Texture
{
private:
	GLuint m_texture;
	std::string m_directory;

public:
	Texture(std::string path);
	static GLuint Load(const std::string& directory);
	void Bind();
};

