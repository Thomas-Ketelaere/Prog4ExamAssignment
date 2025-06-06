#pragma once
#include "GameActorCommand.h"

namespace game
{
	class ButtonsComponent;
	class ButtonsCommand final : public RamCoreEngine::GameActorCommand
	{
	public:
		ButtonsCommand(RamCoreEngine::GameObject* actor);
		~ButtonsCommand() = default;
		ButtonsCommand(const ButtonsCommand& other) = delete;
		ButtonsCommand(ButtonsCommand&& other) = delete;
		ButtonsCommand& operator=(const ButtonsCommand& other) = delete;
		ButtonsCommand& operator=(ButtonsCommand&& other) = delete;
		
		void Execute() override;

		void SetGoesDown(bool goesDown) { m_GoesDown = goesDown; }

	private:
		ButtonsComponent* m_pButtonsComp{};
		//going down is increasing idx
		bool m_GoesDown{};
	};
}


