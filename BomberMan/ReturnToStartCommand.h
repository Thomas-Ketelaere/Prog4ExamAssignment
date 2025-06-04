#pragma once
#include "Command.h"

namespace game
{
	class ReturnToStartCommand : public RamCoreEngine::Command
	{
	public:
		ReturnToStartCommand();
		void Execute() override;

		void Start() override {};
	};
}


