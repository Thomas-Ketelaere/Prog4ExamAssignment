#include "BombComponent.h"
#include "GridComponent.h"
#include "GameObject.h"
#include "ServiceLocator.h"

game::BombComponent::BombComponent(RamCoreEngine::GameObject* gameObject, GridComponent* gridComponent, int cellIndex, int range) :
	Component(gameObject),
	m_pGridComponent{gridComponent},
	m_CellIndex{cellIndex},
	m_Range{range}
{
}

void game::BombComponent::Explode()
{
	RamCoreEngine::ServiceLocator::GetSoundSystem().Play(make_sdbm_hash("ExplodeBombSFX"), 100);
	m_pGridComponent->ExplodeBomb(m_CellIndex, m_Range);
	GetGameObject()->Destroy(); //destroy bomb after explosion
}
