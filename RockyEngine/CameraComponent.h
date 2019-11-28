#pragma once
#include "Component.h"
#include "Camera.h"
class CameraComponent : public Component
{
private:
	Camera* m_camera;
	// Inherited via Component
public:
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;
	void Start(CameraType type);

	Camera* GetCamera() { return m_camera; } // pointer to the camera,so that we can obtain it from the entity its attached to?
};

