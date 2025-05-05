#pragma once
#include "GameActorCommand.h"
namespace dae
{
	class StartGameCommand : public GameActorCommand
	{
	public:
		StartGameCommand(GameObject* actor);
		virtual void Execute() override;

		void Start() override {}
	};
}


