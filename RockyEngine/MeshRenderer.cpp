#include "pch.h"
#include "MeshRenderer.h"
#include "Entity.h"
#include "Common.h"
#include "Application.h"
#include "Camera.h"


MeshRenderer::MeshRenderer(Model* model, ShaderProgram* program)
{
	m_program = program;
	m_default = program;
	m_model = model;
	m_texture = nullptr;
}
MeshRenderer::MeshRenderer(Mesh* mesh, ShaderProgram* program, Texture* texture)
{
	m_model = nullptr;
	m_mesh = mesh;
	m_program = program;
	m_texture = texture;
}
MeshRenderer::MeshRenderer(Model* model, ShaderProgram* program, Texture* texture)
{
	m_program = program;
	m_model = model;
	m_texture = texture;
}
void MeshRenderer::OnAttach()
{
	if (m_model == nullptr)
	{
		if (m_texture == nullptr)
		{
			m_texture = Resources::GetInstance()->GetTexture("missing.png");
			LOG_WARNING("Texture nullptr, default assigned");
		}

		return;
	}
	else
	{
		meshes = m_model->GetMeshes();

		if (m_model->hasMaterials)
		{
			textures = m_model->GetTextures();
			meshTexIds = m_model->GetMeshTexIds();
		}
		else
		{
			if (m_texture == nullptr)
			{
				m_texture = Resources::GetInstance()->GetTexture("missing.png");
				LOG_WARNING("Texture nullptr, default assigned");
			}
		}
	}
}
void MeshRenderer::OnUpdate(float deltaTime)
{

}
void MeshRenderer::OnRender()
{
	//glm::mat4 model = m_entity->GetTransform()->GetTransformationMatrix();
	//m_program->SetUniformMat4("model", model);
	
	if (m_model != nullptr)
	{
		if (m_model->hasMaterials == true)
		{
			for (unsigned int i = 0; i < meshes.size(); i++)
			{
				unsigned int materialInd = meshTexIds[i];

				if (materialInd < textures.size() && textures[materialInd])
				{
					textures[materialInd]->Bind();
				}

				meshes[i]->Bind();
			}
		}
		else
		{
			for (unsigned int i = 0; i < meshes.size(); i++)
			{
				m_texture->Bind();
				meshes[i]->Bind();
			}
		}
	}
	else
	{
		m_texture->Bind();
		m_mesh->Bind();
	}
	
}