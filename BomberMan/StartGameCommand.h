#pragma once
#include "GameActorCommand.h"
namespace game
{
	class HandleUIComponent;
	class StartGameCommand : public RamCoreEngine::GameActorCommand
	{
	public:
		StartGameCommand(RamCoreEngine::GameObject* actor);
		void Execute() override;

		void Start() override {}

	private:
		HandleUIComponent* m_pHandleUIComp{};
	};
}


