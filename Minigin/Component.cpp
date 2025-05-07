#include "Component.h"
#include "GameObject.h"

RamCoreEngine::Component::Component(GameObject* gameObject)
{
	m_pGameObject = gameObject;
	m_pTransform = gameObject->GetTransform();

}
