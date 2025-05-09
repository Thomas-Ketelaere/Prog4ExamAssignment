#pragma once
#include "GameActorCommand.h"
#include <vector>

namespace game
{
	class HandleUIComponent;
	class HandleUICommand : public RamCoreEngine::GameActorCommand
	{
	public:
		HandleUICommand(RamCoreEngine::GameObject* actor);
		
		void Start() override;
		void Execute() override;

		void SetGoesDown(bool goesDown) { m_GoesDown = goesDown; }

	private:
		HandleUIComponent* m_pHandleUIComp{};
		//going down is increasing idx
		bool m_GoesDown{};
	};
}


