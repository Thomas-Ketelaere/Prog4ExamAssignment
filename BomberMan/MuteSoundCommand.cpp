#include "MuteSoundCommand.h"
#include "ServiceLocator.h"

game::MuteSoundCommand::MuteSoundCommand():
	Command()
{
}

void game::MuteSoundCommand::Execute()
{
	m_Muted = !m_Muted;
	if (m_Muted)
	{
		RamCoreEngine::ServiceLocator::GetSoundSystem().Mute();
	}
	else
	{
		RamCoreEngine::ServiceLocator::GetSoundSystem().Unmute();
	}
}
