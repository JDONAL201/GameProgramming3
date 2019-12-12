#pragma once

class SkyBox
{
public:
	SkyBox();
	SkyBox(std::vector<std::string>facePaths);
	void LoadSkybox();
	void RenderSkyBox(ShaderProgram* shader);

private:
	std::vector<std::string> m_faces;
	int width, height, channels;
	unsigned int faces = 6;
	unsigned int m_textureID;
	Mesh* skyboxCube;
};

