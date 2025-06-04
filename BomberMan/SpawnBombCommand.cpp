#include "SpawnBombCommand.h"
#include "GameObject.h"
#include "SpawnBombComponent.h"

game::SpawnBombCommand::SpawnBombCommand(RamCoreEngine::GameObject* actor):
	GameActorCommand(actor)
{
	m_pSpawnBombComponent = actor->GetComponent<SpawnBombComponent>();
}

void game::SpawnBombCommand::Start()
{
}

void game::SpawnBombCommand::Execute()
{
	m_pSpawnBombComponent->SpawnBomb(GetGameActor()->GetWorldPosition());
}


