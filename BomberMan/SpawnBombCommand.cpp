#include "SpawnBombCommand.h"
#include "GridComponent.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Hash.h"

game::SpawnBombCommand::SpawnBombCommand(RamCoreEngine::GameObject* actor):
	GameActorCommand(actor)
{
	
}

void game::SpawnBombCommand::Execute()
{
	m_pGridComponent->SpawnBomb(GetGameActor()->GetWorldPosition());
}

void game::SpawnBombCommand::Start()
{
	RamCoreEngine::GameObject* gridObject = RamCoreEngine::SceneManager::GetInstance().GetCurrentScene()->GetFirstObjectWithTag(make_sdbm_hash("Grid"));
	m_pGridComponent = gridObject->GetComponent<GridComponent>();
}
