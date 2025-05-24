#include "LevelLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>

void game::LevelLoader::ReadFile(const std::string& fileName)
{
    m_Enemies.clear();
    m_HardWallIndices.clear();
    m_AmountBreakableWalls = 0;

    std::ifstream inFile(fileName); 
    if (!inFile)
    {
        std::cout << "failed to open file" << std::endl;
        return;
    }

    std::string numEnemies{};
    std::getline(inFile, numEnemies);
    m_Enemies.resize(std::stoi(numEnemies));
    for (int i = 0; i < std::stoi(numEnemies); ++i)
    {
        glm::vec2 enemyPos{};
        std::string enemyX{};
        std::string enemyY{};
        std::getline(inFile, enemyX);
        std::getline(inFile, enemyY);

        enemyPos.x = std::stof(enemyX);
        enemyPos.y = std::stof(enemyY);

        std::string enemyIndex{};
        std::getline(inFile, enemyIndex);
        m_Enemies[i].first = enemyPos;
        m_Enemies[i].second = std::stoi(enemyIndex);
    }

    std::string numHardWalls{};
    std::getline(inFile, numHardWalls);
    m_HardWallIndices.resize(std::stoi(numHardWalls));
    for (int i = 0; i < std::stoi(numHardWalls); ++i)
    {
        std::string index{};
        std::getline(inFile, index);
        m_HardWallIndices[i] = std::stoi(index);
    }

    std::string amountBreakableWalls;
    std::getline(inFile, amountBreakableWalls);
    m_AmountBreakableWalls = std::stoi(amountBreakableWalls);

    std::string numPickUps{};
    std::getline(inFile, numPickUps);
    m_PickUpIndices.resize(std::stoi(numPickUps));
    for (int i = 0; i < std::stoi(numPickUps); ++i)
    {
        std::string index{};
        std::getline(inFile, index);
        m_PickUpIndices[i] = std::stoi(index);
    }

    inFile.close();
}
