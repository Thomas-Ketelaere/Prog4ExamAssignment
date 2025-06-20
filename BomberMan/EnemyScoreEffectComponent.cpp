#include "EnemyScoreEffectComponent.h"
#include "Timer.h"
#include "GameObject.h"
#include "TextureComponent.h"

game::EnemyScoreEffectComponent::EnemyScoreEffectComponent(RamCoreEngine::GameObject* gameObject, int score, float lifeTime, glm::vec2 position):
	Component(gameObject),
	m_LifeTime{lifeTime}
{
	std::string scorePath = "Scores/Score" + std::to_string(score) + ".png";
	auto scoreTextComp = std::make_unique<RamCoreEngine::TextureComponent>(gameObject, scorePath, true);
	scoreTextComp->SetCustomPosition(position);
	m_ScoreTextureComp = scoreTextComp.get();
	gameObject->AddComponent(std::move(scoreTextComp));
}

void game::EnemyScoreEffectComponent::Update()
{
	m_AccumulatedTime += RamCoreEngine::Time::GetInstance().m_DeltaTime;
	if (m_AccumulatedTime >= m_LifeTime)
	{
		/*GetGameObject()->Destroy();*/
		m_ScoreTextureComp->Destroy();
		Destroy();
	}
}
