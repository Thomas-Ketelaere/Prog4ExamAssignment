#include "Component.h"
#include "GameObject.h"
#include "TransformComponent.h"

RamCoreEngine::Component::Component(GameObject* gameObject)
{
	m_pGameObject = gameObject;
}

RamCoreEngine::TransformComponent* RamCoreEngine::Component::GetTransform() const
{
	return m_pGameObject->GetTransform();
}
