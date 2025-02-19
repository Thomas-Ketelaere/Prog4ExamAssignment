#include "Component.h"
#include "GameObject.h"

dae::Component::Component(GameObject* gameObject)
{
	m_pGameObject = gameObject;
	m_pTransform = gameObject->GetTransform();
}
