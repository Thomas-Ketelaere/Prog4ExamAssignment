#include "TimerLevelComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "Timer.h"
#include "SceneManager.h"
#include <Hash.h>
#include "GridComponent.h"
#include "EnemyCollider.h"
#include "EnemyMovementComponent.h"
#include "ScoreTextComponent.h"
#include "Subject.h"
#include "SpriteSheetComponent.h"
#include "GameManager.h"

game::TimerLevelComponent::TimerLevelComponent(RamCoreEngine::GameObject* gameObject, float timeForLevel, int amountEnemiesAfterTime):
	Component(gameObject),
	m_TimeForLevel{timeForLevel},
	m_AmountEnemiesAfterTime{amountEnemiesAfterTime}
{
}

void game::TimerLevelComponent::Start()
{
	m_TimeTextComponent = GetGameObject()->GetComponent<RamCoreEngine::TextComponent>();
}

void game::TimerLevelComponent::Update()
{
	m_TimeForLevel -= RamCoreEngine::Time::GetInstance().m_DeltaTime;
	if (m_TimeForLevel <= 0)
	{
		
		auto enemies = RamCoreEngine::SceneManager::GetInstance().GetCurrentScene()->GetAllObjectsWithTag(make_sdbm_hash("Enemy"));
		for (auto& enemy : enemies)
		{
			enemy->Destroy();
		}
		RamCoreEngine::GameObject* gridObject = RamCoreEngine::SceneManager::GetInstance().GetCurrentScene()->GetFirstObjectWithTag(make_sdbm_hash("Grid"));
		GridComponent* gridComponent = gridObject->GetComponent<GridComponent>();
		auto playerScoreTextChange = RamCoreEngine::SceneManager::GetInstance().GetCurrentScene()->GetFirstObjectWithTag(make_sdbm_hash("ScoreText"));
		ScoreTextComponent* scoreTextComp = playerScoreTextChange->GetComponent<ScoreTextComponent>();
		for (int enemyCounter{}; enemyCounter < m_AmountEnemiesAfterTime; ++enemyCounter)
		{
			glm::vec2 enemyPos = gridComponent->GetRandomEmptyCellPosition();
			auto enemy = std::make_unique<RamCoreEngine::GameObject>();
			enemy->SetTag(make_sdbm_hash("Enemy"));
			enemy->SetParent(gridObject, true);
			enemy->SetLocalPosition(glm::vec3(enemyPos.x, enemyPos.y, 0));
			auto enemyCollider = std::make_unique<game::EnemyCollider>(enemy.get(), 25.f, 25.f, true);
			enemy->AddComponent(std::move(enemyCollider));
			auto enemyMovement = std::make_unique<game::EnemyMovementComponent>(enemy.get(), 100.f, 400, false, true, 100.f);
			enemyMovement->SetDebugRendering(true);
			enemyMovement->GetEnemyDiedSubject()->AddObserver(scoreTextComp);

			auto enemySprite = std::make_unique<RamCoreEngine::SpriteSheetComponent>(enemy.get(), "Minvo.png", 4, 3, 0.2f, false);
			enemy->AddComponent(std::move(enemyMovement));
			enemy->AddComponent(std::move(enemySprite));
			enemy->Start();
			RamCoreEngine::SceneManager::GetInstance().GetCurrentScene()->Add(std::move(enemy));
		}
		GameManager::GetInstance().SetAmountEnemies(m_AmountEnemiesAfterTime);
		Destroy();
	}
	else
	{
		if (m_TimeText != static_cast<int>(m_TimeForLevel)) // so text doesnt update the whole time
		{
			m_TimeText = static_cast<int>(m_TimeForLevel);
			std::string newTimeText = "Time " + std::to_string(m_TimeText);
			m_TimeTextComponent->ChangeText(newTimeText);
		}
	}
}
