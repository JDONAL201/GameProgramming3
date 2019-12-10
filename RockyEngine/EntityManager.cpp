#include "pch.h"
#include "EntityManager.h"
#include "Input.h"

EntityManager* EntityManager::m_instance = nullptr;
EntityManager::EntityManager()
{

}
EntityManager* EntityManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new EntityManager();
	}

	return m_instance;
}

Entity* EntityManager::CreateEntity(std::string tag)
{
	if (m_entities.find(tag) == m_entities.end())
	{
		m_entities[tag] = new Entity();
		return m_entities[tag];
	}
	
	LOG_ERROR("Cannot create entity with same tagID : Change tag : " + tag);

}

Entity* EntityManager::GetEntity(const std::string& name)
{
	if (m_entities.find(name) == m_entities.end())
	{
		LOG_WARNING("No entity with ID  : " + name + " exists" );
	}
	else
	{

		return m_entities[name];
	}
}

void EntityManager::DisplayAllEntities()
{
	LOG_RESOURCE("All currently active entities : ");
	unsigned int count = 0;
	for (auto itr = m_entities.begin(); itr != m_entities.end(); itr++)
	{
		LOG_RESOURCE("[ Entity : " + std::to_string(count) + "] : " + itr->first);
		count += 1;
	}

}
void EntityManager::ReleaseEntities()
{
	for ( auto iter = m_entities.begin(); iter != m_entities.end(); iter++)
	{
		delete iter->second;
	}
}
//void EntityManager::MovableEntity(Entity* m_entity, float deltaTime, float speed)
//{
//	if (m_transform == NULL)
//	{
//		m_transform = m_entity->GetTransform();
//	}
//
//	m_velocity = deltaTime * speed;
//
//	if (INPUT->GetKey(SDLK_w))
//	{
//		m_transform->m_position += m_transform->m_forward * m_velocity;
//	}
//
//	if (INPUT->GetKey(SDLK_s))
//	{
//		m_transform->m_position -= m_transform->m_forward * m_velocity;;
//	}
//
//	if (INPUT->GetKey(SDLK_a))
//	{
//		m_transform->m_position -= m_transform->m_right * m_velocity;
//	}
//
//	if (INPUT->GetKey(SDLK_d))
//	{
//		m_transform->m_position += m_transform->m_right * m_velocity;
//	}
//
//
//}
//void EntityManager::Rotate(Entity* entity, double mouseX , double mouseY)
//{
//	mouseX *= rotSpeed; // multiply the amount to change by the rotation speed to turn smooth towards
//	mouseY *= rotSpeed;
//
//	yaw += mouseX; // update the yaw to add the change in x
//	pitch -= mouseY; // update the pitch to minus the change in y
//
//	if (pitch > 89.0f) // limit the pitch
//	{
//		pitch = 89.0f;
//	}
//	if (pitch < -89.0f) //limit the pitch
//	{
//		pitch = -89.0f;
//	}
//
//	entity->GetTransform()->m_forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));  // update forward to be relative to the pitch and yaw.
//	entity->GetTransform()->m_forward.y = sin(glm::radians(pitch));
//	entity->GetTransform()->m_forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//	entity->GetTransform()->m_forward = glm::normalize(entity->GetTransform()->m_forward); // normalise to obtain a unit vector in the forward direction
//	entity->GetTransform()->m_right = glm::normalize(glm::cross(entity->GetTransform()->m_forward, entity->GetTransform()->m_worldUp));// find the right angle , so right is always relative to world up
//	entity->GetTransform()->m_up = glm::normalize(glm::cross(entity->GetTransform()->m_right, entity->GetTransform()->m_forward));					// up can change thus why is not used instead of worldSpace up above which will always be up in the world.
//}
void EntityManager::Destroy(Entity* entity)
{
	for (auto iter = m_entities.begin(); iter != m_entities.end(); iter++)
	{
		if (iter->second == entity)
		{
			delete iter->second;
			m_entities.erase(iter);
			return;
		}
	}
}
void EntityManager::Destroy(std::string entityID)
{
	for (auto iter = m_entities.begin(); iter != m_entities.end(); iter++)
	{
		if (iter->first == entityID)
		{
			delete iter->second;
			m_entities.erase(iter);
			return;
		}
	}
}
void EntityManager::Destroy(Entity* entity, float deltaTime, float delay)
{
	bool found = false;

	for (auto iter = m_entities.begin(); iter != m_entities.end(); iter++)
	{
		if (iter->second == entity)
		{
			while (found == false)
			{
				if (delay > 0)
				{
					std::cout<<delay<<std::endl;
					delay -= deltaTime /100;
				}
				else 
				{
					delay = 0;
					found = true;
				}
			}
			delete iter->second;
			m_entities.erase(iter);
			break;
		}
	}
}
EntityManager::~EntityManager()
{
	ReleaseEntities();
}
