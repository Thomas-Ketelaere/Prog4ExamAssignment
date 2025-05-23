#pragma once
#include "Component.h"
#include <vector>
#include <glm.hpp>
#include <string>

namespace RamCoreEngine
{
	class SpriteSheetComponent;
}

namespace game
{
	class BombComponent;
	enum class CellState
	{
		Empty, HardWall, BreakableWall
	};

	// PU = power up
	enum class CellItem
	{
		Empty, Exit, ExtraBombPU, DetonatorPU, FlamesPU
	};

	struct Cell
	{ 
		Cell(glm::vec2 position) { m_Position = position; }
		CellState m_CellState{};
		CellItem m_CellItem{CellItem::Empty};
		glm::vec2 m_Position{};
		BombComponent* m_pBombComponent = nullptr;
		RamCoreEngine::SpriteSheetComponent* m_pSpriteSheetWall = nullptr;
	};

	struct Node
	{
		int index = -1;
		int connectionIndex = -1;
		float estimatedTotalCost = 0.f;
		float costSoFar = 0.f;

		bool operator<(const Node& other) const
		{
			return estimatedTotalCost < other.estimatedTotalCost;
		};
	};

	class GridComponent final : public RamCoreEngine::Component
	{
	public:
		GridComponent(RamCoreEngine::GameObject* gameObject, int amountColumns, int amountRows, int gridWidth, int gridHeight, float cellSize, float offsetY, int screenWidth);
		virtual ~GridComponent() override;

		virtual void LateUpdate() override;

		void SpawnBomb(glm::vec2 position, int range);
		void ExplodeBomb(int index, int range);

		bool IsCellWalkable(const glm::vec2& position, bool isPlayer);
		Cell* GetCellFromPosition(const glm::vec2& position);

		const glm::vec2& GetRandomEmptyCellPosition();

		// TODO: RETURNS COPY NOW
		const std::vector<glm::vec2> GetPath(const glm::vec2& startPosition, const glm::vec2& endPosition);

		
		bool ShouldGridMove(glm::vec2& playerPos, float moveDirection);
		
	private:
		void HandleBreakableWall(Cell* cell);
		void SpawnExplodeTexture(const glm::vec2& position, const std::string& fullPath);
		int GetIndexFromPosition(const glm::vec2& position) const;
		glm::vec2 GetCellPositionFromIndexLocal(const int index) const;
		glm::vec2 GetCellPositionFromIndexWorld(const int index) const;
		int GetIndexWithCellOffset(int columnOffset, int rowOffset, int currentIndex);
		bool IsObjectInCell(const glm::vec2& position, const int cellIndex);
		Cell* GetRandomCell(CellState cellState);

		//A*
		std::vector<int> FindPath(int startIndex, int endIndex);
		float GetHeuristicCost(glm::vec2 a, glm::vec2 b);
		std::vector<int> GetConnectionIndexFromCellIndex(int index);

		std::vector<Cell*> m_pCells;
		std::vector<int> m_ExplodedCellIndices;

		float m_CellWidth;
		float m_CellHeight;
		const float m_OffsetY;
		const int m_AmountColumns;
		const int m_AmountRows;
		const int m_GridWidth;
		const int m_GridHeight;
		const int m_ScreenWidth;

		bool m_BombExploded;
	};
}



