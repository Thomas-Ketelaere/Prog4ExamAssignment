#pragma once
#include "GameActorCommand.h"

namespace game
{
	class SaveScoreComponent;
	class SaveScoreReleaseCommand final : public RamCoreEngine::GameActorCommand
	{
	public:
		SaveScoreReleaseCommand(RamCoreEngine::GameObject* actor);
		~SaveScoreReleaseCommand() = default;
		SaveScoreReleaseCommand(const SaveScoreReleaseCommand& other) = delete;
		SaveScoreReleaseCommand(SaveScoreReleaseCommand&& other) = delete;
		SaveScoreReleaseCommand& operator=(const SaveScoreReleaseCommand& other) = delete;
		SaveScoreReleaseCommand& operator=(SaveScoreReleaseCommand&& other) = delete;

		void Execute() override;

	private:
		SaveScoreComponent* m_pSaveScoreComponent{};
	};
}

