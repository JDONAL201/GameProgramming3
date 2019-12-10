#include "Model.h"


void Model::Load()
{
	Assimp::Importer importer; // create instance of importer
	const aiScene* scene = importer.ReadFile(m_directory, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices); //create pointer to scene, read in from file, Triangulate to split into triangles, flip our texture uv values, smooth normals , join identical vertices

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if there is no scene , of returned flags or no root node , error
	{
		LOG_ERROR(importer.GetErrorString()); //log error
		return;
	}
	processNode(scene->mRootNode, scene); //get the first node and the entire scene

	if (hasMaterials) 
	{
		LOG_DEBUG("HAS MATERIALS");
		processMaterials(scene); // pass the scene to the load materials function
	}
	
}
void Model::processNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		processMesh(scene->mMeshes[node->mMeshes[i]], scene); //process the mesh at the scenes list of meshes , iterate through all meshes and load them.
	}
	
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		//recursion, call the function we are in 
		processNode(node->mChildren[i], scene);
	}
}

void Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<int> indices;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		//process vertex position, normlas , colors and texture coords
		vertex.pos.x = mesh->mVertices[i].x;
		vertex.pos.y = mesh->mVertices[i].y;
		vertex.pos.z = mesh->mVertices[i].z;

		if (mesh->HasNormals())
		{
			vertex.normal.x = -mesh->mNormals[i].x;
			vertex.normal.y = -mesh->mNormals[i].y;
			vertex.normal.z = -mesh->mNormals[i].z;
		}

		if (mesh->mColors[0])
		{
			vertex.color.r = mesh->mColors[0][i].r;
			vertex.color.g = mesh->mColors[0][i].g;
			vertex.color.b = mesh->mColors[0][i].b;
			vertex.color.a = mesh->mColors[0][i].a;
		}
		else
		{
			vertex.color = glm::vec4(1.f);
		}

		if (mesh->mTextureCoords[0]) // does the mesh contain textures coords?
		{
			vertex.texture.x = mesh->mTextureCoords[0][i].x;
			vertex.texture.y = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			vertex.texture = glm::vec2(0.f, 0.f);
		}

		vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned  j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	Mesh* newMesh = new Mesh(vertices, indices);
	m_meshes.push_back(newMesh);
	m_meshToTexID.push_back(mesh->mMaterialIndex); //Where the material is in the material list, sync the texture being pointed to
	//return newMesh;
}
void Model::processMaterials(const aiScene* scene)
{
	m_textures.resize(scene->mNumMaterials); //create a size relative to the number of materials

	for (unsigned int i = 0; i < scene->mNumMaterials; i++)
	{
		aiMaterial* material = scene->mMaterials[i];

		m_textures[i] = nullptr;


		if (material->GetTextureCount(aiTextureType_DIFFUSE)) //can check different types of textures here if implementing normals etc TODO:: IF DOING NORMAL
		{
			aiString path;

			if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) //get the diffuse texture and place the path in our path string, check that it loaded successfully
			{
				//incase exported with the creators absolute file path, retreive just the end 
				int index = std::string(path.data).rfind("\\"); // convert path into regular string no aiString, then reverse through and fince "\" , 2 need as its an escape character
				std::string filename = std::string(path.data).substr(index + 1); // thiss will retrieve everything after the backslash and store in filename

				std::string texPath = m_texFolder  + filename;
				
				m_textures[i] = new Texture(texPath.c_str());

				//Changed texture class to a bool to check if the texture is able to load or not
				if (!m_textures[i]->Load())
				{
					//when failed to load, assign to null ptr 
					LOG_WARNING("Failed to load texture at: " + texPath);
					delete m_textures[i];
					m_textures[i] = nullptr;
				}

			}
		}

		if (!m_textures[i]) // if there isnt texture , then apply a defualt texture 
		{
			std::string assetPath = "assets//missing.png";
			m_textures[i] = new Texture(assetPath.c_str());
			m_textures[i]->Load();
		}
	}
}
Model::Model(const std::string& path ,const std::string& texFolder)
{
	m_directory = path;
	m_texFolder = texFolder;
	hasMaterials = true;
	Load();
}

Model::Model(const std::string& path)
{
	m_directory = path;
	hasMaterials = false;
	Load();
}
