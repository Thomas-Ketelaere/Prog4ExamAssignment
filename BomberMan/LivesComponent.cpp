#include "LivesComponent.h"
#include "Subject.h"
#include <SceneManager.h>


game::LivesComponent::LivesComponent(RamCoreEngine::GameObject* gameObject, int maxLives):
	Component(gameObject),
	m_CurrentLives{maxLives}
{
	m_pActorDiedEvent = std::make_unique<RamCoreEngine::Subject>();
}

void game::LivesComponent::LoseLive()
{
	if (m_CurrentLives > 0)
	{
		--m_CurrentLives;
		Event e (make_sdbm_hash("PlayerDied"));
		m_pActorDiedEvent->NotifyObservers(e, GetGameObject());
		RamCoreEngine::SceneManager::GetInstance().ReloadScene(); // cant say load scene, bcs this can differ from different levels
	}
}
