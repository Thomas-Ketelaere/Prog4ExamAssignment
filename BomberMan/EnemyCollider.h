#pragma once
#include "Component.h"
#include "Collider.h"

namespace game
{
	class EnemyCollider final : public RamCoreEngine::Component, public RamCoreEngine::Collider
	{
	public:
		EnemyCollider(RamCoreEngine::GameObject* gameObject, const float width, const float height, bool isTrigger);
		~EnemyCollider() = default;
		EnemyCollider(const EnemyCollider& other) = delete;
		EnemyCollider(EnemyCollider&& other) = delete;
		EnemyCollider& operator=(const EnemyCollider& other) = delete;
		EnemyCollider& operator=(EnemyCollider&& other) = delete;

		void OnTriggerOverlap(Collider* other) override;
	};
}
