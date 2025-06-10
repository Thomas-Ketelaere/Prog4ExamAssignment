#pragma once
#include "Command.h"

namespace game
{
	class MuteSoundCommand final : public RamCoreEngine::Command
	{
	public:
		MuteSoundCommand();
		~MuteSoundCommand() = default;
		MuteSoundCommand(const MuteSoundCommand& other) = delete;
		MuteSoundCommand(MuteSoundCommand&& other) = delete;
		MuteSoundCommand& operator=(const MuteSoundCommand& other) = delete;
		MuteSoundCommand& operator=(MuteSoundCommand&& other) = delete;

		void Execute() override;
	};
}

