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
	std::unordered_map<std::string, Entity*>  m_entities;
	static EntityManager* GetInstance();
	Entity* CreateEntity(std::string tag);

	Entity* GetEntity(const std::string& name);
	void DisplayAllEntities();
	void ReleaseEntities();
	/*void MovableEntity(Entity* m_entity, float deltaTime, float speed);
	void Rotate(Entity* entity, double mouseX, double mouseY);*/
	
	void Destroy(Entity* entity);
	void Destroy(std::string entityID);
	void Destroy(Entity* entity, float deltaTime,float delay);

};

