#pragma once
#include "Component.h"
namespace game
{
	class ExplosionTimerComponent final : public RamCoreEngine::Component
	{
	public:
		ExplosionTimerComponent(RamCoreEngine::GameObject* gameObject, float timeExplosion);
		~ExplosionTimerComponent() = default;
		ExplosionTimerComponent(const ExplosionTimerComponent& other) = delete;
		ExplosionTimerComponent(ExplosionTimerComponent&& other) = delete;
		ExplosionTimerComponent& operator=(const ExplosionTimerComponent& other) = delete;
		ExplosionTimerComponent& operator=(ExplosionTimerComponent&& other) = delete;

		void Update() override;

	private:
		const float m_TimeExplosion;
		float m_AccumulatedTime{};
	};
}


