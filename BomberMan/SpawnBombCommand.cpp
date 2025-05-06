#include "SpawnBombCommand.h"
#include "GridComponent.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Hash.h"

dae::SpawnBombCommand::SpawnBombCommand(GameObject* actor):
	GameActorCommand(actor)
{
	
}

void dae::SpawnBombCommand::Execute()
{
	m_pGridComponent->SpawnBomb(GetGameActor()->GetWorldPosition());
}

void dae::SpawnBombCommand::Start()
{
	GameObject* gridObject = SceneManager::GetInstance().GetCurrentScene()->GetFirstObjectWithTag(make_sdbm_hash("Grid"));
	m_pGridComponent = gridObject->GetComponent<GridComponent>();
}
