#include "Component.h"
#include "Entity.h"
#include "ControllerComponent.h"
#include "Input.h"

void ControllerComponent::ControlEntityMovement(float deltaTime)
{
	m_velocity = deltaTime * m_speed; // create a velocity to move at

	if (INPUT->GetKey(SDLK_w) || INPUT->GetGamepad_LeftMotion().y < 0) // check keyboard and controller axis
	{
		m_Transform->AddPosition(m_Transform->GetForward() * m_velocity); // apply the velocity to the appropriate direction
	}

	if (INPUT->GetKey(SDLK_s) || INPUT->GetGamepad_LeftMotion().y > 0)
	{
		m_Transform->AddPosition(-m_Transform->GetForward() * m_velocity);
	}

	if (INPUT->GetKey(SDLK_a) || INPUT->GetGamepad_LeftMotion().x < 0)
	{
		m_Transform->AddPosition(-m_Transform->GetRight() * m_velocity);
	}

	if (INPUT->GetKey(SDLK_d) || INPUT->GetGamepad_LeftMotion().x > 0)
	{
		m_Transform->AddPosition(m_Transform->GetRight() * m_velocity);
	}

	if (INPUT->GamePadIsActive()) // is game pad active
	{
		//if so allow entity to rotate via control stick motion
		m_Transform->RotateEulerAxis(INPUT->GetGamepad_RightMotion().x * m_rotSpeed, m_Transform->GetRight());
		m_Transform->RotateEulerAxis(INPUT->GetGamepad_RightMotion().y * m_rotSpeed, glm::vec3(0.f, 1.f, 0.f));
	}


}
void ControllerComponent::ControlEntityRotation()
{
	// rotate eular axis relative to  mouse position
	glm::ivec2 MouseMotion = INPUT->GetMouseDelta();
	m_Transform->RotateEulerAxis(-MouseMotion.x * 0.5f, glm::vec3(0.f, 1.f, 0.f));
	m_Transform->RotateEulerAxis(-MouseMotion.y * 0.5f, m_Transform->GetRight());
}

void ControllerComponent::SetMouseMotion()
{
	ControlEntityRotation(); // so that its only updated when the mouse is moved
}

void ControllerComponent::OnAttach()
{
	m_Transform = m_entity->GetTransform(); // get the parent entity transform
}

void ControllerComponent::OnUpdate(float deltaTime)
{
	ControlEntityMovement(deltaTime); // update using delta time
}

void ControllerComponent::OnRender()
{
}
