#pragma once
#include "CollisionShape.h"
class BoxShape : public CollisionShape
{
private:
	glm::vec3 m_halfExtents;

public:
	BoxShape(glm::vec3 halfExtents);
};

