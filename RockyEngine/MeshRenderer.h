#pragma once
#include "Component.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "Texture.h"



class MeshRenderer : public Component
{
private:



	std::shared_ptr<Mesh> m_mesh;
	std::shared_ptr<Texture> m_texture;
	std::shared_ptr <Model> m_model;
	std::shared_ptr <ShaderProgram> m_program;
	std::shared_ptr<ShaderProgram> m_default;

	std::vector<Texture*> textures;
	std::vector<unsigned int> meshTexIds;

public:
	// Inherited via Component
	MeshRenderer(std::shared_ptr<Mesh> mesh, std::shared_ptr<ShaderProgram> program, std::shared_ptr<Texture> texture);
	MeshRenderer(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> program, std::shared_ptr<Texture> texture);
	MeshRenderer(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> program);
	virtual void OnAttach() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;
	std::vector<Mesh*> meshes;
};

