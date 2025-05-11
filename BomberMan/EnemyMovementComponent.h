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
	class EnemyMovementComponent; // to forward it for ENemy states
	//State Pattern
	class EnemyState
	{
	public:
		EnemyState(EnemyMovementComponent* component) { m_pComponent = component; }
		virtual ~EnemyState() = default;
		virtual void OnEnter() {};
		virtual void OnExit() {};
		virtual std::unique_ptr<EnemyState> Update() = 0;

		EnemyMovementComponent* GetComponent() { return m_pComponent; }

	private:
		EnemyMovementComponent* m_pComponent;
	};

	class WanderingState final : public EnemyState
	{
	public:
		WanderingState(EnemyMovementComponent* component, float speed, bool shouldTrackPlayer, float triggerDistance) : EnemyState(component), m_Speed{ speed }, m_ShouldTrackPlayer{ shouldTrackPlayer }, m_TriggerDistance{ triggerDistance } {};
		void OnEnter() override;
		std::unique_ptr<EnemyState> Update() override;

	private:
		std::vector<glm::vec2> m_Path;
		unsigned int m_PathIndex{ 1 };
		const float m_DistanceToReachPoint{ 2.f };
		const float m_Speed;
		bool m_ShouldTrackPlayer{};
		const float m_TriggerDistance{};
	};

	class ChaseState final : public EnemyState
	{
	public:
		ChaseState(EnemyMovementComponent* component, float speed, float triggerDistance) : EnemyState(component), m_Speed{ speed }, m_TriggerDistance{ triggerDistance } {};
		void OnEnter() override;
		std::unique_ptr<EnemyState> Update() override;

	private:
		glm::vec2 GetRandomPlayerPositionInRange();
		std::vector<glm::vec2> m_Path;
		unsigned int m_PathIndex{ 1 };
		const float m_DistanceToReachPoint{ 2.f };
		const float m_Speed;
		const float m_TriggerDistance{};
	};

	class DyingState final : public EnemyState
	{
	public:
		DyingState(EnemyMovementComponent* component, float timeToDie) : EnemyState(component), m_TimeToDie{ timeToDie }, m_AccumulatedTime{} {};
		std::unique_ptr<EnemyState> Update() override;

	private:
		const float m_TimeToDie;
		float m_AccumulatedTime;
	};

	class GridComponent;

	class EnemyMovementComponent final : public RamCoreEngine::Component
	{
	public:
		EnemyMovementComponent(RamCoreEngine::GameObject* gameObject, const float speed, const int scoreWhenDead);
		EnemyMovementComponent(RamCoreEngine::GameObject* gameObject, const float speed, const int scoreWhenDead, bool shouldTrackPlayer, float triggerDistance);



		void Start() override;
		void Update() override;
		void Render() const override;
		void OnDestroy() override;
		void SetSpriteDirection(glm::vec2 direction);

		void StartDying();
		void SetDebugRendering(bool shouldDebugRender) { m_DebugRender = shouldDebugRender; }

		GridComponent* GetGridComponent() { return m_pGridComponent; }
		std::vector<RamCoreEngine::GameObject*> GetPlayers() { return m_pPlayers; }
		RamCoreEngine::SpriteSheetComponent* GetSpriteSheet() { return m_pSpriteSheetComponent; }

		RamCoreEngine::Subject* GetEnemyDiedSubject() const { return m_pEnemyDiedEvent.get(); }

	private:
		
		glm::vec2 GetRandomPlayerPositionInRange();
		std::unique_ptr<RamCoreEngine::Subject> m_pEnemyDiedEvent;
		RamCoreEngine::SpriteSheetComponent* m_pSpriteSheetComponent = nullptr;
		GridComponent* m_pGridComponent = nullptr;
		
		std::vector<RamCoreEngine::GameObject*> m_pPlayers;
		const int m_ScoreWhenDead;

		const float m_Speed;
		
		bool m_ShouldTrackPlayer{};
		const float m_TriggerDistance{};

		bool m_DebugRender{};
		bool m_IsDying{};

		std::unique_ptr<EnemyState> m_pEnemyState;
	};

	

}


