#pragma once
#include "Component.h"
#include <vector>
#include <glm.hpp>
namespace dae
{
	enum class CellState
	{
		Empty, HardWall, BreakableWall
	};

	struct Cell
	{ 
		Cell(glm::vec2 position) { m_Position = position; }
		CellState m_CellState{};
		glm::vec2 m_Position{};
	};

	class GridComponent final : public Component
	{
	public:
		GridComponent(GameObject* gameObject, int amountColumns, int amountRows, int screenWidth, int screenHeight);

		virtual void Render() const override;

		bool IsCellWalkable(const glm::vec2& position);
		
	private:
		int GetIndexFromPosition(const glm::vec2& position) const;

		//REMOVE
		glm::vec2 lastPosition{};

		std::vector<Cell> m_Cells;
		float m_CellWidth;
		float m_CellHeight;
		const int m_AmountColumns;
		const int m_AmountRows;
		const int m_ScreenWidth;
		const int m_ScreenHeight;
	};
}



