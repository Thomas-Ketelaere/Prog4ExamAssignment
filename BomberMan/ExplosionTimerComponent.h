#pragma once
#include "Component.h"
namespace game
{
	class ExplosionTimerComponent final : public RamCoreEngine::Component
	{
	public:
		ExplosionTimerComponent(RamCoreEngine::GameObject* gameObject, float timeExplosion);
		void Update() override;

	private:
		const float m_TimeExplosion;
		float m_AccumulatedTime{};
	};
}


