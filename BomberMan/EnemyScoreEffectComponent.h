#pragma once
#include "Component.h"
#include "glm.hpp"

namespace RamCoreEngine
{
	class TextureComponent;
}

namespace game
{
	class EnemyScoreEffectComponent final : public RamCoreEngine::Component
	{
	public:
		EnemyScoreEffectComponent(RamCoreEngine::GameObject* gameObject, int score, float lifeTime, glm::vec2 position);
		~EnemyScoreEffectComponent() = default;
		EnemyScoreEffectComponent(const EnemyScoreEffectComponent& other) = delete;
		EnemyScoreEffectComponent(EnemyScoreEffectComponent&& other) = delete;
		EnemyScoreEffectComponent& operator=(const EnemyScoreEffectComponent& other) = delete;
		EnemyScoreEffectComponent& operator=(EnemyScoreEffectComponent&& other) = delete;

		void Update() override;

	private:
		RamCoreEngine::TextureComponent* m_ScoreTextureComp;
		const float m_LifeTime;
		float m_AccumulatedTime{};
	};
}


