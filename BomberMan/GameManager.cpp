#include "GameManager.h"
#include "SceneManager.h"
#include "Hash.h"
#include <iostream>

void game::GameManager::LoseLive()
{
	--m_TotalLives;
	m_RemoteExplode = false; //when losing live, only this ability gets removed
	if (m_TotalLives <= -1)
	{
		RamCoreEngine::SceneManager::GetInstance().LoadScene(make_sdbm_hash("EndScreen"));
	}
	else
	{
		RamCoreEngine::SceneManager::GetInstance().LoadScene(make_sdbm_hash("LoadingScreen"));
	}
	
}

void game::GameManager::ResetStats()
{
	m_TotalLives = m_MaxLives;
	m_MaxBombs = 1;
	m_CurrentLevel = 1;
	m_BombRange = 1;
	m_Name = " ";
	m_TotalScore = 0;
	m_RemoteExplode = false;
}


void game::GameManager::AdvanceLevel()
{
	++m_CurrentLevel;
	if (m_CurrentLevel >= m_MaxLevels)
	{
		RamCoreEngine::SceneManager::GetInstance().LoadScene(make_sdbm_hash("EndScreen"));
	}
	else
	{
		++m_TotalLives; //gain live after winning level
		RamCoreEngine::SceneManager::GetInstance().LoadScene(make_sdbm_hash("LoadingScreen"));
	}
}

void game::GameManager::AddLetterToName(char letter)
{
	m_Name += letter;
}

void game::GameManager::RemoveLetterFromName()
{
	if (m_Name.size() >1)
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
