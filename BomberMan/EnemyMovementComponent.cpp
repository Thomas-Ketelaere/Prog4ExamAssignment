#include "EnemyMovementComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "GridComponent.h"
#include "Timer.h"
#include "Renderer.h"
#include "SpriteSheetComponent.h"
#include <iostream>
#include <Subject.h>
#include "SceneManager.h"
#include "GameManager.h"
#include <algorithm>

game::EnemyMovementComponent::EnemyMovementComponent(RamCoreEngine::GameObject* gameObject, const float speed, const int scoreWhenDead):
	EnemyMovementComponent(gameObject, speed, scoreWhenDead, false, 0.f)
{
	
}

game::EnemyMovementComponent::EnemyMovementComponent(RamCoreEngine::GameObject* gameObject, const float speed, const int scoreWhenDead, bool shouldTrackPlayer, float triggerDistance) :
	Component(gameObject),
	m_Speed{ speed },
	m_ScoreWhenDead{ scoreWhenDead },
	m_ShouldTrackPlayer{shouldTrackPlayer},
	m_TriggerDistance{triggerDistance}
{
	m_pEnemyDiedEvent = std::make_unique<RamCoreEngine::Subject>();
}

void game::EnemyMovementComponent::Start()
{
	m_pGridComponent = GetGameObject()->GetParent()->GetComponent<GridComponent>();
	m_pSpriteSheetComponent = GetGameObject()->GetComponent<RamCoreEngine::SpriteSheetComponent>();
	m_Path = m_pGridComponent->GetPath(GetGameObject()->GetLocalPosition() , glm::vec2(848, 48));

	if (m_ShouldTrackPlayer) // only need to get em if enemy needs to track
	{
		m_pPlayers = RamCoreEngine::SceneManager::GetInstance().GetCurrentScene()->GetAllObjectsWithTag(make_sdbm_hash("Player"));
	}
	
}

void game::EnemyMovementComponent::Update()
{
	//if (!m_IsDying)
	//{
	//	glm::vec3 gridPos = m_pGridComponent->GetGameObject()->GetWorldPosition();
	//	std::vector<glm::vec2> movedPath;
	//	movedPath.resize(m_Path.size());

	//	std::transform(m_Path.begin(), m_Path.end(), movedPath.begin(), [gridPos](glm::vec2 point)
	//		{
	//			glm::vec2 movedPoint{point};
	//			movedPoint.x += gridPos.x;
	//			movedPoint.y += gridPos.y;
	//			return movedPoint;
	//		});

	//	glm::vec2 pos = GetGameObject()->GetWorldPosition();
	//	if (glm::distance(pos, m_Path[m_PathIndex]) <= m_DistanceToReachPoint)
	//	{
	//		++m_PathIndex;
	//		if (m_PathIndex == m_Path.size() || !m_pGridComponent->IsCellWalkable(m_Path[m_PathIndex], false)) // if player reached final cell or check if cell is walkable (if e.g. bomb has been placed after path calculation)
	//		{
	//			m_PathIndex = 0; // index 0 is already where enemy is
	//			//new path
	//			auto randomTarget = m_pGridComponent->GetRandomEmptyCell();
	//			m_Path = m_pGridComponent->GetPath(GetGameObject()->GetLocalPosition(), randomTarget);
	//		}

	//		if (m_ShouldTrackPlayer) //needs to check every time it reaches a cell
	//		{
	//			glm::vec2 playerPos = GetRandomPlayerPositionInRange();
	//			if (playerPos.x != 0 && playerPos.y != 0)
	//			{
	//				m_Path = m_pGridComponent->GetPath(GetGameObject()->GetLocalPosition(), playerPos);
	//				m_PathIndex = 0; // index 0 is already where enemy is
	//			}
	//			
	//		}
	//		SetSpriteDirection();
	//	}

	//	else
	//	{
	//		glm::vec2 direction = movedPath[m_PathIndex] - pos;
	//		glm::vec2 dirNorm = glm::normalize(direction);

	//		pos += m_Speed * dirNorm * RamCoreEngine::Time::GetInstance().m_DeltaTime;
	//		
	//		GetGameObject()->SetLocalPosition(glm::vec3(pos.x, pos.y, 0.f));
	//		//GetGameObject()->SetWorldPosition(pos.x, pos.y);
	//	}
	//}

	//	// Local position is already in grid space because enemy is a child of the grid
	//glm::vec2 localPos = GetGameObject()->GetLocalPosition();

	//if (glm::distance(localPos, m_Path[m_PathIndex]) <= m_DistanceToReachPoint)
	//{
	//	++m_PathIndex;

	//	if (m_PathIndex == m_Path.size() || !m_pGridComponent->IsCellWalkable(m_Path[m_PathIndex], false))
	//	{
	//		m_PathIndex = 0;
	//		auto randomTarget = m_pGridComponent->GetRandomEmptyCell();
	//		m_Path = m_pGridComponent->GetPath(localPos, randomTarget);
	//	}

	//	if (m_ShouldTrackPlayer)
	//	{
	//		glm::vec2 playerPos = GetRandomPlayerPositionInRange();
	//		if (playerPos.x != 0 && playerPos.y != 0)
	//		{
	//			m_Path = m_pGridComponent->GetPath(localPos, playerPos);
	//			m_PathIndex = 0;
	//		}
	//	}

	//	SetSpriteDirection();
	//}
	//else
	//{
	//	glm::vec2 direction = m_Path[m_PathIndex] - localPos;
	//	glm::vec2 dirNorm = glm::normalize(direction);

	//	localPos += m_Speed * dirNorm * RamCoreEngine::Time::GetInstance().m_DeltaTime;

	//	GetGameObject()->SetLocalPosition(glm::vec3(localPos.x, localPos.y, 0.f));
	//}
	//


	if (!m_IsDying)
	{


		glm::vec2 worldPos = GetGameObject()->GetWorldPosition();
		glm::vec2 localPos = GetGameObject()->GetLocalPosition();

		glm::vec3 gridPos = m_pGridComponent->GetGameObject()->GetWorldPosition();

		// Convert path points to world space
		std::vector<glm::vec2> movedPath(m_Path.size());
		std::transform(m_Path.begin(), m_Path.end(), movedPath.begin(), [gridPos](glm::vec2 point)
			{
				point += glm::vec2(gridPos.x, gridPos.y);
				return point;
			});


		if (glm::distance(worldPos, movedPath[m_PathIndex]) <= m_DistanceToReachPoint)
		{
			++m_PathIndex;

			if (m_PathIndex == m_Path.size() || !m_pGridComponent->IsCellWalkable(movedPath[m_PathIndex], false))
			{
				m_PathIndex = 1;
				auto randomTarget = m_pGridComponent->GetRandomEmptyCell();
				m_Path = m_pGridComponent->GetPath(worldPos, randomTarget);
			}

			if (m_ShouldTrackPlayer)
			{
				glm::vec2 playerPos = GetRandomPlayerPositionInRange();
				if (playerPos.x != 0 && playerPos.y != 0)
				{
					m_Path = m_pGridComponent->GetPath(worldPos, playerPos);
					m_PathIndex = 1;
				}
			}

			SetSpriteDirection();
		}
		else
		{
			

			
			glm::vec2 direction = movedPath[m_PathIndex] - worldPos;
			glm::vec2 dirNorm = glm::normalize(direction);

			localPos += m_Speed * dirNorm * RamCoreEngine::Time::GetInstance().m_DeltaTime;
			GetGameObject()->SetLocalPosition(glm::vec3(localPos.x, localPos.y, 0.f));
		}
	}
}

void game::EnemyMovementComponent::Render() const
{
	if (m_DebugRender)
	{
		SDL_Color color = { 0, 0, 255, 255 };
		glm::vec3 gridPos = m_pGridComponent->GetGameObject()->GetLocalPosition();
		std::vector<glm::vec2> movedPath;
		movedPath.resize(m_Path.size());

		std::transform(m_Path.begin(), m_Path.end(), movedPath.begin(), [gridPos](glm::vec2 point)
			{
				glm::vec2 movedPoint{ point };
				movedPoint.x += gridPos.x;
				movedPoint.y += gridPos.y;
				return movedPoint;
			});

		for (unsigned int pathCounter{}; pathCounter < movedPath.size() - 1; ++pathCounter)
		{
			glm::vec2 pointOne = movedPath[pathCounter];
			glm::vec2 pointTwo = movedPath[pathCounter + 1];
			RamCoreEngine::Renderer::GetInstance().DrawLine(pointOne.x, pointOne.y, pointTwo.x, pointTwo.y, color);
		}
	}
}

void game::EnemyMovementComponent::StartDying()
{
	if (!m_IsDying)
	{
		m_IsDying = true;
		//play dead animation
		m_pSpriteSheetComponent->SetRow(2);
		m_pSpriteSheetComponent->SetColumn(0);
		m_pSpriteSheetComponent->DestroyAfterPlayed();
		m_pSpriteSheetComponent->SetInterval(0.5f);
		std::cout << "TODO: Enemy component removed but not enemy object itself" << std::endl; //wait for state machine maybe?

		GameManager::GetInstance().GainScore(m_ScoreWhenDead);

		Event e(make_sdbm_hash("EnemyDied"));
		m_pEnemyDiedEvent->NotifyObservers(e, GetGameObject());

	}
}

void game::EnemyMovementComponent::SetSpriteDirection()
{
	glm::vec2 pos = GetTransform()->GetWorldPosition();
	glm::vec2 direction = m_Path[m_PathIndex] - pos;

	if (direction.x > 0.f)
	{
		// set right sprite
		m_pSpriteSheetComponent->SetRow(0);
	}

	else if (direction.x < 0.f)
	{
		//set left sprite
		m_pSpriteSheetComponent->SetRow(1);
	}

}

//returns (0, 0) if not in range
glm::vec2 game::EnemyMovementComponent::GetRandomPlayerPositionInRange()
{
	std::vector<glm::vec3> playersPositions;
		
	for (RamCoreEngine::GameObject* player : m_pPlayers)
	{
		glm::vec3 playerPos = player->GetWorldPosition();
		if (glm::distance(playerPos, GetGameObject()->GetWorldPosition()) <= m_TriggerDistance)
		{
			playersPositions.emplace_back(playerPos);
		}
	}

	if (playersPositions.size() == 0)
	{
		return glm::vec2(0, 0);
	}

	else if (playersPositions.size() == 1)
	{
		return playersPositions[0];
	}

	else
	{
		int randPos = rand() % playersPositions.size();
		return playersPositions[randPos];
	}
}
