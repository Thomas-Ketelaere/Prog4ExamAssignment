#include "EnemyCollider.h"
#include "GameObject.h"
#include "ColliderComponent.h"
#include <Events.h>
#include "LivesComponent.h"

dae::EnemyCollider::EnemyCollider(GameObject* gameObject, const float width, const float height):
	Component(gameObject)
{
	
	m_pEnemyCollider = std::make_unique<ColliderComponent>(gameObject, width, height);
}

void dae::EnemyCollider::AddPlayerCollider(ColliderComponent* playerCollider)
{
	m_pPlayerColliders.emplace_back(playerCollider);
}

void dae::EnemyCollider::LateUpdate()
{
	for(ColliderComponent* playerCollider : m_pPlayerColliders)
	if (m_pEnemyCollider->IsColliding(playerCollider))
	{
		auto playerLivesComponent = playerCollider->GetGameObject()->GetComponent<LivesComponent>();
		if (playerLivesComponent != nullptr)
		{
			playerLivesComponent->LoseLive();
		}
	}
}
