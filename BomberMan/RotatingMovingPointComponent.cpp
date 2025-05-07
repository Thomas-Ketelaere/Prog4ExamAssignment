#include "RotatingMovingPointComponent.h"
#include "GameObject.h"
#include "MovementComponent.h"

game::RotatingMovingPointComponent::RotatingMovingPointComponent(RamCoreEngine::GameObject* gameObject):
	Component(gameObject)
{
}

void game::RotatingMovingPointComponent::Start()
{
	m_MovementComponent = GetGameObject()->GetComponent<MovementComponent>();
	m_Parent = GetGameObject()->GetParent();

	auto newRotationPoint = m_Parent->GetWorldPosition();
	m_MovementComponent->SetRotationPoint(newRotationPoint.x, newRotationPoint.y);

	m_MovementComponent->CalculateRadiusAndAngle(); // have to do this, otherwise radius will not be correct
}

void game::RotatingMovingPointComponent::Update()
{
	auto newRotationPoint = m_Parent->GetWorldPosition();
	m_MovementComponent->SetRotationPoint(newRotationPoint.x, newRotationPoint.y);
}
