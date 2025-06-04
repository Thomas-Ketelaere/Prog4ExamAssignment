#include "ReturnToStartCommand.h"
#include "SceneManager.h"

game::ReturnToStartCommand::ReturnToStartCommand():
	Command()
{
}

void game::ReturnToStartCommand::Execute()
{
	RamCoreEngine::SceneManager::GetInstance().LoadScene("Start");
}
