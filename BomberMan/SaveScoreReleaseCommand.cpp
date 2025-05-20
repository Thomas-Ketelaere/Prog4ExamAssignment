#include "SaveScoreReleaseCommand.h"
#include "GameObject.h"
#include "SaveScoreComponent.h"

game::SaveScoreReleaseCommand::SaveScoreReleaseCommand(RamCoreEngine::GameObject* actor):
	GameActorCommand(actor)
{
	m_pSaveScoreComponent = actor->GetComponent<SaveScoreComponent>();
}

void game::SaveScoreReleaseCommand::Execute()
{
	m_pSaveScoreComponent->ResetBar();
}
