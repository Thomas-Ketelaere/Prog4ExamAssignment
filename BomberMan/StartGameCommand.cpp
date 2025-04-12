#include "StartGameCommand.h"
#include "SceneManager.h"

dae::StartGameCommand::StartGameCommand(GameObject* actor) :
	GameActorCommand(actor)
{
}

void dae::StartGameCommand::Execute()
{
	SceneManager::GetInstance().LoadScene("Game");
}
