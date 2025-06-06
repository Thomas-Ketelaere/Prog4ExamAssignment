#pragma once
#include "Command.h"

namespace game
{
	class ReturnToStartCommand final : public RamCoreEngine::Command
	{
	public:
		ReturnToStartCommand();
		~ReturnToStartCommand() = default;
		ReturnToStartCommand(const ReturnToStartCommand& other) = delete;
		ReturnToStartCommand(ReturnToStartCommand&& other) = delete;
		ReturnToStartCommand& operator=(const ReturnToStartCommand& other) = delete;
		ReturnToStartCommand& operator=(ReturnToStartCommand&& other) = delete;

		void Execute() override;
	};
}


