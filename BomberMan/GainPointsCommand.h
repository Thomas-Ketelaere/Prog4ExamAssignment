#pragma once
#include "GameActorCommand.h"

namespace game
{
	class ScoreComponent;
	class GainPointsCommand : public RamCoreEngine::GameActorCommand
	{
	public:
		GainPointsCommand(RamCoreEngine::GameObject* actor);
		virtual void Execute() override;
		void Start() override {}

		void SetGainScore(int newGainScore) { m_GainScore = newGainScore; }
	private:
		ScoreComponent* m_pScoreComponent;
		int m_GainScore{};
	};
}


