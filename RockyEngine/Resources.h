#pragma once
#include "pch.h"
#include "Common.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Entity.h"

class Resources
{
private:

	std::unordered_map<std::string,std::shared_ptr<ShaderProgram>> m_shaderPrograms;
	std::unordered_map<std::string, std::shared_ptr<Model>> m_models;
	std::unordered_map<std::string, std::shared_ptr<Texture>> m_textures;
	std::vector<std::string> skyboxFaces;

	static Resources* m_instance;
	Resources();
	~Resources();

public:
	
	static Resources* GetInstance(); //singleton
	//adds shader to the map , should be done at the start of application
	
	void AddShader(const std::string name, const std::string& VshaderPath, const std::string& FshaderPath)
	{
		if (m_shaderPrograms.find(name) == m_shaderPrograms.end())
		{
			m_shaderPrograms[name] = std::shared_ptr<ShaderProgram>(new ShaderProgram(SHADER_PATH + VshaderPath, SHADER_PATH + FshaderPath));
		}
	}

	void AddModel(const std::string& directory);//, const std::string& texturePath);
	void AddModel(const std::string& name, std::shared_ptr<Model> m) { m_models[name] = m; }

	void AddModelWithMat(const std::string& directory, const std::string& texturePath);

	void AddTexture(const std::string& directory);
	void AddTexture(const std::string& name, std::shared_ptr<Texture> t) { m_textures[name] = t; }


	//void AddSkyboxFaces(const std::string& faceLocation);

	std::shared_ptr<ShaderProgram> GetShader(const std::string& name);
	std::shared_ptr<Model> GetModel(const std::string& name);
	std::shared_ptr<Texture> GetTexture(const std::string& name);

	std::vector<std::string> GetSkyboxFaces() { return skyboxFaces; }
	//Deletes all the things!
	void ReleaseResources();
};

