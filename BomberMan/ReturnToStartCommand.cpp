#include "ReturnToStartCommand.h"
#include "SceneManager.h"
#include <Hash.h>

game::ReturnToStartCommand::ReturnToStartCommand():
	Command()
{
}

void game::ReturnToStartCommand::Execute()
{
	RamCoreEngine::SceneManager::GetInstance().LoadScene(make_sdbm_hash("Start"));
}
