#include "BombComponent.h"
#include "Timer.h"
#include "GridComponent.h"
#include "GameObject.h"
#include "ServiceLocator.h"


game::BombComponent::BombComponent(RamCoreEngine::GameObject* gameObject, GridComponent* gridComponent, int cellIndex, float timeToExplode) :
	Component(gameObject),
	m_pGridComponent{gridComponent},
	m_CellIndex{cellIndex},
	m_TimeToExplode{timeToExplode},
	m_AccumulatedTime{}
{
	
}

void game::BombComponent::Update()
{
	m_AccumulatedTime += RamCoreEngine::Time::GetInstance().m_DeltaTime;
	if (m_AccumulatedTime >= m_TimeToExplode)
	{
		RamCoreEngine::ServiceLocator::GetSoundSystem().Play(make_sdbm_hash("ExplodeBombSFX"), 100);
		m_pGridComponent->ExplodeBomb(m_CellIndex, 1);
		GetGameObject()->Destroy(); //destroy bomb after explosion
	}
}
