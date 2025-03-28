#include "GridComponent.h"
#include "Renderer.h"

dae::GridComponent::GridComponent(GameObject* gameObject, int amountColumns, int amountRows, int screenWidth, int screenHeight):
	Component(gameObject),
	m_AmountColumns{amountColumns},
	m_AmountRows{amountRows},
	m_ScreenWidth{screenWidth},
	m_ScreenHeight{screenHeight}
{
	m_CellWidth = screenWidth / float(amountColumns);
	m_CellHeight = screenHeight / float(amountRows);
	for (int rowCounter{}; rowCounter < amountRows; ++rowCounter)
	{
		for (int colCounter{}; colCounter < amountColumns; ++colCounter)
		{
			glm::vec2 position = { colCounter * m_CellWidth, rowCounter * m_CellHeight };
			Cell cell{ position };
			cell.m_CellState = CellState::Empty;
			if (m_Cells.size() % 7 == 0)
			{
				cell.m_CellState = CellState::HardWall;
			}

			m_Cells.emplace_back(cell);
		}
	}
}

void dae::GridComponent::Render() const
{
	SDL_Color color = { 255, 0, 0, 255 };
	for (const Cell& cell : m_Cells)
	{
		if (cell.m_CellState == CellState::HardWall)
		{
			Renderer::GetInstance().FillRectangle(cell.m_Position.x, cell.m_Position.y, m_CellWidth, m_CellHeight, color);
		}
		else
		{
			Renderer::GetInstance().DrawRectangle(cell.m_Position.x, cell.m_Position.y, m_CellWidth, m_CellHeight, color);
		}
	}

	//REMOVE
	SDL_Color lastColor = { 255, 255, 255, 255 };
	Renderer::GetInstance().DrawRectangle(lastPosition.x, lastPosition.y, 32, 32, lastColor);
}

bool dae::GridComponent::IsCellWalkable(const glm::vec2& position)
{
	lastPosition = position;
	if (position.x < 0 || position.x > m_ScreenWidth || position.y < 0 || position.y > m_ScreenHeight)
	{
		return false;
	}

	int indexCell = GetIndexFromPosition(position);
	if (m_Cells[indexCell].m_CellState == CellState::Empty)
	{
		return true;
	}
	return false;
}

int dae::GridComponent::GetIndexFromPosition(const glm::vec2& pos) const
{
	int column = int(pos.x / m_CellWidth);
	int row = int(pos.y / m_CellHeight);

	int index = row * m_AmountColumns + column;

	return index;
}
