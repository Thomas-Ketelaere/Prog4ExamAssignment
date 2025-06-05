#include "SpawnBombComponent.h"
#include <Hash.h>
#include "SceneManager.h"
#include "GridComponent.h"
#include "GameManager.h"
#include "BombComponent.h"
#include "SpriteSheetComponent.h"
#include "BombTimerComponent.h"
#include "PlayerSpriteComponent.h"

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
	m_pPlayerSpriteComponent = GetGameObject()->GetComponent<PlayerSpriteComponent>();
}

void game::SpawnBombComponent::Notify(Event event, RamCoreEngine::GameObject*)
{
	if (event.id == make_sdbm_hash("BombExploded"))
	{
		if (m_CurrentAmountBombs > 0) // when in coop, first player spawns one, but this will get called also on second player who hasnt spawned bomb
		{
			--m_CurrentAmountBombs;
			if (m_RemoteExplode)
			{
				m_Bombs.pop();
			}
		}
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
	if (m_pPlayerSpriteComponent->IsDying())
	{
		return;
	}
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
			auto bombComponent = std::make_unique<BombComponent>(bombObject.get(), m_pGridComponent, index, m_Range);
			BombComponent* bombCompPtr = bombComponent.get(); //getting component in BombTimer but still need it for grid and queue
			bombObject->AddComponent(std::move(bombComponent));
			if (!m_RemoteExplode) //if not yet have ability, add timer so explodes after some time
			{
				auto bombTimerComponent = std::make_unique<BombTimerComponent>(bombObject.get(), m_TimeToExplode);
				bombObject->AddComponent(std::move(bombTimerComponent));
			}
			else
			{
				m_Bombs.push(bombCompPtr);
			}
			auto bombSpriteComponent = std::make_unique<RamCoreEngine::SpriteSheetComponent>(bombObject.get(), "Bomb.png", 3, 1, 0.2f, false);
			m_pGridComponent->GetCellFromPosition(position)->m_pBombComponent = bombCompPtr;
			bombObject->SetLocalPosition(glm::vec3(spawnPosMoved.x, spawnPosMoved.y, 0.f));
			bombObject->AddComponent(std::move(bombSpriteComponent));
			RamCoreEngine::SceneManager::GetInstance().GetCurrentScene()->Add(std::move(bombObject));
			++m_CurrentAmountBombs;
		}
	}
}

void game::SpawnBombComponent::RemoteExplodeBomb()
{
	if (m_pPlayerSpriteComponent->IsDying())
	{
		return;
	}
	if (m_Bombs.size() > 0)
	{
		BombComponent* bombComponent = m_Bombs.front();
		bombComponent->Explode();
		//not poping here, bomb can trigger other bomb, but here wouldnt get popped, so done in BombExploded event
	}
}
