#pragma once
#include "Component.h"
namespace game
{
	class EnemyScoreEffectComponent final : public RamCoreEngine::Component
	{
	public:
		EnemyScoreEffectComponent(RamCoreEngine::GameObject* gameObject, int score, float lifeTime);

		void Update() override;

	private:
		const float m_LifeTime;
		float m_AccumulatedTime{};
	};
}


