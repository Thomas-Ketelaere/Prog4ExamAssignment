#include "TransformComponent.h"

dae::TransformComponent::TransformComponent(GameObject* gameObject):
	Component(gameObject)
{
}

void dae::TransformComponent::SetWorldPosition(const float x, const float y, const float z)
{
	m_WorldPosition.x = x;
	m_WorldPosition.y = y;
	m_WorldPosition.z = z;
}

void dae::TransformComponent::SetLocalPosition(float x, float y, float z)
{
	m_LocalPosition.x = x;
	m_LocalPosition.y = y;
	m_LocalPosition.z = z;
}
