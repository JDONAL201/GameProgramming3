#pragma once
#include "Component.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "Texture.h"



class MeshRenderer : public Component
{
private:
	//Mesh* m_mesh;
	Texture* m_texture;
	Model* m_model;
	ShaderProgram* m_program;

public:
	// Inherited via Component
	//MeshRenderer(Mesh* mesh, ShaderProgram* program, Texture* texture);
	MeshRenderer(Model* model, ShaderProgram* program, Texture* texture);
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

};

