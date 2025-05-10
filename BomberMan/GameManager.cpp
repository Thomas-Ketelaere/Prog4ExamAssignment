#include "GameManager.h"
#include "SceneManager.h"
#include "Hash.h"
#include <iostream>

void game::GameManager::LoseLive()
{
	--m_TotalLives;
	//TODO: check if it is < 0 or not
	RamCoreEngine::SceneManager::GetInstance().LoadScene("LoadingScreen");
}

void game::GameManager::ResetStats()
{
	m_TotalLives = m_MaxLives;
	m_CurrentAmountBombs = 0;
	m_MaxBombs = 1;
}

void game::GameManager::CountEnemies()
{
	m_AmountEnemies = (int)RamCoreEngine::SceneManager::GetInstance().GetCurrentScene()->GetAllObjectsWithTag(make_sdbm_hash("Enemy")).size();
	std::cout << "amount enemies: " << m_AmountEnemies << std::endl;
}

void game::GameManager::NewLevelLoaded()
{
	m_CurrentAmountBombs = 0; //if bomb was still on grid while level change, it wouldn't reset
}

void game::GameManager::AdvanceLevel()
{
	++m_CurrentLevel;
	//TODO: check if it is max level or not, if so => endscreen with high score
	RamCoreEngine::SceneManager::GetInstance().LoadScene("LoadingScreen");
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
