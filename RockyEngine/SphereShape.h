#pragma once
#include "CollisionShape.h"
class SphereShape : public CollisionShape
{
public:
	SphereShape(float radius);
private:
	float m_radius;
};

