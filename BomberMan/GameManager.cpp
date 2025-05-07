#include "GameManager.h"
#include "SceneManager.h"

void game::GameManager::LoseLive()
{
	--m_TotalLives;
	//TODO: check if it is < 0 or not
	RamCoreEngine::SceneManager::GetInstance().ReloadScene();
}
