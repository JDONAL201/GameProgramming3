#pragma once
#include "pch.h"
#include "Common.h"
#include "Transform.h"
#include "Application.h"
enum CameraType { PERSPECTIVE, ORTHOGRAPHIC , FPS };
class Camera
{
private:
	Transform* m_parentTransform;
	glm::mat4 m_projMatrix, m_viewMatrix, VP;
	CameraType m_type = CameraType::PERSPECTIVE;
	float m_nearPlane = 0.1f;
	float m_farPlane = 1000.f;
	union
	{
		float m_fov = 45.f;
		float m_bottom;
	};
	union
	{
		float m_ratio =1280.f / 720.f; //TODO: fix the macros so that we can use (float) WINDOW_W etc instead , accessible from one place
		float m_left;
	};
	float m_right = 0;
	float m_top = 0;


	Camera();
public:

	Camera(Transform* parent, CameraType type = CameraType::PERSPECTIVE);
	void Recalculate();
	inline glm::mat4 Get() { return VP; }
	void SetFPS();
	void SetParentTransform(Transform* transform) {
		m_parentTransform =
			transform;
	}
	Transform* GetParentTransform() { return m_parentTransform; }
	inline glm::mat4 GetView() { return m_viewMatrix; }
	inline glm::mat4 GetProj() { return m_projMatrix; }
	inline CameraType GetType() { return m_type; }
	//sets the perspective projection
	void SetProjPersp(float fov, float ratio, float nearPlane, float
		farPlane);
	//sets the orthographic projection
	void SetProjOrtho(float left, float right, float bottom, float top,
		float nearPlane, float farPlane);

	//glm::vec3 forward = glm::vec3(0.f, 0.f, 1.0f);
	//glm::vec3 worldUp = glm::vec3(0.f, 0.f, 0.f);
	//glm::vec3 right = glm::vec3(1.f, 0.f, 0.f);
	//glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);
};