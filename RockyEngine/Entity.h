#pragma once
#include "pch.h"
#include "Transform.h"
#include "Component.h"
#include "Common.h"
	class Entity
	{
	private:
		std::vector <Component*> m_components;
		Transform* m_transform = nullptr;
	public:
		Entity();
		void AddComponent(Component* c);
		template < class T > void AddComponent();
		template<class T> T* GetComponent();
		void OnUpdate(float deltaTime);
		void OnRender();
		Transform* GetTransform() { return m_transform; };

		std::string m_tag =  "";
};


template < class T >
void Entity::AddComponent()
{
	T* t = new T();
	Component* c = dynamic_cast <Component*>(t);
	if (c != nullptr)
	{
		c->m_entity = this;
		m_components.push_back(c);
	}
	else
	{
		LOG_WARNING("Can't add component, does not inherit from Component" );
	}
}
//TODO:entity GetComponent function template goes HERE!
template<class T>
T* Entity::GetComponent()
{
	for (auto& c : m_components)
	{
		T* cd = dynamic_cast<T*>(c);
		if (cd != nullptr)
		{
			return cd;
		}

	}
	return nullptr;
}

