#include "CapsuleShape.h"

CapsuleShape::CapsuleShape(float radius, float height)
{
	m_height = height;
	m_radius = radius;

	m_shape = new btCapsuleShape(radius,height);

	m_type = CShapeType::CAPSULE;
}
