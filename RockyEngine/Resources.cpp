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
		m_models[directory] = std::shared_ptr<Model>(new Model(MODEL_PATH + directory));//,TEXTURE_PATH + texturePath);

		LOG_INFO("Model Loaded from " + directory);
	}
}
void Resources::AddModelWithMat(const std::string& directory, const std::string& texturePath)
{
	if (m_models.find(directory) == m_models.end())
	{
		m_models[directory] = std::shared_ptr<Model>(new Model(MODEL_PATH + directory,TEXTURE_PATH + texturePath));
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
		m_textures[directory] = std::shared_ptr<Texture>(new Texture(TEXTURE_PATH + directory));
		m_textures[directory]->Load();
	//	LOG_INFO("Texture Loaded from " + directory);
	}
}
std::shared_ptr<ShaderProgram> Resources::GetShader(const std::string& name)
{
	return m_shaderPrograms[name];
}
std::shared_ptr<Model> Resources::GetModel(const std::string& name)
{
	if (m_models.find(name) == m_models.end())
	{
		LOG_ERROR("Model doesnt exist: Returning error default");
		return m_models["error.obj"];
	}
	return m_models[name];
}
std::shared_ptr<Texture> Resources::GetTexture(const std::string& name)
{
	if (m_textures.find(name) == m_textures.end())
	{
		LOG_ERROR("Texture doesnt exist: Returning missing default");
		return m_textures["missing.png"];
	}
	return m_textures[name];
}


void Resources::ReleaseResources()
{
	//No longer need to be released as smart pointers will do this 
}
Resources::~Resources()
{
	ReleaseResources();
}