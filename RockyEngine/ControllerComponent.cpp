#include "Component.h"
#include "Entity.h"
#include "ControllerComponent.h"
#include "Input.h"

void ControllerComponent::ControlEntityMovement(float deltaTime)
{
	m_velocity = deltaTime * m_speed;

	if (INPUT->GetKey(SDLK_w))
	{
		m_Transform->AddPosition(m_Transform->GetForward() * m_velocity);
	}

	if (INPUT->GetKey(SDLK_s))
	{
		m_Transform->AddPosition(-m_Transform->GetForward() * m_velocity);
	}

	if (INPUT->GetKey(SDLK_a))
	{
		m_Transform->AddPosition(-m_Transform->GetRight() * m_velocity);
	}

	if (INPUT->GetKey(SDLK_d))
	{
		m_Transform->AddPosition(m_Transform->GetRight() * m_velocity);
	}
}
void ControllerComponent::ControlEntityRotation()
{
	glm::ivec2 MouseMotion = INPUT->GetMouseDelta();
	m_Transform->RotateEulerAxis(-MouseMotion.x * 0.1f, glm::vec3(0.f, 1.f, 0.f));
	m_Transform->RotateEulerAxis(-MouseMotion.y * 0.1f, m_Transform->GetRight());
}

void ControllerComponent::SetMouseMotion()
{
	ControlEntityRotation();
}

void ControllerComponent::OnAttach()
{
	m_Transform = m_entity->GetTransform();
}

void ControllerComponent::OnUpdate(float deltaTime)
{
	ControlEntityMovement(deltaTime);
}

void ControllerComponent::OnRender()
{
}
