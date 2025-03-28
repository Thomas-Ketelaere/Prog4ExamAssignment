#include "BombComponent.h"
#include "Timer.h"
#include "GridComponent.h"


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
		m_pGridComponent->ExplodeBomb(m_CellIndex, 1);
	}
}
