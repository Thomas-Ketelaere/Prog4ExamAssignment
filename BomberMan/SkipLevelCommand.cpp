#include "SkipLevelCommand.h"
#include "GameManager.h"

game::SkipLevelCommand::SkipLevelCommand():
	Command()
{
}

void game::SkipLevelCommand::Execute()
{
	game::GameManager::GetInstance().AdvanceLevel();
}
