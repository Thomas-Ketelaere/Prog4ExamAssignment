#include "HighScoresTextComponent.h"
#include "TextComponent.h"
#include <fstream>
#include <iostream>
#include "GameManager.h"
#include <algorithm>
#include "ResourceManager.h"
#include "GameObject.h"

game::HighScoresTextComponent::HighScoresTextComponent(RamCoreEngine::GameObject* gameObject, const std::string& saveFileName, float offsetYBetween):
	Component(gameObject)
{
	std::ifstream inFile(saveFileName);
	std::vector<std::pair<int, std::string>> playersInfo{};
	if (inFile)
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

	std::sort(playersInfo.begin(), playersInfo.end(), [](std::pair<int, std::string>& playerOneInfo, std::pair<int, std::string>& playerTwoInfo)
		{
			return playerOneInfo.first > playerTwoInfo.first;
		});

	auto font = RamCoreEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto highScoreText = std::make_unique<RamCoreEngine::TextComponent>(gameObject, "HighScores", font, true);
	highScoreText->SetCustomPosition(glm::vec2(0, -offsetYBetween * 2));
	highScoreText->ChangeFontSize(40);
	gameObject->AddComponent(std::move(highScoreText));

	for (size_t playerIndex{}; playerIndex < playersInfo.size(); ++playerIndex)
	{
		auto& playerInfo = playersInfo[playerIndex];
		std::string nameAndScore = playerInfo.second + ": " + std::to_string(playerInfo.first);
		auto playerText = std::make_unique<RamCoreEngine::TextComponent>(gameObject, nameAndScore, font, true);
		playerText->SetCustomPosition(glm::vec2(0, offsetYBetween * playerIndex));
		gameObject->AddComponent(std::move(playerText));
	}
}
