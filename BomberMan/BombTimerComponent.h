#pragma once
#include "Component.h"

namespace game
{
	class BombComponent;
	class BombTimerComponent final : public RamCoreEngine::Component
	{
	public: 
		BombTimerComponent(RamCoreEngine::GameObject* gameObject, float timeToExplode);
		~BombTimerComponent() = default;
		BombTimerComponent(const BombTimerComponent& other) = delete;
		BombTimerComponent(BombTimerComponent&& other) = delete;
		BombTimerComponent& operator=(const BombTimerComponent& other) = delete;
		BombTimerComponent& operator=(BombTimerComponent&& other) = delete;

		virtual void Update() override;

	private:
		BombComponent* m_pBombComponent;
		const float m_TimeToExplode;
		float m_AccumulatedTime;
	};
}


