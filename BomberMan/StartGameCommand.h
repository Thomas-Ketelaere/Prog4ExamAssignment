#pragma once
#include "GameActorCommand.h"
namespace game
{
	class ButtonsComponent;
	class StartGameCommand : public RamCoreEngine::GameActorCommand
	{
	public:
		StartGameCommand(RamCoreEngine::GameObject* actor);
		void Execute() override;

		void Start() override {}

	private:
		ButtonsComponent* m_pButtonComp{};
	};
}


