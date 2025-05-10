#include "ButtonsCommand.h"
#include "GameObject.h"
#include "ButtonsComponent.h"

game::ButtonsCommand::ButtonsCommand(RamCoreEngine::GameObject* actor):
	GameActorCommand(actor)
{
	m_pButtonsComp = actor->GetComponent<ButtonsComponent>();
}

void game::ButtonsCommand::Execute()
{
	m_pButtonsComp->ChangeIndex(m_GoesDown);
}
