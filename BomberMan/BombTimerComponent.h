#pragma once
#include "Component.h"

namespace game
{
	class BombComponent;
	class BombTimerComponent final : public RamCoreEngine::Component
	{
	public: 
		BombTimerComponent(RamCoreEngine::GameObject* gameObject, float timeToExplode);

		virtual void Update() override;

	private:
		BombComponent* m_pBombComponent;
		const float m_TimeToExplode;
		float m_AccumulatedTime;
	};
}


