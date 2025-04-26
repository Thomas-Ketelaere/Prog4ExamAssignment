#include "EnemyMovementComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "GridComponent.h"
#include "Timer.h"
#include "Renderer.h"
#include "SpriteSheetComponent.h"
#include <iostream>
#include <Subject.h>

dae::EnemyMovementComponent::EnemyMovementComponent(GameObject* gameObject, const float speed, const std::string& name):
	Component(gameObject),
	m_Speed{speed},
	m_Name{name}
{
	m_pEnemyDiedEvent = std::make_unique<Subject>();
}

void dae::EnemyMovementComponent::Start()
{
	m_pGridComponent = GetGameObject()->GetParent()->GetComponent<GridComponent>();
	m_pSpriteSheetComponent = GetGameObject()->GetComponent<SpriteSheetComponent>();
	m_Path = m_pGridComponent->GetPath(GetTransform()->GetWorldPosition() , glm::vec2(848, 48));
}

void dae::EnemyMovementComponent::Update()
{
	if (!m_IsDying)
	{
		glm::vec2 pos = GetTransform()->GetWorldPosition();
		if (glm::distance(pos, m_Path[m_PathIndex]) <= m_DistanceToReachPoint)
		{
			++m_PathIndex;
			if (m_PathIndex == m_Path.size())
			{
				m_PathIndex = 0;
				//new path
				auto randomTarget = m_pGridComponent->GetRandomEmptyCell();
				m_Path = m_pGridComponent->GetPath(GetTransform()->GetWorldPosition(), randomTarget);
			}

			else if (!m_pGridComponent->IsCellWalkable(m_Path[m_PathIndex], false)) //check if cell is walkable (if e.g. bomb has been placed after path calculation)
			{
				m_PathIndex = 0;
				//new path
				auto randomTarget = m_pGridComponent->GetRandomEmptyCell();
				m_Path = m_pGridComponent->GetPath(GetTransform()->GetWorldPosition(), randomTarget);
			}
			SetSpriteDirection();
		}

		else
		{
			glm::vec2 direction = m_Path[m_PathIndex] - pos;
			glm::vec2 dirNorm = glm::normalize(direction);

			pos += m_Speed * dirNorm * Time::GetInstance().m_DeltaTime;

			GetGameObject()->SetWorldPosition(pos.x, pos.y);
		}
	}
	
}

void dae::EnemyMovementComponent::Render() const
{
	if (m_DebugRender)
	{
		SDL_Color color = { 0, 0, 255, 255 };
		for (unsigned int pathCounter{}; pathCounter < m_Path.size() - 1; ++pathCounter)
		{
			glm::vec2 pointOne = m_Path[pathCounter];
			glm::vec2 pointTwo = m_Path[pathCounter + 1];
			Renderer::GetInstance().DrawLine(pointOne.x, pointOne.y, pointTwo.x, pointTwo.y, color);
		}
	}
}

void dae::EnemyMovementComponent::StartDying()
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

void dae::EnemyMovementComponent::SetSpriteDirection()
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
