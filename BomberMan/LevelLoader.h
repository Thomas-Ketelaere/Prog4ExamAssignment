#pragma once
#include "Singleton.h"
#include <vector>
#include <glm.hpp>
#include <string>

namespace game
{
	class LevelLoader : public RamCoreEngine::Singleton<LevelLoader>
	{
	public:
		void ReadFile(const std::string& fileName);

		const std::vector<std::pair<glm::vec2, int>>& GetEnemies() { return m_Enemies; }
		const std::vector<int>& GetHardWallIndices() { return m_HardWallIndices; }
		const std::vector<int>& GetPickUpIndices() { return m_PickUpIndices; }
		int GetAmountBreakableWalls() { return m_AmountBreakableWalls; }

	private:
		friend class Singleton<LevelLoader>;

		std::vector<std::pair<glm::vec2, int>> m_Enemies;
		std::vector<int> m_HardWallIndices;
		std::vector<int> m_PickUpIndices;
		int m_AmountBreakableWalls{};
	};
}


