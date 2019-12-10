#include "pch.h"
#include "MeshRenderer.h"
#include "Entity.h"
#include "Common.h"
#include "Application.h"
#include "Camera.h"


MeshRenderer::MeshRenderer(Model* model, ShaderProgram* program)
{
	m_program = program;
	m_model = model;
	m_texture = nullptr;
}
MeshRenderer::MeshRenderer(Model* model, ShaderProgram* program, Texture* texture) 
{
	m_program = program;
	m_model = model;
	m_texture = texture;
}
void MeshRenderer::OnAttach()
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
void MeshRenderer::OnUpdate(float deltaTime)
{

}
void MeshRenderer::OnRender()
{
	m_program->Use();

	//set uniforms here!
	glm::mat4 model = m_entity->GetTransform()->GetTransformationMatrix();
	glm::mat4 view = Application::Instance()->GetCamera()->GetView();
	glm::mat4 projection = Application::Instance()->GetCamera()->GetProj();
	glm::vec3 viewPosition = Application::Instance()->GetCamera()->GetParentTransform()->GetPosition();

	m_program->SetUniformMat4("proj", projection);
	m_program->SetUniformMat4("view", view);
	m_program->SetUniformMat4("model", model);
	m_program->SetUniformVec3("viewPosition",glm::vec3(viewPosition.x, viewPosition.y, viewPosition.z));

	m_program->SetUniformVec3("directional.color", glm::vec3(1.0f, 1.f, 1.f));
	m_program->SetFloat("directional.ambient_Intensity", 0.1f);
	m_program->SetUniformVec3("directional.direction", glm::vec3(0.f, -1.f, 0.f));
	m_program->SetFloat("directional.diffuse_Intensity", 0.8f);
	m_program->SetFloat("material.specular_Intensity", 1.0f);
	m_program->SetFloat("material.shine_Strength", 32);
	m_program->SetUniformBoolean("blinn", true);

	
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