#include "pch.h"
#include "CameraComponent.h"
#include "Camera.h"

void CameraComponent::OnAttach()
{
	m_camera = new Camera(m_entity->GetTransform(), CameraType::PERSPECTIVE);
	if (Application::Instance()->GetCamera() == nullptr)
	{
		Application::Instance()->SetCamera(m_camera);
	}
}
void CameraComponent::OnUpdate(float deltaTime)
{
}
void CameraComponent::OnRender()
{
}
//void CameraComponent::Start(CameraType type)
//{
//
//}
