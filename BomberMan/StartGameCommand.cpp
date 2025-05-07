#include "StartGameCommand.h"
#include "SceneManager.h"

game::StartGameCommand::StartGameCommand(RamCoreEngine::GameObject* actor) :
	GameActorCommand(actor)
{
}

void game::StartGameCommand::Execute()
{
	RamCoreEngine::SceneManager::GetInstance().LoadScene("Game");
}
