#include "pch.h"
#include "CameraComponent.h"
#include "Camera.h"
void CameraComponent::OnUpdate(float deltaTime)
{

}
void CameraComponent::OnRender()
{
}
void CameraComponent::Start(CameraType type)
{
	m_camera = new Camera(m_entity->GetTransform(), type);
	if (Application::Instance()->GetCamera() == nullptr)
	{
		Application::Instance()->SetCamera(m_camera);
	}
}