#pragma once
#include "Command.h"

namespace game
{
	class SkipLevelCommand final : public RamCoreEngine::Command
	{
	public:
		SkipLevelCommand();
		~SkipLevelCommand() = default;
		SkipLevelCommand(const SkipLevelCommand& other) = delete;
		SkipLevelCommand(SkipLevelCommand&& other) = delete;
		SkipLevelCommand& operator=(const SkipLevelCommand& other) = delete;
		SkipLevelCommand& operator=(SkipLevelCommand&& other) = delete;

		void Execute() override;
	};
}

