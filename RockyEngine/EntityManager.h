#pragma once
#include "pch.h"
#include "Entity.h"
class EntityManager
{


private:

	static EntityManager* m_instance;
	EntityManager();
	~EntityManager();
	Transform* m_transform; //for moving entity
	float m_velocity; // for moving entity
	std::string temp = "Empty Entity";
	unsigned int emptyCount = 0;

	//float pitch = 0.f;
	//float yaw = 0.f;
	//float rotSpeed = 0.1f;

public:
	std::unordered_map<std::string, std::shared_ptr<Entity>>  m_entities;
	static EntityManager* GetInstance();
	std::shared_ptr<Entity> CreateEntity(std::string tag);

	std::shared_ptr<Entity> GetEntity(const std::string& name);
	void DisplayAllEntities();
	void ReleaseEntities();
	/*void MovableEntity(Entity* m_entity, float deltaTime, float speed);
	void Rotate(Entity* entity, double mouseX, double mouseY);*/
	
	void Destroy(std::shared_ptr<Entity> entity);
	void Destroy(std::string entityID);
	void Destroy(std::shared_ptr<Entity> entity, float deltaTime,float delay);

};

