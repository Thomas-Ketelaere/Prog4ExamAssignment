#include "LoadingScreenComponent.h"
#include "Timer.h"
#include "SceneManager.h"
#include "GameManager.h"

game::LoadingScreenComponent::LoadingScreenComponent(RamCoreEngine::GameObject* gameObject, float timeToLoadLevel):
	Component(gameObject),
	m_TimeToLoadLevel{timeToLoadLevel}
{
}

void game::LoadingScreenComponent::Update()
{
	m_AccumulatedTime += RamCoreEngine::Time::GetInstance().m_DeltaTime;
	if (m_AccumulatedTime >= m_TimeToLoadLevel)
	{
		//load level
		std::string level = "Level" + std::to_string(game::GameManager::GetInstance().GetCurrentLevel());
		RamCoreEngine::SceneManager::GetInstance().LoadScene(level);
	}
}
