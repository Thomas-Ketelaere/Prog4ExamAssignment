#pragma once
#include "GameActorCommand.h"
namespace game
{
	class ButtonsComponent;
	class StartGameCommand final : public RamCoreEngine::GameActorCommand
	{
	public:
		StartGameCommand(RamCoreEngine::GameObject* actor);
		~StartGameCommand() = default;
		StartGameCommand(const StartGameCommand& other) = delete;
		StartGameCommand(StartGameCommand&& other) = delete;
		StartGameCommand& operator=(const StartGameCommand& other) = delete;
		StartGameCommand& operator=(StartGameCommand&& other) = delete;

		void Execute() override;

	private:
		ButtonsComponent* m_pButtonComp{};
	};
}


