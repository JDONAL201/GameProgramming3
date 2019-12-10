#include "pch.h"
#include "Resources.h"


Resources::Resources()
{

}

Resources* Resources::m_instance = nullptr;

Resources* Resources::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new Resources();
	}

	return m_instance;
}

void Resources::AddModel(const std::string& directory)//, const std::string& texturePath)
{
	if (m_models.find(directory) == m_models.end())
	{
		m_models[directory] = new Model(MODEL_PATH + directory);//,TEXTURE_PATH + texturePath);

		LOG_INFO("Model Loaded from " + directory);
	}
}
void Resources::AddModelWithMat(const std::string& directory, const std::string& texturePath)
{
	if (m_models.find(directory) == m_models.end())
	{
		m_models[directory] = new Model(MODEL_PATH + directory,TEXTURE_PATH + texturePath);
		LOG_INFO("Model Loaded from " + directory);
	}
}
//void Resources::AddSkyboxFaces(const std::string& faceLocation)
//{
//	skyboxFaces.push_back(faceLocation);
//}
void Resources::AddTexture(const std::string& directory)
{
	if (m_textures.find(directory) == m_textures.end())
	{
		m_textures[directory] = new Texture(TEXTURE_PATH + directory);
		m_textures[directory]->Load();
	//	LOG_INFO("Texture Loaded from " + directory);
	}
}
ShaderProgram* Resources::GetShader(const std::string& name)
{
	return m_shaderPrograms[name];
}
Model* Resources::GetModel(const std::string& name)
{
	if (m_models.find(name) == m_models.end())
	{
		LOG_ERROR("Model doesnt exist: Returning defualt");
		return m_models["error.obj"];
	}
	return m_models[name];
}
Texture* Resources::GetTexture(const std::string& name)
{
	return m_textures[name];
}


void Resources::ReleaseResources()
{
	//using an iterator patter to iterate through all elemenets 

	/*for (auto iter = m_models.begin(); iter != m_models.end(); iter++)
	{
		delete iter->second;
	}*/
	for (auto iter = m_textures.begin(); iter != m_textures.end(); iter++)
	{
		delete iter->second;
	}

	for (auto iter = m_shaderPrograms.begin(); iter != m_shaderPrograms.end(); iter++)
	{
		delete iter->second;
	}

	//TODO: Release other resources properly like above? ^^
};
Resources::~Resources()
{
	ReleaseResources();
}