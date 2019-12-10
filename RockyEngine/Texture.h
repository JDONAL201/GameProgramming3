#pragma once
#include "pch.h"
#include "Common.h"
class Texture
{
private:
	GLuint m_textureID;
	std::string m_directory;
public:
	Texture(const std::string& directory);
	bool Load();
	void ReleaseTexture();
	void Bind();
};

