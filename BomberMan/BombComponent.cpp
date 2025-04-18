#include "BombComponent.h"
#include "Timer.h"
#include "GridComponent.h"
#include "GameObject.h"
#include "ServiceLocator.h"


dae::BombComponent::BombComponent(GameObject* gameObject, GridComponent* gridComponent, int cellIndex, float timeToExplode) :
	Component(gameObject),
	m_pGridComponent{gridComponent},
	m_CellIndex{cellIndex},
	m_TimeToExplode{timeToExplode},
	m_AccumulatedTime{}
{
	
}

void dae::BombComponent::Update()
{
	m_AccumulatedTime += Time::GetInstance().m_DeltaTime;
	if (m_AccumulatedTime >= m_TimeToExplode)
	{
		ServiceLocator::GetSoundSystem().Play(make_sdbm_hash("ExplodeBombSFX"), 100.f);
		m_pGridComponent->ExplodeBomb(m_CellIndex, 2);
		GetGameObject()->Destroy(); //destroy bomb after explosion
	}
}
