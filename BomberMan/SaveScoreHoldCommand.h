#pragma once
#include "GameActorCommand.h"

namespace game
{
	class SaveScoreComponent;
	class SaveScoreHoldCommand final : public RamCoreEngine::GameActorCommand
	{
	public:
		SaveScoreHoldCommand(RamCoreEngine::GameObject* actor);
		void Execute() override;
		void Start() override {}

	private:
		SaveScoreComponent* m_pSaveScoreComponent{};
	};
}



