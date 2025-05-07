#pragma once
#include "Singleton.h"

namespace game
{
	class GameManager : public RamCoreEngine::Singleton<GameManager>
	{
	public:
		void GainScore(int scoreAdd) { m_TotalScore += scoreAdd; }
		void LoseLive();

		void SetLives(int lives) { m_TotalLives = lives; }

		const int GetTotalLives() { return m_TotalLives; }
		const int GetTotalScore() { return m_TotalScore; }

	private:
		friend class Singleton<GameManager>;

		int m_TotalLives{};
		int m_TotalScore{};
	};

}
