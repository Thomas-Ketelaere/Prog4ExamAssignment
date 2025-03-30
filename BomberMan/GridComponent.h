#pragma once
#include "Component.h"
#include <vector>
#include <glm.hpp>
#include <string>

namespace dae
{
	class SpriteSheetComponent;
	class TextureComponent;
	enum class CellState
	{
		Empty, HardWall, BreakableWall
	};

	struct Cell
	{ 
		Cell(glm::vec2 position) { m_Position = position; }
		CellState m_CellState{};
		glm::vec2 m_Position{};
		SpriteSheetComponent* m_pSpriteSheetWall = nullptr;
	};

	class GridComponent final : public Component
	{
	public:
		GridComponent(GameObject* gameObject, int amountColumns, int amountRows, int screenWidth, int screenHeight, float cellSize);
		virtual ~GridComponent() override;

		void SpawnBomb(glm::vec2 position);
		void ExplodeBomb(int index, int range);

		bool IsCellWalkable(const glm::vec2& position);
		
	private:
		void SpawnExplodeTexture(const glm::vec2& position, const std::string& fullPath);
		int GetIndexFromPosition(const glm::vec2& position) const;
		glm::vec2 GetCellPositionFromIndex(const int index) const;
		int GetIndexWithCellOffset(int columnOffset, int rowOffset, int currentIndex);

		std::vector<Cell*> m_pCells;
		float m_CellWidth;
		float m_CellHeight;
		const int m_AmountColumns;
		const int m_AmountRows;
		const int m_ScreenWidth;
		const int m_ScreenHeight;

		bool m_CanSpawnBomb;
	};
}



