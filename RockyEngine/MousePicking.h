#pragma once
class MousePicking
{
public:
	MousePicking();
	void Update();

	glm::vec3 MouseRayCalculate();
	Entity* m_entity;
	glm::vec3 GetRay() { return ray; }
	void SetEntity(Entity* entity);
private:
	glm::vec3 ray;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	glm::vec2 GetNormalizedDeviceCoords(float mouseX, float mouseY);
	glm::vec4 ClipToViewSpaceCoords(glm::vec4 clipCoords);
	glm::vec3 ViewToWorldCoords(glm::vec4 viewCoords);
	bool IntersectionInRange(float start, float end, glm::vec3 rayCast);
	glm::vec3 GetPointOnRay(glm::vec3 rayCast,float distance);
	glm::vec3 BinarySearch(int count, float start, float finish, glm::vec3 ray);
	int recursionCount = 200;
	float ray_range = 600;
	bool isThrough(glm::vec3 testingPoint);
	Entity* GetEntity(float worldX, float worldY);
	glm::vec3 currentPoint;
	
};

