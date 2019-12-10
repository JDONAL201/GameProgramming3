#pragma once
#include "Component.h"
#include "Camera.h"
class CameraComponent : public Component
{
private:
	Camera* m_camera;
	CameraType type;
	// Inherited via Component
public:
	virtual void OnAttach() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;
	Camera* GetCamera() { return m_camera; } // pointer to the camera,so that we can obtain it from the entity its attached to?
};

