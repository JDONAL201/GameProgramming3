#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>


Texture::Texture(const std::string& directory)
{
	m_directory = directory;
	m_textureID = 0;
}
bool Texture::Load()
{
	int width = 0, height = 0, nrChannels = 0;
	unsigned char* data = stbi_load(m_directory.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		GL_ATTEMPT(glGenTextures(1, &m_textureID));
		GL_ATTEMPT(glBindTexture(GL_TEXTURE_2D, m_textureID));

		GL_ATTEMPT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GL_ATTEMPT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GL_ATTEMPT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GL_ATTEMPT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));


		auto glChannels = GL_RGBA;

		switch (nrChannels)
		{
		case 3:
			glChannels = GL_RGB;
			break;
		case 4:
			glChannels = GL_RGBA;
			break;
		}


		GL_ATTEMPT(glTexImage2D(GL_TEXTURE_2D, 0, glChannels, width, height, 0, glChannels, GL_UNSIGNED_BYTE, data);
		GL_ATTEMPT(glGenerateMipmap(GL_TEXTURE_2D)));
		glBindTexture(GL_TEXTURE_2D, 0);

	}
	else
	{
		LOG_ERROR("Failed to load texture");
		return false;
	}

	stbi_image_free(data);
	return true;
}

void Texture::ReleaseTexture()
{
	glDeleteTextures(1, &m_textureID);
	m_textureID = 0;
	m_directory = "";
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}
