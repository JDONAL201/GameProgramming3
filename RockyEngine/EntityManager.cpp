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
