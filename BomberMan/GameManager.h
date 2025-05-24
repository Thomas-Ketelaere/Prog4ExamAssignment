#pragma once
#include "Singleton.h"
#include "string"

namespace game
{
	//IF TIME LEFT: (change these into events)
	// - check if possible count enemies in Grid?
	// - check if possible Lose Live in live component for both players?
	// - check if possible do bombs spawning different (same with range)
	class GameManager : public RamCoreEngine::Singleton<GameManager>
	{
	public:
		void ResetStats();

		//Lives
		void LoseLive();
		void SetMaxLives(int lives) { m_MaxLives = lives; m_TotalLives = m_MaxLives; }
		int GetTotalLives() const { return m_TotalLives; }

		//Score
		void GainScore(int scoreAdd) { m_TotalScore += scoreAdd; }
		const int GetTotalScore() { return m_TotalScore; }

		//Enemies
		void EnemyKilled();
		void SetAmountEnemies(int amount) { m_AmountEnemies = amount; }

		//Bomb
		bool CanSpawnBomb() { return m_CurrentAmountBombs < m_MaxBombs; }
		int GetBombRange() { return m_BombRange; }
		void SpawnedBomb() { ++m_CurrentAmountBombs; }
		void BombExploded() { --m_CurrentAmountBombs; }
		void ExtraBombPU() { ++m_MaxBombs; }
		void FlamesPU() { ++m_BombRange; }
		
		//Level
		const int GetCurrentLevel() { return m_CurrentLevel; }
		void NewLevelLoaded();
		bool CanPlayerExit() { return m_AmountEnemies == 0; }
		void AdvanceLevel();

		//End
		void ClearName() { m_Name = ""; }
		void AddLetterToName(char letter);
		void RemoveLetterFromName();
		const std::string& GetName() { return m_Name; }

	private:
		friend class Singleton<GameManager>;

		std::string m_Name{" "};
		int m_TotalLives{};
		int m_MaxLives{};
		int m_TotalScore{};
		int m_CurrentLevel{ 1 };
		int m_CurrentAmountBombs{};
		int m_MaxBombs{ 1 };
		int m_AmountEnemies{};
		const int m_MaxLevels{ 1 }; //should be three but for testing one now
		int m_BombRange{ 1 };
	};

}
