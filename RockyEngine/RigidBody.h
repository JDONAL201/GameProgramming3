#pragma once
#include "Component.h"
#include "Physics.h"
#include "CollisionShape.h"

class RigidBody : public Component
{
public:
	CollisionShape* m_shape;
	btRigidBody* m_rigidbody;
	btMotionState* m_mState = nullptr;
	float mass;

public:
	virtual void OnAttach() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

	void Init(CollisionShape* shape, float mass = 1.f, const glm::vec3 localInertia = glm::vec3(1));
	virtual void UpdateParent();
	virtual void UpdateRigidBody();

	void AddForce(glm::vec3 forceDirection, glm::vec3 relPos, float forceAmount);
	void AddTorque(glm::vec3 torque, float torqueAmount);

	btRigidBody* Get() { return m_rigidbody; }
};

