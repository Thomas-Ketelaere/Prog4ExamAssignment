#pragma once
#include "GameActorCommand.h"
namespace game
{
	class StartGameCommand : public RamCoreEngine::GameActorCommand
	{
	public:
		StartGameCommand(RamCoreEngine::GameObject* actor);
		virtual void Execute() override;

		void Start() override {}
	};
}


