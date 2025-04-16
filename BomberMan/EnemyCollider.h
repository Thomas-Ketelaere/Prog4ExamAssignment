#pragma once
#include "Component.h"
#include <vector>
#include <memory>

namespace dae
{
	class ColliderComponent;
	class EnemyCollider final : public Component
	{
	public:
		EnemyCollider(GameObject* gameObject, const float width, const float height);
		void AddPlayerCollider(ColliderComponent* playerCollider);

		virtual void LateUpdate() override;

	private:
		std::unique_ptr<ColliderComponent>m_pEnemyCollider;
		std::vector<ColliderComponent*> m_pPlayerColliders;
	};
}


