#pragma once
#include "GameActorCommand.h"

namespace game
{
	class SaveScoreComponent;
	class SaveScoreReleaseCommand final : public RamCoreEngine::GameActorCommand
	{
	public:
		SaveScoreReleaseCommand(RamCoreEngine::GameObject* actor);
		void Execute() override;
		void Start() override {}

	private:
		SaveScoreComponent* m_pSaveScoreComponent{};
	};
}

