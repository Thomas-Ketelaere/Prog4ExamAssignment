#pragma once
#include "GameActorCommand.h"

namespace dae
{
	class ScoreComponent;
	class GainPointsCommand : public GameActorCommand
	{
	public:
		GainPointsCommand(GameObject* actor);
		virtual void Execute() override;
		void Start() override {}

		void SetGainScore(int newGainScore) { m_GainScore = newGainScore; }
	private:
		ScoreComponent* m_pScoreComponent;
		int m_GainScore{};
	};
}


