#include "SpawnBombCommand.h"
#include "GridComponent.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Hash.h"
#include "GameManager.h"

game::SpawnBombCommand::SpawnBombCommand(RamCoreEngine::GameObject* actor):
	GameActorCommand(actor)
{
}

void game::SpawnBombCommand::Start()
{
	RamCoreEngine::GameObject* gridObject = RamCoreEngine::SceneManager::GetInstance().GetCurrentScene()->GetFirstObjectWithTag(make_sdbm_hash("Grid"));
	m_pGridComponent = gridObject->GetComponent<GridComponent>();
}

void game::SpawnBombCommand::Execute()
{
	if (game::GameManager::GetInstance().CanSpawnBomb())
	{
		m_pGridComponent->SpawnBomb(GetGameActor()->GetWorldPosition(), game::GameManager::GetInstance().GetBombRange());
		game::GameManager::GetInstance().SpawnedBomb();
	}
}


