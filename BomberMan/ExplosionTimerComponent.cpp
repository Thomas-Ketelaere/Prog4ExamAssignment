#include "ExplosionTimerComponent.h"
#include "GameObject.h"
#include "Timer.h"

game::ExplosionTimerComponent::ExplosionTimerComponent(RamCoreEngine::GameObject* gameObject, float timeExplosion):
	Component(gameObject),
	m_TimeExplosion{timeExplosion}
{
}

void game::ExplosionTimerComponent::Update()
{
	m_AccumulatedTime += RamCoreEngine::Time::GetInstance().m_DeltaTime;
	if (m_AccumulatedTime >= m_TimeExplosion)
	{
		GetGameObject()->Destroy();
	}
}
