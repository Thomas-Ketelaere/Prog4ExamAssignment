#include "OnScreenKeyboardCommand.h"
#include "GameObject.h"
#include "OnScreenKeyboardComponent.h"

game::OnScreenKeyboardCommand::OnScreenKeyboardCommand(RamCoreEngine::GameObject* actor) :
	GameActorCommand(actor)
{
	m_pKeyboardComp = actor->GetComponent<OnScreenKeyboardComponent>();
}

void game::OnScreenKeyboardCommand::Execute()
{
	m_pKeyboardComp->ChangeSelected(m_Direction);
}
