#include "pch.h"
#include "RigidBody.h"
#include "Physics.h"
#include "Entity.h"

void RigidBody::OnAttach()
{

}

void RigidBody::OnUpdate(float deltaTime)
{
}

void RigidBody::OnRender()
{
}

void RigidBody::Init(CollisionShape* shape, float mass, const glm::vec3 localInertia)
{
	btTransform bT = Physics::ConvertTransformToBtTransform(*m_entity->GetTransform());
	m_mState = new btDefaultMotionState(bT);
	m_shape = shape;
	btVector3 li = btVector3(localInertia.x, localInertia.y,
		localInertia.z);
	m_shape->Get()->calculateLocalInertia(mass, li);
	m_rigidbody = new btRigidBody(btScalar(mass), m_mState,
		m_shape->Get(), li);
	Physics::GetInstance()->AddRigidbody(this);
	m_rigidbody->setSleepingThresholds(0, 0);
	m_rigidbody->setFriction(1);
}

void RigidBody::UpdateParent()
{
	btTransform bT;
	m_rigidbody->getMotionState()->getWorldTransform(bT);

	Physics::ConvertBtTransformToTransform(bT, m_entity->GetTransform());
}

void RigidBody::UpdateRigidBody()
{
	btTransform t = Physics::ConvertTransformToBtTransform(*m_entity->GetTransform());
	m_rigidbody->setWorldTransform(t);
	m_rigidbody->getMotionState()->setWorldTransform(t);
}

void RigidBody::AddForce(glm::vec3 forceDirection, glm::vec3 relPos,float forceAmount)
{
	btVector3 m_force = btVector3(forceDirection.x, forceDirection.y, forceDirection.z);
	btVector3 m_relPos = btVector3(relPos.x, relPos.y, relPos.z);
	m_force *= forceAmount;
	m_rigidbody->applyForce(m_force, m_relPos);
}

void RigidBody::AddTorque(glm::vec3 torque,float torqueAmount)
{

	btVector3 t = btVector3(torque.x, torque.y, torque.z);
	t *= torqueAmount;
	m_rigidbody->applyTorque(t);
}

