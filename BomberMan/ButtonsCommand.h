#pragma once
#include "GameActorCommand.h"

namespace game
{
	class ButtonsComponent;
	class ButtonsCommand : public RamCoreEngine::GameActorCommand
	{
	public:
		ButtonsCommand(RamCoreEngine::GameObject* actor);
		
		void Start() override {};
		void Execute() override;

		void SetGoesDown(bool goesDown) { m_GoesDown = goesDown; }

	private:
		ButtonsComponent* m_pButtonsComp{};
		//going down is increasing idx
		bool m_GoesDown{};
	};
}


