#pragma once
#include "CollisionShape.h"

class CapsuleShape:public CollisionShape
{
public:
	CapsuleShape(float radius, float height);
private:
	float m_radius;
	float m_height;
};

