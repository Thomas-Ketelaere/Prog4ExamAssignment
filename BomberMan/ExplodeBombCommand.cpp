#include "ExplodeBombCommand.h"
#include "SpawnBombComponent.h"
#include "GameObject.h"

game::ExplodeBombCommand::ExplodeBombCommand(RamCoreEngine::GameObject* actor):
	GameActorCommand(actor)
{
	m_pSpawnBombComponent = actor->GetComponent<SpawnBombComponent>();
}

void game::ExplodeBombCommand::Start()
{
}

void game::ExplodeBombCommand::Execute()
{
	m_pSpawnBombComponent->RemoteExplodeBomb();
}
