#include "SpawnBombCommand.h"
#include "GridComponent.h"
#include "GameObject.h"

dae::SpawnBombCommand::SpawnBombCommand(GameObject* actor):
	GameActorCommand(actor)
{
	m_pGridComponent = actor->GetParent()->GetComponent<GridComponent>();
}

void dae::SpawnBombCommand::Execute()
{
	m_pGridComponent->SpawnBomb(GetGameActor()->GetWorldPosition());
}
