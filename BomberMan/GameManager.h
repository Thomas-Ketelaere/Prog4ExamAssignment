#pragma once
#include "Singleton.h"
#include "string"

namespace game
{
	enum class GameMode
	{
		Single, Coop, Versus
	};
	// TODO IF TIME LEFT: (change these into events)
	// - check if possible count enemies in Grid? Or enemy counter component with event (that already exists) when enemy dies, put game object on grid to check in grid component if enemies are stil alive
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
		const int GetTotalScore() const { return m_TotalScore; }

		//Enemies
		void EnemyKilled();
		void SetAmountEnemies(int amount) { m_AmountEnemies = amount; }

		//Bomb
		bool RemoteExplodeActive() const { return m_RemoteExplode; }
		int GetBombRange() const  { return m_BombRange; }
		int GetMaxBombs() const  { return m_MaxBombs; }
		void SaveBombRange(int newRange) { m_BombRange = newRange; }
		void SaveRemoteExplode(bool remoteExplode) { m_RemoteExplode = remoteExplode; }
		void SaveMaxBombs(int newMaxBombs) { m_MaxBombs = newMaxBombs; }
		
		//Level
		const int GetCurrentLevel() const { return m_CurrentLevel; }
		bool CanPlayerExit() const { return m_AmountEnemies == 0; }
		void AdvanceLevel();

		//End
		void ClearName() { m_Name = ""; }
		void AddLetterToName(char letter);
		void RemoveLetterFromName();
		const std::string& GetName() { return m_Name; }

		//Game mode
		GameMode GetGameMode() const { return m_CurrentGameMode; }
		void SetGameMode(GameMode newGameMode) { m_CurrentGameMode = newGameMode; }

		//Controller rumble
		void SetControllerRumble(float percentLeft, float percentRight); //doing it in game manager to check amount of controllers need to be set as rumble (so no need to keep checking game mode in other classes)

	private:
		friend class Singleton<GameManager>;
		GameMode m_CurrentGameMode{};
		std::string m_Name{" "};
		int m_TotalLives{};
		int m_MaxLives{};
		int m_TotalScore{};
		int m_CurrentLevel{ 1 };
		int m_MaxBombs{ 1 };
		int m_AmountEnemies{};
		const int m_MaxLevels{ 3 }; 
		const size_t m_MaxLetters{ 10 };
		int m_BombRange{ 1 };
		bool m_RemoteExplode{};
	};

}
