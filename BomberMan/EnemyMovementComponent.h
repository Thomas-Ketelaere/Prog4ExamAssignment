#pragma once
#include "Component.h"
#include <glm.hpp>
#include <vector>
#include <memory>
#include <string>

namespace RamCoreEngine
{
	class SpriteSheetComponent;
	class Subject;
}

namespace game
{
	class GridComponent;

	class EnemyMovementComponent final : public RamCoreEngine::Component
	{
	public:
		EnemyMovementComponent(RamCoreEngine::GameObject* gameObject, const float speed, const int scoreWhenDead);
		EnemyMovementComponent(RamCoreEngine::GameObject* gameObject, const float speed, const int scoreWhenDead, bool shouldTrackPlayer, float triggerDistance);

		virtual void Start() override;
		virtual void Update() override;
		virtual void Render() const override;

		void StartDying();
		void SetDebugRendering(bool shouldDebugRender) { m_DebugRender = shouldDebugRender; }

		RamCoreEngine::Subject* GetEnemyDiedSubject() const { return m_pEnemyDiedEvent.get(); }

	private:
		void SetSpriteDirection();
		glm::vec2 GetRandomPlayerPositionInRange();
		std::unique_ptr<RamCoreEngine::Subject> m_pEnemyDiedEvent;
		RamCoreEngine::SpriteSheetComponent* m_pSpriteSheetComponent = nullptr;
		GridComponent* m_pGridComponent = nullptr;
		std::vector<glm::vec2> m_Path;
		std::vector<RamCoreEngine::GameObject*> m_pPlayers;
		const int m_ScoreWhenDead;

		const float m_Speed;
		const float m_DistanceToReachPoint{ 2.f };
		const float m_TriggerDistance{};

		unsigned int m_PathIndex{};

		bool m_DebugRender{};
		bool m_IsDying{};
		bool m_ShouldTrackPlayer{};
	};

}


