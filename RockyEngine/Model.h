#pragma once
#include "Mesh.h"
#include "Vertex.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Texture.h"
class Model
{
private:
	std::vector<Mesh*> m_meshes;
	std::string m_directory;

	void Load();
	void processNode(aiNode* node, const aiScene* scene);
	Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
	
	//TODO MATERIALS
	//void processMaterial(const aiScene* scene, const std::string& textFolder);
	//std::vector<Texture*> m_textures;
	//std::vector<unsigned int> meshToTexture;

public:
	Model(std::string path);
	std::vector<Mesh*> GetMeshes() { return m_meshes; }
};

