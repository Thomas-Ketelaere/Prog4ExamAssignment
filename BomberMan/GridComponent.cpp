#include "GridComponent.h"
#include "Renderer.h"
#include "BombComponent.h"
#include "GameObject.h"
#include "SpriteSheetComponent.h"
#include "TextureComponent.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include <memory>
#include "EnemyMovementComponent.h"

#include "PlayerSpriteComponent.h"
game::GridComponent::GridComponent(RamCoreEngine::GameObject* gameObject, int amountColumns, int amountRows, int gridWidth, int gridHeight, float cellSize, float offsetY, int screenWidth):
	Component(gameObject),
	m_AmountColumns{amountColumns},
	m_AmountRows{amountRows},
	m_GridWidth{gridWidth},
	m_GridHeight{gridHeight},
	m_CellWidth{cellSize},
	m_CellHeight{cellSize},
	m_CanSpawnBomb{true},
	m_BombExploded{},
	m_OffsetY{offsetY},
	m_ScreenWidth{screenWidth}
{
	std::vector<Cell*> emptyCells;
	for (int rowCounter{}; rowCounter < amountRows; ++rowCounter)
	{
		for (int colCounter{}; colCounter < amountColumns; ++colCounter)
		{
			glm::vec2 position = { colCounter * m_CellWidth + m_CellWidth / 2, rowCounter * m_CellHeight + m_CellHeight / 2 + offsetY};
			Cell* cell = new Cell(position);
			if (rowCounter == 0 || colCounter == 0 || rowCounter == amountRows - 1 || colCounter == amountColumns - 1)
			{
				cell->m_CellState = CellState::HardWall;
				auto spriteSheetWall = std::make_unique<RamCoreEngine::TextureComponent>(GetGameObject(), "HardWall.png", true);
				spriteSheetWall->SetCustomPosition(position);
				GetGameObject()->AddComponent(std::move(spriteSheetWall));
			}
			else if (rowCounter % 2 == 0 && colCounter % 2 == 0)
			{
				cell->m_CellState = CellState::HardWall;
				auto spriteSheetWall = std::make_unique<RamCoreEngine::TextureComponent>(GetGameObject(), "HardWall.png", true);
				spriteSheetWall->SetCustomPosition(position);
				GetGameObject()->AddComponent(std::move(spriteSheetWall));
			}
			else
			{
				cell->m_CellState = CellState::Empty;
				emptyCells.emplace_back(cell);
			}

			m_pCells.emplace_back(cell);
		}
	}

	//TODO : MAKE READ FROM FILE
	const int tempAmountOfBreakableWalls{ 10 };
	for (int emptyCounter{}; emptyCounter < tempAmountOfBreakableWalls; ++emptyCounter)
	{
		int index = std::rand() % emptyCells.size();
		Cell* cell = emptyCells[index];
		if (cell->m_CellState == CellState::Empty) // make sure that it doesnt set the same cell twice
		{
			cell->m_CellState = CellState::BreakableWall;
			cell->m_CellItem = CellItem::Exit; //TODO: obviously not all breakable walls are Exits, this is just for testing purposes
			auto spriteSheetWall = std::make_unique<RamCoreEngine::SpriteSheetComponent>(GetGameObject(), "BreakableWall.png", 7, 1, 0.1f, true, true);
			spriteSheetWall->SetCustomPosition(cell->m_Position);
			spriteSheetWall->ShouldAnimate(false);
			cell->m_pSpriteSheetWall = spriteSheetWall.get(); 
			emptyCells.erase(emptyCells.begin() + index);
			GetGameObject()->AddComponent(std::move(spriteSheetWall));
		}
	}


	SDL_Color color = { 56, 135, 0, 255 };
	RamCoreEngine::Renderer::GetInstance().SetBackgroundColor(color);
}

game::GridComponent::~GridComponent()
{
	for (const Cell* cell : m_pCells)
	{
		delete cell;
	}
}

void game::GridComponent::LateUpdate()
{
	if (m_BombExploded)
	{
		std::vector<RamCoreEngine::GameObject*> objectsOnGrid = GetGameObject()->GetChildren(); //TODO: copy? (maybe save it)
		std::vector<RamCoreEngine::GameObject*> playerObjects = RamCoreEngine::SceneManager::GetInstance().GetCurrentScene()->GetAllObjectsWithTag(make_sdbm_hash("Player")); //TODO: make it so it's possible to get it from one function and not adding vectors
		objectsOnGrid.insert(objectsOnGrid.end(), playerObjects.begin(), playerObjects.end());
		for (int index : m_ExplodedCellIndices)
		{
			for (RamCoreEngine::GameObject* object : objectsOnGrid)
			{
				if (IsObjectInCell(object->GetWorldPosition(), index))
				{
					EnemyMovementComponent* enemyComponent = object->GetComponent<EnemyMovementComponent>();
					if (enemyComponent)
					{
						enemyComponent->StartDying();
						continue;
					}

					PlayerSpriteComponent* playerComponent = object->GetComponent<PlayerSpriteComponent>();
					if (playerComponent)
					{
						playerComponent->StartDying();
					}

				}
			}
		}
		m_BombExploded = false; // this should be after some time
	}
	
}


void game::GridComponent::SpawnBomb(glm::vec2 position)
{
	if (m_CanSpawnBomb)
	{
		int index = GetIndexFromPosition(position);
		if (m_pCells[index]->m_CellState == CellState::Empty) // extra check since position can be off by a bit
		{
			glm::vec2 spawnPosition = GetCellPositionFromIndexWorld(index);
			glm::vec3 gridPos = GetTransform()->GetWorldPosition();
			glm::vec2 spawnPosMoved{};
			spawnPosMoved.x = spawnPosition.x - gridPos.x;
			spawnPosMoved.y = spawnPosition.y - gridPos.y;
			auto bombObject = std::make_unique<RamCoreEngine::GameObject>();
			bombObject->SetParent(GetGameObject(), true);
			auto bombComponent = std::make_unique<BombComponent>(bombObject.get(), this, index, 2.f);
			auto bombSpriteComponent = std::make_unique<RamCoreEngine::SpriteSheetComponent>(bombObject.get(), "Bomb.png", 3, 1, 0.2f, false);
			bombObject->SetLocalPosition(glm::vec3(spawnPosMoved.x, spawnPosMoved.y, 0.f));
			bombObject->AddComponent(std::move(bombComponent));
			bombObject->AddComponent(std::move(bombSpriteComponent));
			RamCoreEngine::SceneManager::GetInstance().GetCurrentScene()->Add(std::move(bombObject));
			m_pCells[index]->m_CellState = CellState::Bomb;
			m_CanSpawnBomb = false;
		}
	}
}

void game::GridComponent::ExplodeBomb(int index, int range)
{
	//TODO : CLEAN UP AND MAKE MORE EFFICIENT
	m_CanSpawnBomb = true;
	m_BombExploded = true;
	m_ExplodedCellIndices.clear();
	m_ExplodedCellIndices.emplace_back(index);

	// also check once for place with bomb on
	Cell* cellCenter = m_pCells[index];
	
	cellCenter->m_CellState = CellState::Empty;
	auto spriteSheetExplosionCenter = std::make_unique<RamCoreEngine::SpriteSheetComponent>(GetGameObject(), "ExplosionCenter.png", 7, 1, 0.1f, true, true);
	spriteSheetExplosionCenter->SetCustomPosition(cellCenter->m_Position);
	GetGameObject()->AddComponent(std::move(spriteSheetExplosionCenter));
	
	

	for (int rangeCounter = 1; rangeCounter <= range; ++rangeCounter) // need different for loop for each direction, so it'll break when hitting hard wall
	{
		int indexRight = GetIndexWithCellOffset(rangeCounter, 0, index);
		if (indexRight == -1) break;

		Cell* cell = m_pCells[indexRight];
		if (cell->m_CellState == CellState::HardWall) break;

		m_ExplodedCellIndices.emplace_back(indexRight); // player cant stand on hardwall so after check

		if (cell->m_CellState == CellState::BreakableWall)
		{
			HandleBreakableWall(cell);
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

		m_ExplodedCellIndices.emplace_back(indexLeft);

		if (cell->m_CellState == CellState::BreakableWall)
		{
			HandleBreakableWall(cell);
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

		m_ExplodedCellIndices.emplace_back(indexDown);

		if (cell->m_CellState == CellState::BreakableWall)
		{
			HandleBreakableWall(cell);
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

		m_ExplodedCellIndices.emplace_back(indexUp);

		if (cell->m_CellState == CellState::BreakableWall)
		{
			HandleBreakableWall(cell);
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

bool game::GridComponent::IsCellWalkable(const glm::vec2& position, bool isPlayer) //player can walk over bomb while enemies cant
{
	if (position.x < 0 || position.x > m_GridWidth || position.y < 0 || position.y > m_GridHeight)
	{
		return false;
	}

	int indexCell = GetIndexFromPosition(position);
	if (isPlayer)
	{
		if (m_pCells[indexCell]->m_CellState == CellState::Empty)
		{
			switch (m_pCells[indexCell]->m_CellItem)
			{
			case CellItem::Exit:
				//Check enemies (from game manager?)
				//Level completed
				m_pCells[indexCell]->m_CellItem = CellItem::Empty;
				m_pCells[indexCell]->m_pSpriteSheetWall->Destroy();
				break;
			case CellItem::DetonatorPU:
				//gain ability
				m_pCells[indexCell]->m_CellItem = CellItem::Empty;
				m_pCells[indexCell]->m_pSpriteSheetWall->Destroy();
				break;
			case CellItem::FlamesPU:
				//gain ability
				m_pCells[indexCell]->m_CellItem = CellItem::Empty;
				m_pCells[indexCell]->m_pSpriteSheetWall->Destroy();
				break;
			case CellItem::ExtraBombPU:
				//gain ability
				m_pCells[indexCell]->m_CellItem = CellItem::Empty;
				m_pCells[indexCell]->m_pSpriteSheetWall->Destroy();
				break;
			}

			return true; //is still possible to reach empty layer so return here
		}


		else if (m_pCells[indexCell]->m_CellState == CellState::Bomb)
		{
			return true;
		}
	}

	else
	{
		if (m_pCells[indexCell]->m_CellState == CellState::Empty)
		{
			return true;
		}
	}
	
	return false;
}

game::Cell* game::GridComponent::GetCellFromPosition(const glm::vec2& position)
{
	int index = GetIndexFromPosition(position);
	return m_pCells[index];
}

const glm::vec2& game::GridComponent::GetRandomEmptyCell()
{
	std::vector<Cell*> emptyCells;
	for (Cell* cell : m_pCells)
	{
		if (cell->m_CellState == CellState::Empty)
		{
			emptyCells.emplace_back(cell);
		}
	}

	int index = std::rand() % emptyCells.size();
	return emptyCells[index]->m_Position;
}

const std::vector<glm::vec2> game::GridComponent::GetPath(const glm::vec2& startPosition, const glm::vec2& endPosition)
{
	std::vector<glm::vec2> pathPositions;
	const int startIndex = GetIndexFromPosition(startPosition); 
	const int endIndex = GetIndexFromPosition(endPosition);

	const std::vector<int> indices = FindPath(startIndex, endIndex);

	pathPositions.clear();
	
	for (int index : indices)
	{
		pathPositions.emplace_back(GetCellPositionFromIndexLocal(index));
	}

	if (indices.size() == 1) // didn't find a path, so locked in, but did already add first index in for loop above
	{
		std::vector<int> neighborIndices = GetConnectionIndexFromCellIndex(startIndex);
		if (neighborIndices.size() > 0) //locked in more than one cell
		{
			pathPositions.emplace_back(GetCellPositionFromIndexLocal(neighborIndices[0])); // just add first neighbor to wander between the two
		}
	}

	return pathPositions;
}

bool game::GridComponent::ShouldGridMove(glm::vec2& playerPos, float moveDirection)
{

	const float centerMargin = 5.f;
	float centerX = m_ScreenWidth / 2.f;

	if (playerPos.x < centerX - centerMargin || playerPos.x > centerX + centerMargin)
	{
		return false;
	}
		
	const glm::vec3& gridPos = GetGameObject()->GetWorldPosition();

	if (moveDirection > 0.f)
	{
		if (m_ScreenWidth - gridPos.x < m_GridWidth)
		{
			return true;
		}
			
	}

	else if (moveDirection < 0.f)
	{
		if (gridPos.x < 0.f)
		{
			return true;
		}
			
	}

	return false;
}


void game::GridComponent::HandleBreakableWall(Cell* cell)
{
	cell->m_CellState = CellState::Empty;
	if (cell->m_CellItem == CellItem::Empty)
	{
		cell->m_pSpriteSheetWall->ShouldAnimate(true);
		cell->m_pSpriteSheetWall->SetColumn(1);
	}

	else if (cell->m_CellItem == CellItem::Exit)
	{
		cell->m_pSpriteSheetWall->Destroy();
		auto spriteSheetWall = std::make_unique<RamCoreEngine::SpriteSheetComponent>(GetGameObject(), "Exit.png", 1, 1, 0.1f, false, true);
		spriteSheetWall->SetCustomPosition(cell->m_Position);
		spriteSheetWall->ShouldAnimate(false);
		cell->m_pSpriteSheetWall = spriteSheetWall.get();
		GetGameObject()->AddComponent(std::move(spriteSheetWall));
	}

	//TODO: do this for all power ups
	/*else if (cell->m_CellItem == CellItem::ExtraBombPU)
	{
		cell->m_pSpriteSheetWall->Destroy();
		auto spriteSheetWall = std::make_unique<SpriteSheetComponent>(GetGameObject(), "Exit.png", 1, 1, 0.1f, false, true);
		spriteSheetWall->SetCustomPosition(cell->m_Position);
		spriteSheetWall->ShouldAnimate(false);
		cell->m_pSpriteSheetWall = spriteSheetWall.get();
		GetGameObject()->AddComponent(std::move(spriteSheetWall));
	}*/
}

void game::GridComponent::SpawnExplodeTexture(const glm::vec2& position, const std::string& fullPath)
{
	auto spriteSheetExplosion = std::make_unique<RamCoreEngine::SpriteSheetComponent>(GetGameObject(), fullPath, 7, 1, 0.1f, true, true);
	spriteSheetExplosion->SetCustomPosition(position);
	GetGameObject()->AddComponent(std::move(spriteSheetExplosion));
}

int game::GridComponent::GetIndexFromPosition(const glm::vec2& pos) const
{
	glm::vec3 gridPos = GetTransform()->GetWorldPosition();
	glm::vec2 movedPos{};
	movedPos.x = pos.x - gridPos.x;
	movedPos.y = pos.y - gridPos.y;
	int column = int(movedPos.x / m_CellWidth);
	int row = int((movedPos.y - m_OffsetY) / m_CellHeight);

	int index = row * m_AmountColumns + column;

	return index;
}

glm::vec2 game::GridComponent::GetCellPositionFromIndexLocal(const int index) const
{
	return m_pCells[index]->m_Position;
}

glm::vec2 game::GridComponent::GetCellPositionFromIndexWorld(const int index) const
{
	glm::vec2 cellPos = m_pCells[index]->m_Position;
	glm::vec2 gridPos = GetGameObject()->GetWorldPosition();
	cellPos.x += gridPos.x;
	cellPos.y += gridPos.y;
	return cellPos;
}

//returns -1 if not valid
int game::GridComponent::GetIndexWithCellOffset(int columnOffset, int rowOffset, int currentIndex)
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

bool game::GridComponent::IsObjectInCell(const glm::vec2& position, const int cellIndex)
{
	int indexObject = GetIndexFromPosition(position);
	if (indexObject == cellIndex)
	{
		return true;
	}
	return false;
}

std::vector<int> game::GridComponent::FindPath(int startIndex, int endIndex)
{
	std::vector<int> pathIndices{};
	std::list<Node> openList;
	std::list<Node> closedList;

	//check if cell is reachable
	if (m_pCells[endIndex]->m_CellState != CellState::Empty)
	{
		pathIndices.emplace_back(startIndex);
		return pathIndices;
	}

	Node currentNodeRecord{};
	Node startNodeRecord{};
	startNodeRecord.index = startIndex;
	startNodeRecord.connectionIndex = -1;
	startNodeRecord.estimatedTotalCost = GetHeuristicCost(GetCellPositionFromIndexWorld(startIndex), GetCellPositionFromIndexWorld(endIndex));

	openList.push_back(startNodeRecord);

	while (!openList.empty())
	{
		auto currentNodeRecordIt = std::min_element(openList.begin(), openList.end());
		currentNodeRecord = *currentNodeRecordIt;

		if (currentNodeRecord.index == endIndex)
		{
			break;
		}

		for (int connectionIndex : GetConnectionIndexFromCellIndex(currentNodeRecord.index))
		{

			float cost = currentNodeRecord.estimatedTotalCost + 1; // not working with different types of floor, so extra cost is always one
			auto closedIt = std::find_if(closedList.begin(), closedList.end(), [&](const Node& record) { return record.index == connectionIndex; });
			if (closedIt != closedList.end())
			{
				if (closedIt->costSoFar < cost)
				{
					continue;
				}
				else
				{
					closedList.erase(closedIt);
				}
			}

			auto openIt = std::find_if(openList.begin(), openList.end(), [&](const Node& record) { return record.index == connectionIndex; });
			if (openIt != openList.end())
			{
				if (openIt->costSoFar < cost)
				{
					continue;
				}
				else
				{
					openList.erase(openIt);
				}
			}
			Node nodeRecord;
			nodeRecord.index = connectionIndex;
			nodeRecord.costSoFar = cost;
			nodeRecord.connectionIndex = currentNodeRecord.index;
			nodeRecord.estimatedTotalCost = GetHeuristicCost(GetCellPositionFromIndexWorld(connectionIndex), GetCellPositionFromIndexWorld(endIndex)) + cost;
			openList.push_back(nodeRecord);
		}

		auto it = std::find_if(openList.begin(), openList.end(),
			[currentNodeRecord](const Node& record)
			{
				return record.index == currentNodeRecord.index;
			});

		if (it != openList.end())
		{
			openList.erase(it);
		}
		closedList.push_back(currentNodeRecord);

	}

	while (currentNodeRecord.index != startIndex)
	{
		pathIndices.push_back(currentNodeRecord.index);

		auto it = std::find_if(closedList.begin(), closedList.end(),
			[&](const Node& record)
			{
				return record.index == currentNodeRecord.connectionIndex;
			});

		if (it == closedList.end())
		{
			break;
		}

		currentNodeRecord = *it;  // Move to the previous node in the path
	}

	pathIndices.push_back(startIndex);
	std::reverse(pathIndices.begin(), pathIndices.end());

	return pathIndices;
}

float game::GridComponent::GetHeuristicCost(glm::vec2 a, glm::vec2 b)
{
	//using the Manhattan distance (TODO: why this one)
	float manDistance = abs(a.x - b.x) + abs(a.y - b.y);
	return manDistance;
}

std::vector<int> game::GridComponent::GetConnectionIndexFromCellIndex(int index)
{
	std::vector<int> connections{};
	//only allow connections that are walkable
	int indexMoved = GetIndexWithCellOffset(-1, 0, index);
	if (indexMoved != -1)
	{
		if (m_pCells[indexMoved]->m_CellState == CellState::Empty)
		{
			connections.emplace_back(indexMoved);
		}
	}
	
	indexMoved = GetIndexWithCellOffset(1, 0, index);
	if (indexMoved != -1)
	{
		if (m_pCells[indexMoved]->m_CellState == CellState::Empty)
		{
			connections.emplace_back(indexMoved);
		}
	}

	indexMoved = GetIndexWithCellOffset(0, -1, index);
	if (indexMoved != -1)
	{
		if (m_pCells[indexMoved]->m_CellState == CellState::Empty)
		{
			connections.emplace_back(indexMoved);
		}
	}

	indexMoved = GetIndexWithCellOffset(0, 1, index);
	if (indexMoved != -1)
	{
		if (m_pCells[indexMoved]->m_CellState == CellState::Empty)
		{
			connections.emplace_back(indexMoved);
		}
	}

	return connections;
}


