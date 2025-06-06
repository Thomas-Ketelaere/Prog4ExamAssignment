#pragma once
#include "GameActorCommand.h"

namespace game
{
	class ScoreComponent;
	class GainPointsCommand final : public RamCoreEngine::GameActorCommand
	{
	public:
		GainPointsCommand(RamCoreEngine::GameObject* actor);
		~GainPointsCommand() = default;
		GainPointsCommand(const GainPointsCommand& other) = delete;
		GainPointsCommand(GainPointsCommand&& other) = delete;
		GainPointsCommand& operator=(const GainPointsCommand& other) = delete;
		GainPointsCommand& operator=(GainPointsCommand&& other) = delete;

		virtual void Execute() override;

		void SetGainScore(int newGainScore) { m_GainScore = newGainScore; }
	private:
		ScoreComponent* m_pScoreComponent;
		int m_GainScore{};
	};
}


