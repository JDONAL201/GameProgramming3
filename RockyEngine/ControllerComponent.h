#pragma once
class ControllerComponent : public Component
{

private:
	//Entity* m_Entity = nullptr;
	Transform* m_Transform;
	float pitch = 0.f;
	float yaw = 0.f;
	float m_velocity;
	float m_speed = 2.0f;
	float m_rotSpeed = 0.5f;
	double mouseX, mouseY;

public:
	//void Start(Entity* entity, float moveSpeed, float rotSpeed);
	void ControlEntityMovement(float deltaTime);
	void ControlEntityRotation();
	void SetMouseMotion();
	virtual void OnAttach() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

};

