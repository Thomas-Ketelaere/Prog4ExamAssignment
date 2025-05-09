#include "HandleUICommand.h"
#include "GameObject.h"
#include "HandleUIComponent.h"

game::HandleUICommand::HandleUICommand(RamCoreEngine::GameObject* actor):
	GameActorCommand(actor)
{
	m_pHandleUIComp = actor->GetComponent<HandleUIComponent>();
}

void game::HandleUICommand::Start()
{
	
}

void game::HandleUICommand::Execute()
{
	m_pHandleUIComp->ChangeIndex(m_GoesDown);
}
