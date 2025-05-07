#include "LoseLiveCommand.h"
#include "GameObject.h"
#include "LivesComponent.h"

game::LoseLiveCommand::LoseLiveCommand(RamCoreEngine::GameObject* actor):
	GameActorCommand(actor)
{
	m_pLivesComponent = actor->GetComponent<LivesComponent>();
}

void game::LoseLiveCommand::Execute()
{
	m_pLivesComponent->LoseLive();
}
