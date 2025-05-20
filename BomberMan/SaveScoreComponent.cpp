#include "SaveScoreComponent.h"
#include "Timer.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include <fstream>
#include <iostream>
#include <map>
#include "GameManager.h"
#include "SceneManager.h"
#include <algorithm>

game::SaveScoreComponent::SaveScoreComponent(RamCoreEngine::GameObject* gameObject, float lengthBar, float heightBar, float speed, const std::string& saveFileName):
	RamCoreEngine::Component(gameObject),
	m_Speed{speed},
	m_LengthBar{lengthBar},
	m_HeightBar{heightBar},
	m_SaveFileName{saveFileName}
{
}

void game::SaveScoreComponent::Render() const
{
	glm::vec3 pos = GetTransform()->GetWorldPosition();
	SDL_Color color{ 255, 255, 255, 255 };
	RamCoreEngine::Renderer::GetInstance().DrawRectangle(pos.x, pos.y, m_LengthBar, m_HeightBar, color);
	RamCoreEngine::Renderer::GetInstance().FillRectangle(pos.x, pos.y, m_CurrentPercent * m_LengthBar / 100.f, m_HeightBar, color); //is percent so divide by 100
}

void game::SaveScoreComponent::IncreaseBar()
{
	m_CurrentPercent += m_Speed * RamCoreEngine::Time::GetInstance().m_DeltaTime;
	if (m_CurrentPercent >= 100.f)
	{
		//write and go back to main screen
		SaveScore();
	}
}

void game::SaveScoreComponent::SaveScore()
{
	std::ifstream inFile(m_SaveFileName);
	std::vector<std::pair<int, std::string>> playersInfo{};
	if (inFile) //if file doesnt exist, still have to continue to write it
	{
		while (!inFile.eof())
		{
			int playerScore{};
			std::string infoScore{};
			std::string playerName{};
			std::getline(inFile, infoScore);
			std::getline(inFile, playerName);
			playerScore = std::stoi(infoScore);
			playersInfo.emplace_back(std::make_pair(playerScore, playerName));
		}
		inFile.close();
	}

	int newPlayerScore = game::GameManager::GetInstance().GetTotalScore();
	std::string newPlayerName = game::GameManager::GetInstance().GetName();
	playersInfo.emplace_back(std::make_pair(newPlayerScore, newPlayerName));

	std::sort(playersInfo.begin(), playersInfo.end(), [](std::pair<int, std::string>& playerOneInfo, std::pair<int, std::string>& playerTwoInfo)
		{
			return playerOneInfo.first > playerTwoInfo.first;
		});

	if (playersInfo.size() >= m_MaxPlayersInFile)
	{
		playersInfo.pop_back(); //will never be able to succeed 5, so just removing last one
	}

	std::ofstream outFile(m_SaveFileName);
	if (outFile.is_open())
	{
		bool firstPlayer{true};
		for (std::pair<int, std::string> playerInfo : playersInfo)
		{
			if (!firstPlayer)
			{
				outFile << "\n"; //doing an extra line here, otherwise would add extra (empty) line at end and would give error in reading since it's empty
			}
			firstPlayer = false;
			outFile << playerInfo.first << "\n"; //score
			outFile << playerInfo.second; //name
		}
	}

	RamCoreEngine::SceneManager::GetInstance().LoadScene("Start"); 
}
