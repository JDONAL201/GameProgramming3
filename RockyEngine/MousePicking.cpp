#include "pch.h"
#include "Camera.h"
#include "Input.h"
#include "RigidBody.h"
#include "MousePicking.h"

MousePicking::MousePicking()
{
	projectionMatrix = Application::Instance()->GetCamera()->GetProj();
	viewMatrix = Application::Instance()->GetCamera()->GetView();
}

void MousePicking::Update()
{
	viewMatrix = Application::Instance()->GetCamera()->GetView();
	ray = MouseRayCalculate();

	if (IntersectionInRange(0, ray_range, ray))
	{
		currentPoint = BinarySearch(0, 0, ray_range, ray);
		std::cout << "HELLLLLLLLLLO" << std::endl;
	}
	//m_entity->GetTransform()->SetPosition(glm::vec3(ray.x,0.0f,ray.z));

}

glm::vec3 MousePicking::MouseRayCalculate()
{
	float mouseX = INPUT->GetInstance()->GetMousePos().x;
	float mouseY = INPUT->GetInstance()->GetMousePos().y;
	glm::vec2 normalizedDeviceCoords = GetNormalizedDeviceCoords(mouseX, mouseY);
	glm::vec4 clipCoords = glm::vec4(normalizedDeviceCoords.x, normalizedDeviceCoords.y, -1.f, 1.f);
	glm::vec4 viewCoords = ClipToViewSpaceCoords(clipCoords);
	glm::vec3 worldRay = ViewToWorldCoords(viewCoords);

	return worldRay;
}
glm::vec4 MousePicking::ClipToViewSpaceCoords(glm::vec4 clipCoords)
{
	glm::mat4 inverseProjection = glm::inverse(projectionMatrix);
	glm::vec4 viewCoords = inverseProjection * clipCoords;

	return glm::vec4(viewCoords.x, viewCoords.y, -1.f, 0.f);
}
glm::vec3 MousePicking::ViewToWorldCoords(glm::vec4 vCoords)
{
	glm::mat4 inverseViewMatrix = glm::inverse(viewMatrix);
	glm::vec4 rayToWorld = inverseViewMatrix * vCoords;
	glm::vec3 mouseRay = glm::normalize(glm::vec3(rayToWorld.x, rayToWorld.y, rayToWorld.z));

	return mouseRay;
}
bool MousePicking::IntersectionInRange(float start, float end, glm::vec3 rayCast)
{
	glm::vec3 startingPoint = GetPointOnRay(rayCast, start);
	glm::vec3 endPoint = GetPointOnRay(rayCast, end);
	if (!isThrough(startingPoint) && isThrough(endPoint))
	{
		return true;
	}
	else
	{
		return false;
	}

}
glm::vec3 MousePicking::GetPointOnRay(glm::vec3 rayCast, float distance)
{
	glm::vec3 cameraPosition = Application::Instance()->GetCamera()->GetParentTransform()->GetPosition();
	glm::vec3 start = cameraPosition;
	glm::vec3 rayScale = glm::vec3(rayCast.x * distance, rayCast.y * distance, rayCast.z * distance);
	glm::vec3 pointOnRay = start + rayScale;
	return pointOnRay;
}
glm::vec3 MousePicking::BinarySearch(int count, float start, float finish, glm::vec3 ray)
{
	float mid = start + ((finish - start) / 2.f);
	if (count >= recursionCount)
	{
		glm::vec3 endPoint = GetPointOnRay(ray, mid);
		Entity* entity = GetEntity(endPoint.x, endPoint.z);

		if (entity != NULL)
		{
			return endPoint;
		}
		else
		{
			return {};
		}
	
	}

	if (IntersectionInRange(start, mid, ray)) 
	{
		return BinarySearch(count + 1, start, mid, ray);

	}
	else
	{
		return BinarySearch(count + 1, mid, finish, ray);
	}
}

bool MousePicking::isThrough(glm::vec3 testingPoint)
{
	Entity* entity = GetEntity(testingPoint.x, testingPoint.z);
	float height = 0;
	if (entity != nullptr)
	{
		height = entity->GetTransform()->GetPosition().y;
	}

	if (testingPoint.y < height)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Entity* MousePicking::GetEntity(float worldX, float worldY)
{
	return m_entity;
}
void MousePicking::SetEntity(Entity* entity)
{
	m_entity = entity;
}
glm::vec2 MousePicking::GetNormalizedDeviceCoords(float mouseX, float mouseY)
{
	float x = (2.f * mouseX) / Application::Instance()->GetWindowWidth() - 1;
	float y = (2.f * mouseY) / Application::Instance()->GetWindowHeight() - 1;
	
	return glm::vec2(x, -y);
}
