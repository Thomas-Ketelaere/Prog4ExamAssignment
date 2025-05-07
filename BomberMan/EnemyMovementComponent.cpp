#include "EnemyMovementComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "GridComponent.h"
#include "Timer.h"
#include "Renderer.h"
#include "SpriteSheetComponent.h"
#include <iostream>
#include <Subject.h>
#include"SceneManager.h"

game::EnemyMovementComponent::EnemyMovementComponent(RamCoreEngine::GameObject* gameObject, const float speed, const std::string& name):
	EnemyMovementComponent(gameObject, speed, name, false, 0.f)
{
	
}

game::EnemyMovementComponent::EnemyMovementComponent(RamCoreEngine::GameObject* gameObject, const float speed, const std::string& name, bool shouldTrackPlayer, float triggerDistance) :
	Component(gameObject),
	m_Speed{ speed },
	m_Name{ name },
	m_ShouldTrackPlayer{shouldTrackPlayer},
	m_TriggerDistance{triggerDistance}
{
	m_pEnemyDiedEvent = std::make_unique<RamCoreEngine::Subject>();
}

void game::EnemyMovementComponent::Start()
{
	m_pGridComponent = GetGameObject()->GetParent()->GetComponent<GridComponent>();
	m_pSpriteSheetComponent = GetGameObject()->GetComponent<RamCoreEngine::SpriteSheetComponent>();
	m_Path = m_pGridComponent->GetPath(GetTransform()->GetWorldPosition() , glm::vec2(848, 48));

	if (m_ShouldTrackPlayer) // only need to get em if enemy needs to track
	{
		m_pPlayers = RamCoreEngine::SceneManager::GetInstance().GetCurrentScene()->GetAllObjectsWithTag(make_sdbm_hash("Player"));
	}
	
}

void game::EnemyMovementComponent::Update()
{
	if (!m_IsDying)
	{
		glm::vec2 pos = GetTransform()->GetWorldPosition();
		if (glm::distance(pos, m_Path[m_PathIndex]) <= m_DistanceToReachPoint)
		{
			++m_PathIndex;
			if (m_PathIndex == m_Path.size() || !m_pGridComponent->IsCellWalkable(m_Path[m_PathIndex], false)) // if player reached final cell or check if cell is walkable (if e.g. bomb has been placed after path calculation)
			{
				m_PathIndex = 1; // index 0 is already where enemy is
				//new path
				auto randomTarget = m_pGridComponent->GetRandomEmptyCell();
				m_Path = m_pGridComponent->GetPath(GetTransform()->GetWorldPosition(), randomTarget);
			}

			if (m_ShouldTrackPlayer) //needs to check every time it reaches a cell
			{
				glm::vec2 playerPos = GetRandomPlayerPositionInRange();
				if (playerPos.x != 0 && playerPos.y != 0)
				{
					m_Path = m_pGridComponent->GetPath(GetTransform()->GetWorldPosition(), playerPos);
					m_PathIndex = 1; // index 0 is already where enemy is
				}
				
			}
			SetSpriteDirection();
		}

		else
		{
			glm::vec2 direction = m_Path[m_PathIndex] - pos;
			glm::vec2 dirNorm = glm::normalize(direction);

			pos += m_Speed * dirNorm * RamCoreEngine::Time::GetInstance().m_DeltaTime;

			GetGameObject()->SetWorldPosition(pos.x, pos.y);
		}
	}
	
}

void game::EnemyMovementComponent::Render() const
{
	if (m_DebugRender)
	{
		SDL_Color color = { 0, 0, 255, 255 };
		for (unsigned int pathCounter{}; pathCounter < m_Path.size() - 1; ++pathCounter)
		{
			glm::vec2 pointOne = m_Path[pathCounter];
			glm::vec2 pointTwo = m_Path[pathCounter + 1];
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

		if (m_Name == "Balloom")
		{
			Event e(make_sdbm_hash("KilledBalloom"));
			m_pEnemyDiedEvent->NotifyObservers(e, GetGameObject());
		}
		
		else if(m_Name == "Oneal")
		{
			//event killed oneal
		}

		else if (m_Name == "Doll")
		{
			//event killed Doll
		}

		else if (m_Name == "Minvo")
		{
			//event killed Minvo
		}

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
		if (glm::distance(playerPos, GetTransform()->GetWorldPosition()) <= m_TriggerDistance)
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
