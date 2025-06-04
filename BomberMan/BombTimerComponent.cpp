#include "BombTimerComponent.h"
#include "GameObject.h"
#include "BombComponent.h"
#include "Timer.h"

game::BombTimerComponent::BombTimerComponent(RamCoreEngine::GameObject* gameObject, float timeToExplode):
	Component(gameObject),
	m_TimeToExplode{ timeToExplode },
	m_AccumulatedTime{}
{
	m_pBombComponent = GetGameObject()->GetComponent<BombComponent>();
}

void game::BombTimerComponent::Update()
{
	m_AccumulatedTime += RamCoreEngine::Time::GetInstance().m_DeltaTime;
	if (m_AccumulatedTime >= m_TimeToExplode)
	{
		m_pBombComponent->Explode();
	}
}
