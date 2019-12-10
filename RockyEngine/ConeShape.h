#pragma once
#include "CollisionShape.h"
class ConeShape:public CollisionShape
{
public:
	ConeShape(float radius, float height);
private:

	float m_radius;
	float m_height;
};

