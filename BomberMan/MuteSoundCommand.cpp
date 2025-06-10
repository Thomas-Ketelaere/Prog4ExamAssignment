#include "MuteSoundCommand.h"
#include "ServiceLocator.h"

game::MuteSoundCommand::MuteSoundCommand():
	Command()
{
}

void game::MuteSoundCommand::Execute()
{
	RamCoreEngine::ServiceLocator::GetSoundSystem().Mute();
}
