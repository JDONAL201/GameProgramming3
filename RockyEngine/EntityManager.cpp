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

std::shared_ptr<Entity> EntityManager::CreateEntity(std::string tag)
{
	if (m_entities.find(tag) == m_entities.end())
	{
		m_entities[tag] = std::shared_ptr<Entity>(new Entity());
		return m_entities[tag];
	}
	else
	{
		for (int i = 0; i < m_entities.size(); i++)
		{
			std::string newTag = tag + "(" + std::to_string(i) +")";

			if (m_entities.find(newTag) == m_entities.end())
			{
				m_entities[newTag] = std::shared_ptr<Entity>(new Entity());
				return m_entities[newTag];
			}
		}
	}
}

std::shared_ptr<Entity> EntityManager::GetEntity(const std::string& name)
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
	LOG_RESOURCE("============ALL ACTIVE ENTITIES=============== ");
	unsigned int count = 0;
	for (auto itr = m_entities.begin(); itr != m_entities.end(); itr++)
	{
		LOG_RESOURCE("[ Entity : " + std::to_string(count) + "] : " + itr->first);
		count += 1;
	}
}
void EntityManager::ReleaseEntities()
{
	
}
void EntityManager::Destroy(std::shared_ptr<Entity> entity)
{
}
void EntityManager::Destroy(std::string entityID)
{
	
}
void EntityManager::Destroy(std::shared_ptr<Entity> entity, float deltaTime, float delay)
{
	//Removed 
}
EntityManager::~EntityManager()
{
	ReleaseEntities();
}
