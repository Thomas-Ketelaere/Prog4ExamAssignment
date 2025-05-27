#include "SpawnBombComponent.h"
#include <Hash.h>
#include "SceneManager.h"
#include "GridComponent.h"
#include "GameManager.h"
#include "BombComponent.h"
#include "SpriteSheetComponent.h"

game::SpawnBombComponent::SpawnBombComponent(RamCoreEngine::GameObject* gameObject):
	Component(gameObject)
{
	m_Range = game::GameManager::GetInstance().GetBombRange();
	m_RemoteExplode = game::GameManager::GetInstance().RemoteExplodeActive();
	m_MaxAmountBombs = game::GameManager::GetInstance().GetMaxBombs();
}

void game::SpawnBombComponent::Start()
{
	RamCoreEngine::GameObject* gridObject = RamCoreEngine::SceneManager::GetInstance().GetCurrentScene()->GetFirstObjectWithTag(make_sdbm_hash("Grid"));
	m_pGridComponent = gridObject->GetComponent<GridComponent>();
}

void game::SpawnBombComponent::Notify(Event event, RamCoreEngine::GameObject*)
{
	if (event.id == make_sdbm_hash("BombExploded"))
	{
		--m_CurrentAmountBombs;
	}

	else if (event.id == make_sdbm_hash("CollectedFlamesPU"))
	{
		++m_Range;
	}
	else if (event.id == make_sdbm_hash("CollectedExtraBombPU"))
	{
		++m_MaxAmountBombs;
	}
	else if (event.id == make_sdbm_hash("CollectedDetonatorPU"))
	{
		m_RemoteExplode = true;
	}

}


game::SpawnBombComponent::~SpawnBombComponent()
{
	game::GameManager::GetInstance().SaveBombRange(m_Range);
	game::GameManager::GetInstance().SaveRemoteExplode(m_RemoteExplode);
	game::GameManager::GetInstance().SaveMaxBombs(m_MaxAmountBombs);
}

void game::SpawnBombComponent::SpawnBomb(const glm::vec2 position)
{
	if (m_CurrentAmountBombs < m_MaxAmountBombs)
	{
		if (m_pGridComponent->IsCellWalkable(position, true)) //checking if cell is empty to spawn
		{
			int index = m_pGridComponent->GetIndexFromPosition(position);
			glm::vec2 spawnPosition = m_pGridComponent->GetCellPositionFromIndexWorld(index);
			glm::vec3 gridPos = m_pGridComponent->GetTransform()->GetWorldPosition();
			glm::vec2 spawnPosMoved{};
			spawnPosMoved.x = spawnPosition.x - gridPos.x;
			spawnPosMoved.y = spawnPosition.y - gridPos.y;
			auto bombObject = std::make_unique<RamCoreEngine::GameObject>();
			bombObject->SetParent(m_pGridComponent->GetGameObject(), true);
			auto bombComponent = std::make_unique<BombComponent>(bombObject.get(), m_pGridComponent, index, 2.f, m_Range);
			auto bombSpriteComponent = std::make_unique<RamCoreEngine::SpriteSheetComponent>(bombObject.get(), "Bomb.png", 3, 1, 0.2f, false);
			m_pGridComponent->GetCellFromPosition(position)->m_pBombComponent = bombComponent.get();
			bombObject->SetLocalPosition(glm::vec3(spawnPosMoved.x, spawnPosMoved.y, 0.f));
			bombObject->AddComponent(std::move(bombComponent));
			bombObject->AddComponent(std::move(bombSpriteComponent));
			RamCoreEngine::SceneManager::GetInstance().GetCurrentScene()->Add(std::move(bombObject));
			++m_CurrentAmountBombs;
		}
	}
	

}
