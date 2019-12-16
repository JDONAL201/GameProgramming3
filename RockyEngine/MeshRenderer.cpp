#include "pch.h"
#include "MeshRenderer.h"
#include "Entity.h"
#include "Common.h"
#include "Application.h"
#include "Camera.h"

MeshRenderer::MeshRenderer(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> program)
{
	m_program = program;
	m_default = program;
	m_model = model;
	m_texture = nullptr;
}
MeshRenderer::MeshRenderer(std::shared_ptr<Mesh> mesh, std::shared_ptr<ShaderProgram> program, std::shared_ptr<Texture> texture)
{
	m_model = nullptr;
	m_mesh = mesh;
	m_program = program;
	m_texture = texture;
}
MeshRenderer::MeshRenderer(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> program, std::shared_ptr<Texture> texture)
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
	if (Application::Instance()->GetRendererType() != RenderType::SHADOWPASS)
	{
		glm::mat4 model = m_entity->GetTransform()->GetTransformationMatrix();
		m_program->SetUniformMat4("model", model);
		m_program->Use(); //use defualt
	}
	
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