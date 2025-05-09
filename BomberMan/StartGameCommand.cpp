#include "StartGameCommand.h"
#include "HandleUIComponent.h"
#include "GameObject.h"

game::StartGameCommand::StartGameCommand(RamCoreEngine::GameObject* actor) :
	GameActorCommand(actor)
{
	m_pHandleUIComp = actor->GetComponent<HandleUIComponent>();
}

void game::StartGameCommand::Execute()
{
	m_pHandleUIComp->ButtonPressed();
}
