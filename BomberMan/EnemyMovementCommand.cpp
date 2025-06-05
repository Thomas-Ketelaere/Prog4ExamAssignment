#include "EnemyMovementCommand.h"
#include "EnemyMovementComponent.h"
#include "GameObject.h"

game::EnemyMovementCommand::EnemyMovementCommand(RamCoreEngine::GameObject* actor):
	GameActorCommand(actor)
{
	m_pEnemyMovementComp = actor->GetComponent<EnemyMovementComponent>();
}

void game::EnemyMovementCommand::Execute()
{
	m_pEnemyMovementComp->ControlledMove(m_Direction);
}
