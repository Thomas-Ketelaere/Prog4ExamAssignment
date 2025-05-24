#include "GameManager.h"
#include "SceneManager.h"
#include "Hash.h"
#include <iostream>

void game::GameManager::LoseLive()
{
	--m_TotalLives;
	//TODO: check if it is < 0 or not
	if (m_TotalLives <= -1)
	{
		RamCoreEngine::SceneManager::GetInstance().LoadScene("EndScreen");
	}
	else
	{
		RamCoreEngine::SceneManager::GetInstance().LoadScene("LoadingScreen");
	}
	
}

void game::GameManager::ResetStats()
{
	m_TotalLives = m_MaxLives;
	m_CurrentAmountBombs = 0;
	m_MaxBombs = 1;
	m_CurrentLevel = 1;
	m_BombRange = 1;
	m_Name = " ";
}

void game::GameManager::NewLevelLoaded()
{
	m_CurrentAmountBombs = 0; //if bomb was still on grid while level change, it wouldn't reset
}

void game::GameManager::AdvanceLevel()
{
	++m_CurrentLevel;
	//TODO: check if it is max level or not, if so => endscreen with high score
	if (m_CurrentLevel >= m_MaxLevels)
	{
		RamCoreEngine::SceneManager::GetInstance().LoadScene("EndScreen");
	}
	else
	{
		RamCoreEngine::SceneManager::GetInstance().LoadScene("LoadingScreen");
	}
}

void game::GameManager::AddLetterToName(char letter)
{
	m_Name += letter;
}

void game::GameManager::RemoveLetterFromName()
{
	if (m_Name.size() >1) //first letter should be space, otherwise error name empty
	{
		m_Name.pop_back();
	}

	if (m_Name.size() == 1) //first letter should be space, otherwise error name empty
	{
		m_Name = " ";
	}
}

void game::GameManager::EnemyKilled()
{
	--m_AmountEnemies;
	std::cout << "amount enemies left: " << m_AmountEnemies << std::endl;
}
