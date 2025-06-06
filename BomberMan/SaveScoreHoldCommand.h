#pragma once
#include "GameActorCommand.h"

namespace game
{
	class SaveScoreComponent;
	class SaveScoreHoldCommand final : public RamCoreEngine::GameActorCommand
	{
	public:
		SaveScoreHoldCommand(RamCoreEngine::GameObject* actor);
		~SaveScoreHoldCommand() = default;
		SaveScoreHoldCommand(const SaveScoreHoldCommand& other) = delete;
		SaveScoreHoldCommand(SaveScoreHoldCommand&& other) = delete;
		SaveScoreHoldCommand& operator=(const SaveScoreHoldCommand& other) = delete;
		SaveScoreHoldCommand& operator=(SaveScoreHoldCommand&& other) = delete;

		void Execute() override;

	private:
		SaveScoreComponent* m_pSaveScoreComponent{};
	};
}



