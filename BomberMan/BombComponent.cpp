#include "BombComponent.h"
#include "Timer.h"
#include "GridComponent.h"
#include "GameObject.h"
#include "ServiceLocator.h"
#include "GameManager.h"


game::BombComponent::BombComponent(RamCoreEngine::GameObject* gameObject, GridComponent* gridComponent, int cellIndex, float timeToExplode, int range) :
	Component(gameObject),
	m_pGridComponent{gridComponent},
	m_CellIndex{cellIndex},
	m_TimeToExplode{timeToExplode},
	m_AccumulatedTime{},
	m_Range{range}
{
	
}

void game::BombComponent::Update()
{
	m_AccumulatedTime += RamCoreEngine::Time::GetInstance().m_DeltaTime;
	if (m_AccumulatedTime >= m_TimeToExplode)
	{
		Explode();
	}
}

void game::BombComponent::Explode()
{
	game::GameManager().GetInstance().BombExploded();
	RamCoreEngine::ServiceLocator::GetSoundSystem().Play(make_sdbm_hash("ExplodeBombSFX"), 100);
	m_pGridComponent->ExplodeBomb(m_CellIndex, m_Range);
	GetGameObject()->Destroy(); //destroy bomb after explosion
}
