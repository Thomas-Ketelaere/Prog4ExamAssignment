#include "GridComponent.h"
#include "Renderer.h"
#include "BombComponent.h"
#include "GameObject.h"
#include "SpriteSheetComponent.h"
#include "TextureComponent.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include <memory>

dae::GridComponent::GridComponent(GameObject* gameObject, int amountColumns, int amountRows, int screenWidth, int screenHeight, float cellSize):
	Component(gameObject),
	m_AmountColumns{amountColumns},
	m_AmountRows{amountRows},
	m_ScreenWidth{screenWidth},
	m_ScreenHeight{screenHeight},
	m_CellWidth{cellSize},
	m_CellHeight{cellSize},
	m_CanSpawnBomb{true}
{
	std::vector<Cell*> m_pEmptyCells;
	for (int rowCounter{}; rowCounter < amountRows; ++rowCounter)
	{
		for (int colCounter{}; colCounter < amountColumns; ++colCounter)
		{
			glm::vec2 position = { colCounter * m_CellWidth, rowCounter * m_CellHeight };
			Cell* cell = new Cell(position);
			if (rowCounter == 0 || colCounter == 0 || rowCounter == amountRows - 1 || colCounter == amountColumns - 1)
			{
				cell->m_CellState = CellState::HardWall;
				auto spriteSheetWall = std::make_unique<TextureComponent>(GetGameObject(), "HardWall.png", true);
				spriteSheetWall->SetCustomPosition(position);
				GetGameObject()->AddComponent(std::move(spriteSheetWall));
			}
			else if (rowCounter % 2 == 0 && colCounter % 2 == 0)
			{
				cell->m_CellState = CellState::HardWall;
				auto spriteSheetWall = std::make_unique<TextureComponent>(GetGameObject(), "HardWall.png", true);
				spriteSheetWall->SetCustomPosition(position);
				GetGameObject()->AddComponent(std::move(spriteSheetWall));
			}
			else
			{
				cell->m_CellState = CellState::Empty;
				m_pEmptyCells.emplace_back(cell);
			}

			m_pCells.emplace_back(cell);
		}
	}

	//TODO : MAKE READ FROM FILE
	const int tempAmountOfBreakableWalls{ 10 };
	for (int emptyCounter{}; emptyCounter < tempAmountOfBreakableWalls; ++emptyCounter)
	{
		int index = std::rand() % m_pEmptyCells.size();
		Cell* cell = m_pEmptyCells[index];
		if (cell->m_CellState == CellState::Empty) // make sure that it doesnt set the same cell twice
		{
			cell->m_CellState = CellState::BreakableWall;
			auto spriteSheetWall = std::make_unique<SpriteSheetComponent>(GetGameObject(), "BreakableWall.png", 7, 1, 0.1f, true, true);
			spriteSheetWall->SetCustomPosition(cell->m_Position);
			spriteSheetWall->ShouldAnimate(false);
			cell->m_pSpriteSheetWall = spriteSheetWall.get();
			GetGameObject()->AddComponent(std::move(spriteSheetWall));
		}
	}

	SDL_Color color = { 56, 135, 0, 255 };
	Renderer::GetInstance().SetBackgroundColor(color);
}

dae::GridComponent::~GridComponent()
{
	for (const Cell* cell : m_pCells)
	{
		delete cell;
	}
}


void dae::GridComponent::SpawnBomb(glm::vec2 position)
{
	if (m_CanSpawnBomb)
	{
		int index = GetIndexFromPosition(position);
		if (m_pCells[index]->m_CellState == CellState::Empty) // extra check since position can be off by a bit
		{
			glm::vec2 spawnPosition = GetCellPositionFromIndex(index);
			auto bombObject = std::make_unique<dae::GameObject>();
			auto bombComponent = std::make_unique<BombComponent>(bombObject.get(), this, index, 1.f);
			auto bombSpriteComponent = std::make_unique<SpriteSheetComponent>(bombObject.get(), "Bomb.png", 3, 1, 0.3f, true);
			bombObject->SetWorldPosition(spawnPosition.x, spawnPosition.y);
			bombObject->AddComponent(std::move(bombComponent));
			bombObject->AddComponent(std::move(bombSpriteComponent));
			bombObject->SetParent(GetGameObject(), true);
			SceneManager::GetInstance().GetCurrentScene()->Add(std::move(bombObject));
			m_CanSpawnBomb = false;
		}
	}
}

void dae::GridComponent::ExplodeBomb(int index, int range)
{
	//TODO : CLEAN UP AND MAKE MORE EFFICIENT
	m_CanSpawnBomb = true;

	auto& ss = dae::ServiceLocator::GetSoundSystem();
	ss.Play(10, 100);

	// also check once for place with bomb on
	Cell* cellCenter = m_pCells[index];
	auto spriteSheetExplosionCenter = std::make_unique<SpriteSheetComponent>(GetGameObject(), "ExplosionCenter.png", 7, 1, 0.1f, true, true);
	spriteSheetExplosionCenter->SetCustomPosition(cellCenter->m_Position);
	GetGameObject()->AddComponent(std::move(spriteSheetExplosionCenter));

	for (int rangeCounter = 1; rangeCounter <= range; ++rangeCounter) // need different for loop for each direction, so it'll break when hitting hard wall
	{
		int indexRight = GetIndexWithCellOffset(rangeCounter, 0, index);
		if (indexRight == -1) break;

		Cell* cell = m_pCells[indexRight];
		if (cell->m_CellState == CellState::HardWall) break; 

		if (cell->m_CellState == CellState::BreakableWall)
		{
			cell->m_CellState = CellState::Empty;
			cell->m_pSpriteSheetWall->ShouldAnimate(true);
			cell->m_pSpriteSheetWall->SetColumn(1);
			break;
		}
		else // empty cell
		{
			if (rangeCounter != range)
			{
				SpawnExplodeTexture(cell->m_Position, "ExplosionSide.png");
			}
			else
			{
				SpawnExplodeTexture(cell->m_Position, "ExplosionEndRight.png");
			}
		}
	}

	// Left direction
	for (int rangeCounter = 1; rangeCounter <= range; ++rangeCounter)
	{
		int indexLeft = GetIndexWithCellOffset(-rangeCounter, 0, index);
		if (indexLeft == -1) break;

		Cell* cell = m_pCells[indexLeft];
		if (cell->m_CellState == CellState::HardWall) break;

		if (cell->m_CellState == CellState::BreakableWall)
		{
			cell->m_CellState = CellState::Empty;
			cell->m_pSpriteSheetWall->ShouldAnimate(true);
			cell->m_pSpriteSheetWall->SetColumn(1);
			break;
		}

		else // empty cell
		{
			if (rangeCounter != range)
			{
				SpawnExplodeTexture(cell->m_Position, "ExplosionSide.png");
			}
			else
			{
				SpawnExplodeTexture(cell->m_Position, "ExplosionEndLeft.png");
			}
		}
	}

	// Down direction
	for (int rangeCounter = 1; rangeCounter <= range; ++rangeCounter)
	{
		int indexDown = GetIndexWithCellOffset(0, rangeCounter, index);
		if (indexDown == -1) break;

		Cell* cell = m_pCells[indexDown];
		if (cell->m_CellState == CellState::HardWall) break;

		if (cell->m_CellState == CellState::BreakableWall)
		{
			cell->m_CellState = CellState::Empty;
			cell->m_pSpriteSheetWall->ShouldAnimate(true);
			cell->m_pSpriteSheetWall->SetColumn(1);
			break;
		}

		else // empty cell
		{
			if (rangeCounter != range)
			{
				SpawnExplodeTexture(cell->m_Position, "ExplosionDown.png");
			}
			else
			{
				SpawnExplodeTexture(cell->m_Position, "ExplosionEndDown.png");
			}

		}
	}

	// Up direction
	for (int rangeCounter = 1; rangeCounter <= range; ++rangeCounter)
	{
		int indexUp = GetIndexWithCellOffset(0, -rangeCounter, index);
		if (indexUp == -1) break;

		Cell* cell = m_pCells[indexUp];
		if (cell->m_CellState == CellState::HardWall) break;

		if (cell->m_CellState == CellState::BreakableWall)
		{
			cell->m_CellState = CellState::Empty;
			cell->m_pSpriteSheetWall->ShouldAnimate(true);
			cell->m_pSpriteSheetWall->SetColumn(1);
			break;
		}

		else // empty cell
		{
			if (rangeCounter != range)
			{
				SpawnExplodeTexture(cell->m_Position, "ExplosionUp.png");
			}
			else
			{
				SpawnExplodeTexture(cell->m_Position, "ExplosionEndUp.png");
			}
		}
	}
}

bool dae::GridComponent::IsCellWalkable(const glm::vec2& position)
{
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

void dae::GridComponent::SpawnExplodeTexture(const glm::vec2& position, const std::string& fullPath)
{
	auto spriteSheetExplosion = std::make_unique<SpriteSheetComponent>(GetGameObject(), fullPath, 7, 1, 0.1f, true, true);
	spriteSheetExplosion->SetCustomPosition(position);
	GetGameObject()->AddComponent(std::move(spriteSheetExplosion));
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


