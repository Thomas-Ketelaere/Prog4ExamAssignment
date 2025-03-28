#include "GridComponent.h"
#include "Renderer.h"
#include "BombComponent.h"
#include "GameObject.h"
#include <memory>

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
			Cell* cell = new Cell(position);
			cell->m_CellState = CellState::Empty;
			if (m_pCells.size() % 7 == 0)
			{
				cell->m_CellState = CellState::BreakableWall;
			}

			m_pCells.emplace_back(cell);
		}
	}
}

dae::GridComponent::~GridComponent()
{
	for (const Cell* cell : m_pCells)
	{
		delete cell;
	}
}

void dae::GridComponent::Render() const
{
	SDL_Color color = { 255, 0, 0, 255 };
	for (const Cell* cell : m_pCells)
	{
		if (cell->m_CellState == CellState::BreakableWall)
		{
			Renderer::GetInstance().FillRectangle(cell->m_Position.x, cell->m_Position.y, m_CellWidth, m_CellHeight, color);
		}
		else
		{
			Renderer::GetInstance().DrawRectangle(cell->m_Position.x, cell->m_Position.y, m_CellWidth, m_CellHeight, color);
		}
	}

	//REMOVE
	SDL_Color lastColor = { 255, 255, 255, 255 };
	Renderer::GetInstance().DrawRectangle(lastPosition.x, lastPosition.y, 32, 32, lastColor);
}


void dae::GridComponent::SpawnBomb(glm::vec2 position)
{
	int index = GetIndexFromPosition(position);
	glm::vec2 spawnPosition = GetCellPositionFromIndex(index);
	auto bombComponent = std::make_unique<BombComponent>(GetGameObject(), this, index, 1.f);
	GetGameObject()->AddComponent(std::move(bombComponent));
}

void dae::GridComponent::ExplodeBomb(int index, int range)
{
	for (int rangeCounter = 1; rangeCounter <= range; ++rangeCounter) // range can be bigger than one, and needs to go over all the cells then
	{
		Cell* cellRight = m_pCells[GetIndexWithCellOffset(rangeCounter, 0, index)];
		if (cellRight->m_CellState == CellState::BreakableWall) cellRight->m_CellState = CellState::Empty;

		Cell* cellLeft = m_pCells[GetIndexWithCellOffset(-rangeCounter, 0, index)];
		if (cellLeft->m_CellState == CellState::BreakableWall) cellLeft->m_CellState = CellState::Empty;

		Cell* cellDown = m_pCells[GetIndexWithCellOffset(0, rangeCounter, index)];
		if (cellDown->m_CellState == CellState::BreakableWall) cellDown->m_CellState = CellState::Empty;

		Cell* cellUp = m_pCells[GetIndexWithCellOffset(0, -rangeCounter, index)];
		if (cellUp->m_CellState == CellState::BreakableWall) cellUp->m_CellState = CellState::Empty;
	}
}

bool dae::GridComponent::IsCellWalkable(const glm::vec2& position)
{
	lastPosition = position;
	if (position.x < 0 || position.x > m_ScreenWidth || position.y < 0 || position.y > m_ScreenHeight)
	{
		return false;
	}

	int indexCell = GetIndexFromPosition(position);
	if (m_pCells[indexCell]->m_CellState == CellState::Empty)
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

glm::vec2 dae::GridComponent::GetCellPositionFromIndex(const int index) const
{
	return m_pCells[index]->m_Position;
}

int dae::GridComponent::GetIndexWithCellOffset(int columnOffset, int rowOffset, int currentIndex)
{
	int currentRow = currentIndex / m_AmountColumns;
	int currentColumn = currentIndex % m_AmountColumns;

	int newRow = currentRow + rowOffset;
	int newColumn = currentColumn + columnOffset;

	return newRow * m_AmountColumns + newColumn;
}


