#include "GridComponent.h"
#include "Renderer.h"
#include "BombComponent.h"
#include "GameObject.h"
#include "SpriteSheetComponent.h"
#include "TextureComponent.h"
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
				auto spriteSheetWall = std::make_unique<SpriteSheetComponent>(GetGameObject(), "BreakableWall.png", 7, 1, 0.1f, true, true);
				spriteSheetWall->SetCustomPosition(position);
				cell->m_pSpriteSheetWall = spriteSheetWall.get();
				GetGameObject()->AddComponent(std::move(spriteSheetWall));
			}
			else if (m_pCells.size() % 13 == 0)
			{
				cell->m_CellState = CellState::HardWall;
				auto spriteSheetWall = std::make_unique<TextureComponent>(GetGameObject(), "HardWall.png", true);
				spriteSheetWall->SetCustomPosition(position);
				cell->m_pHardWallTexture = spriteSheetWall.get();
				GetGameObject()->AddComponent(std::move(spriteSheetWall));
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
		int indexRight = GetIndexWithCellOffset(rangeCounter, 0, index);
		if (indexRight != -1)
		{
			Cell* cell = m_pCells[indexRight];
			if (cell->m_CellState == CellState::BreakableWall)
			{
				cell->m_CellState = CellState::Empty;
				cell->m_pSpriteSheetWall->ShouldAnimate(true);
				cell->m_pSpriteSheetWall->SetColumn(1);
			}
				
		}
		
		int indexLeft = GetIndexWithCellOffset(-rangeCounter, 0, index);
		if (indexLeft != -1)
		{
			Cell* cell = m_pCells[indexLeft];
			if (cell->m_CellState == CellState::BreakableWall)
			{
				cell->m_CellState = CellState::Empty;
				cell->m_pSpriteSheetWall->ShouldAnimate(true);
				cell->m_pSpriteSheetWall->SetColumn(1);
			}
		}
		
		int indexDown = GetIndexWithCellOffset(0, rangeCounter, index);
		if (indexDown != -1)
		{
			Cell* cell = m_pCells[indexDown];
			if (cell->m_CellState == CellState::BreakableWall)
			{
				cell->m_CellState = CellState::Empty;
				cell->m_pSpriteSheetWall->ShouldAnimate(true);
				cell->m_pSpriteSheetWall->SetColumn(1);
			}
		}
		
		int indexUp = GetIndexWithCellOffset(0, -rangeCounter, index);
		if(indexUp != -1)
		{
			Cell* cell = m_pCells[indexUp];
			if (cell->m_CellState == CellState::BreakableWall)
			{
				cell->m_CellState = CellState::Empty;
				cell->m_pSpriteSheetWall->ShouldAnimate(true);
				cell->m_pSpriteSheetWall->SetColumn(1);
			}
		}
		
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

	if (newRow < 0 || newColumn < 0 || newRow >= m_AmountRows || newColumn >= m_AmountColumns) // not a valid index
	{
		return -1;
	}

	int newIndex = newRow * m_AmountColumns + newColumn;
	return newIndex;
}


