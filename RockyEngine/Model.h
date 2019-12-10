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
	std::vector<Texture*> m_textures;
	std::vector<unsigned int> m_meshToTexID;

	 std::string m_directory;
	 std::string m_texFolder;

	void Load();
	void processNode(aiNode* node, const aiScene* scene); 
	void processMesh(aiMesh* mesh, const aiScene* scene);
	void processMaterials(const aiScene* scene);

public:
	void RenderModel();
	std::vector<Mesh*> GetMeshes() { return m_meshes; }
	std::vector<Texture*> GetTextures() { return m_textures; }
	std::vector<unsigned int> GetMeshTexIds(){ return m_meshToTexID; }
	Model(const std::string& path, const std::string& texPath);
	Model(const std::string& path);
	bool hasMaterials = false;
};

