#include "PressScreenKeyboardCommand.h"
#include "GameObject.h"
#include "OnScreenKeyboardComponent.h"

game::PressScreenKeyboardCommand::PressScreenKeyboardCommand(RamCoreEngine::GameObject* actor):
	GameActorCommand(actor)
{
	m_pKeyboardComp = actor->GetComponent<OnScreenKeyboardComponent>();
}

void game::PressScreenKeyboardCommand::Execute()
{
	m_pKeyboardComp->ButtonPressed(m_ShouldRemove);
}
