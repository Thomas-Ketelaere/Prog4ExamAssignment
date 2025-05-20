#include "SaveScoreHoldCommand.h"
#include "GameObject.h"
#include "SaveScoreComponent.h"

game::SaveScoreHoldCommand::SaveScoreHoldCommand(RamCoreEngine::GameObject* actor):
	GameActorCommand(actor)
{
	m_pSaveScoreComponent = actor->GetComponent<SaveScoreComponent>();
}

void game::SaveScoreHoldCommand::Execute()
{
	m_pSaveScoreComponent->IncreaseBar();
}
