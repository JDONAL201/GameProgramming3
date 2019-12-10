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

	//TODO: USE SMART POINTERS
	std::unordered_map<std::string, ShaderProgram*> m_shaderPrograms;
	std::unordered_map<std::string, Model*> m_models;
	std::unordered_map<std::string, Texture*> m_textures;
	std::vector<std::string> skyboxFaces;

	static Resources* m_instance;
	Resources();
	~Resources();

public:
	
	static Resources* GetInstance(); //singleton
	//adds shader to the map , should be done at the start of application
	void AddShader(ShaderProgram* shader, std::string name)
	{
		m_shaderPrograms[name] = shader;
	}

	void AddModel(const std::string& directory);//, const std::string& texturePath);
	void AddModel(const std::string& name, Model* m) { m_models[name] = m; }

	void AddModelWithMat(const std::string& directory, const std::string& texturePath);

	void AddTexture(const std::string& directory);
	void AddTexture(const std::string& name, Texture* t) { m_textures[name] = t; }


	//void AddSkyboxFaces(const std::string& faceLocation);

	ShaderProgram* GetShader(const std::string& name);
	Model* GetModel(const std::string& name);
	Texture* GetTexture(const std::string& name);

	std::vector<std::string> GetSkyboxFaces() { return skyboxFaces; }
	//Deletes all the things!
	void ReleaseResources();
};

