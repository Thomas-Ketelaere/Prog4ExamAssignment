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
#include "Timer.h"
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
	m_pEnemyState = std::make_unique<WanderingState>(this, speed, shouldTrackPlayer, triggerDistance);
	m_pEnemyDiedEvent = std::make_unique<RamCoreEngine::Subject>();
}

void game::EnemyMovementComponent::Start()
{
	m_pGridComponent = GetGameObject()->GetParent()->GetComponent<GridComponent>();
	m_pSpriteSheetComponent = GetGameObject()->GetComponent<RamCoreEngine::SpriteSheetComponent>();
	

	if (m_ShouldTrackPlayer) // only need to get em if enemy needs to track
	{
		m_pPlayers = RamCoreEngine::SceneManager::GetInstance().GetCurrentScene()->GetAllObjectsWithTag(make_sdbm_hash("Player"));
	}

	m_pEnemyState->OnEnter();
	
}

void game::EnemyMovementComponent::Update()
{
	auto newEnemyState = m_pEnemyState->Update();
	if (newEnemyState != nullptr)
	{
		m_pEnemyState->OnExit();
		m_pEnemyState = std::move(newEnemyState);
		m_pEnemyState->OnEnter();
	}
}

void game::EnemyMovementComponent::Render() const
{
	/*if (m_DebugRender)
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
	}*/
}

void game::EnemyMovementComponent::OnDestroy()
{
	GameManager::GetInstance().GainScore(m_ScoreWhenDead);
	game::GameManager().GetInstance().EnemyKilled();

	Event e(make_sdbm_hash("EnemyDied"));
	m_pEnemyDiedEvent->NotifyObservers(e, GetGameObject());
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
		//std::cout << "TODO: Enemy component removed but not enemy object itself" << std::endl; //wait for state machine maybe?
		m_pEnemyState->OnExit();
		m_pEnemyState = std::make_unique<DyingState>(this, 2.f);
		m_pEnemyState->OnEnter();
	}
}

void game::EnemyMovementComponent::SetSpriteDirection(glm::vec2 direction)
{
	glm::vec2 pos = GetTransform()->GetWorldPosition();

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

void game::WanderingState::OnEnter()
{
	m_Path = GetComponent()->GetGridComponent()->GetPath(GetComponent()->GetGameObject()->GetLocalPosition(), glm::vec2(848, 48));
	m_PathIndex = 0;
}

std::unique_ptr<game::EnemyState> game::WanderingState::Update()
{
	glm::vec2 worldPos = GetComponent()->GetGameObject()->GetWorldPosition();
	glm::vec2 localPos = GetComponent()->GetGameObject()->GetLocalPosition();

	glm::vec3 gridPos = GetComponent()->GetGridComponent()->GetGameObject()->GetWorldPosition();

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

		if (m_PathIndex == movedPath.size() || !GetComponent()->GetGridComponent()->IsCellWalkable(movedPath[m_PathIndex], false))
		{
			m_PathIndex = 1;
			auto randomTarget = GetComponent()->GetGridComponent()->GetRandomEmptyCellPosition();
			m_Path = GetComponent()->GetGridComponent()->GetPath(worldPos, randomTarget);
		}
		glm::vec2 direction = movedPath[m_PathIndex] - worldPos;
		GetComponent()->SetSpriteDirection(direction);
	}

	else
	{
		glm::vec2 direction = movedPath[m_PathIndex] - worldPos;
		glm::vec2 dirNorm = glm::normalize(direction);

		localPos += m_Speed * dirNorm * RamCoreEngine::Time::GetInstance().m_DeltaTime;
		GetComponent()->GetGameObject()->SetLocalPosition(glm::vec3(localPos.x, localPos.y, 0.f));
	}

	if (m_ShouldTrackPlayer)
	{
		bool playerCloseEnough{ false };
		for (RamCoreEngine::GameObject* player : GetComponent()->GetPlayers())
		{
			glm::vec3 playerPos = player->GetWorldPosition();
			if (glm::distance(playerPos, GetComponent()->GetGameObject()->GetWorldPosition()) <= m_TriggerDistance)
			{
				playerCloseEnough = true;
			}
		}

		if (playerCloseEnough)
		{
			return std::make_unique<ChaseState>(GetComponent(), m_Speed, m_TriggerDistance);
		}
	}
	return nullptr;
}

void game::ChaseState::OnEnter()
{
	glm::vec2 worldPos = GetComponent()->GetGameObject()->GetWorldPosition();
	glm::vec2 playerPos = GetRandomPlayerPositionInRange();
	if (playerPos.x != 0 && playerPos.y != 0)
	{
		m_Path = GetComponent()->GetGridComponent()->GetPath(worldPos, playerPos);
		m_PathIndex = 0;
	}
}

std::unique_ptr<game::EnemyState> game::ChaseState::Update()
{
	glm::vec2 worldPos = GetComponent()->GetGameObject()->GetWorldPosition();
	glm::vec2 localPos = GetComponent()->GetGameObject()->GetLocalPosition();

	glm::vec3 gridPos = GetComponent()->GetGridComponent()->GetGameObject()->GetWorldPosition();

	std::vector<glm::vec2> movedPath(m_Path.size());
	std::transform(m_Path.begin(), m_Path.end(), movedPath.begin(), [gridPos](glm::vec2 point)
		{
			point += glm::vec2(gridPos.x, gridPos.y);
			return point;
		});

	if (glm::distance(worldPos, movedPath[m_PathIndex]) <= m_DistanceToReachPoint)
	{
		++m_PathIndex;

		glm::vec2 playerPos = GetRandomPlayerPositionInRange();
		if (playerPos.x != 0 && playerPos.y != 0)
		{
			m_Path = GetComponent()->GetGridComponent()->GetPath(worldPos, playerPos);
			m_PathIndex = 1;
		}
		else //no players close enouhg
		{
			return std::make_unique<WanderingState>(GetComponent(), m_Speed, true, m_TriggerDistance);//since this is in chasing, enemy is able to chase player, so can just say it's true
		}
		glm::vec2 direction = movedPath[m_PathIndex] - worldPos;
		GetComponent()->SetSpriteDirection(direction);
	}

	else
	{
		glm::vec2 direction = movedPath[m_PathIndex] - worldPos;
		glm::vec2 dirNorm = glm::normalize(direction);

		localPos += m_Speed * dirNorm * RamCoreEngine::Time::GetInstance().m_DeltaTime;
		GetComponent()->GetGameObject()->SetLocalPosition(glm::vec3(localPos.x, localPos.y, 0.f));
	}

	return nullptr;
}

glm::vec2 game::ChaseState::GetRandomPlayerPositionInRange()
{
	std::vector<glm::vec3> playersPositions;

	for (RamCoreEngine::GameObject* player : GetComponent()->GetPlayers())
	{
		glm::vec3 playerPos = player->GetWorldPosition();
		if (glm::distance(playerPos, GetComponent()->GetGameObject()->GetWorldPosition()) <= m_TriggerDistance)
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

std::unique_ptr<game::EnemyState> game::DyingState::Update()
{
	m_AccumulatedTime += RamCoreEngine::Time::GetInstance().m_DeltaTime;
	if (m_AccumulatedTime >= m_TimeToDie)
	{
		GetComponent()->GetGameObject()->Destroy();
	}
	return nullptr;
}
