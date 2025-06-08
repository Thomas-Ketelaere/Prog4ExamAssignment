#pragma once
#include "Component.h"
#include "Observer.h"
#include <glm.hpp>
#include <queue>
#include "BombComponent.h"

namespace game
{
	class GridComponent;
	class PlayerSpriteComponent;
	class SpawnBombComponent final : public RamCoreEngine::Component, public RamCoreEngine::Observer
	{
	public:
		SpawnBombComponent(RamCoreEngine::GameObject* gameObject, float strengthRumble, float timeRumble);
		~SpawnBombComponent() = default;
		SpawnBombComponent(const SpawnBombComponent& other) = delete;
		SpawnBombComponent(SpawnBombComponent&& other) = delete;
		SpawnBombComponent& operator=(const SpawnBombComponent& other) = delete;
		SpawnBombComponent& operator=(SpawnBombComponent&& other) = delete;

		void Start() override;
		void Update() override;
		void OnDestroy() override;
		void Notify(Event event, RamCoreEngine::GameObject* gameObject) override;

		void SpawnBomb(const glm::vec2 position);
		void RemoteExplodeBomb();

	private:
		std::queue<BombComponent*> m_Bombs{};
		PlayerSpriteComponent* m_pPlayerSpriteComponent{};
		GridComponent* m_pGridComponent{};
		const float m_TimeToExplode{ 1.5f };
		int m_Range;
		int m_MaxAmountBombs;
		int m_CurrentAmountBombs{};
		bool m_RemoteExplode;

		//rumble
		const float m_StrengthRumble;
		const float m_TimeRumble;
		float m_AccumulatedTime{};
		bool m_BombExploded{};

	};
}
