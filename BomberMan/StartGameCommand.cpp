#include "StartGameCommand.h"
#include "ButtonsComponent.h"
#include "GameObject.h"

game::StartGameCommand::StartGameCommand(RamCoreEngine::GameObject* actor) :
	GameActorCommand(actor)
{
	m_pButtonComp = actor->GetComponent<ButtonsComponent>();
}

void game::StartGameCommand::Execute()
{
	m_pButtonComp->ButtonPressed();
}
