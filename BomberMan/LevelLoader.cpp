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

    int numEnemies{};
    inFile >> numEnemies;
    m_Enemies.resize(numEnemies);
    for (int i = 0; i < numEnemies; ++i)
    {
        inFile >> m_Enemies[i].first.x >> m_Enemies[i].first.y;
        inFile >> m_Enemies[i].second;
    }

    int numHardWalls{};
    inFile >> numHardWalls;
    m_HardWallIndices.resize(numHardWalls);
    for (int i = 0; i < numHardWalls; ++i)
    {
        inFile >> m_HardWallIndices[i];
    }

    inFile >> m_AmountBreakableWalls;

    inFile.close();
}
