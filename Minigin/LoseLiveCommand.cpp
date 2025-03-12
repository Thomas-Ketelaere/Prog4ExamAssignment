#include "LoseLiveCommand.h"
#include "GameObject.h"
#include "LivesComponent.h"

dae::LoseLiveCommand::LoseLiveCommand(GameObject* actor):
	GameActorCommand(actor)
{
	m_pLivesComponent = actor->GetComponent<LivesComponent>();
}

void dae::LoseLiveCommand::Execute()
{
	m_pLivesComponent->LoseLive();
}
