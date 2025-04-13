#include "EnemyMovementComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "GridComponent.h"
#include "Timer.h"
#include "Renderer.h"

dae::EnemyMovementComponent::EnemyMovementComponent(GameObject* gameObject, const float speed):
	Component(gameObject),
	m_Speed{speed}
{
	m_pGridComponent = GetGameObject()->GetParent()->GetComponent<GridComponent>();
	m_Path.emplace_back(GetTransform()->GetWorldPosition());
}

void dae::EnemyMovementComponent::Start()
{
	m_pGridComponent->GetPath(m_Path, glm::vec2(848, 48));
}

void dae::EnemyMovementComponent::Update()
{
	glm::vec2 pos = GetTransform()->GetWorldPosition();
	if (glm::distance(pos, m_Path[m_PathIndex]) <= m_DistanceToReachPoint)
	{
		++m_PathIndex;
		if (m_PathIndex == m_Path.size())
		{
			m_PathIndex = 0;
			//new path
		}
		
	}

	else
	{
		glm::vec2 direction = m_Path[m_PathIndex] - pos;
		glm::vec2 dirNorm = glm::normalize(direction);

		pos += m_Speed * dirNorm * Time::GetInstance().m_DeltaTime;

		GetGameObject()->SetWorldPosition(pos.x, pos.y);
	}
}

void dae::EnemyMovementComponent::Render() const
{
	if (m_DebugRender)
	{
		glm::vec2 pos = GetTransform()->GetWorldPosition();
		SDL_Color color = { 0, 0, 255, 255 };
		Renderer::GetInstance().FillRectangle(pos.x, pos.y, 20.f, 20.f, color);
		for (int pathCounter{}; pathCounter < m_Path.size() - 1; ++pathCounter)
		{
			glm::vec2 pointOne = m_Path[pathCounter];
			glm::vec2 pointTwo = m_Path[pathCounter + 1];
			Renderer::GetInstance().DrawLine(pointOne.x, pointOne.y, pointTwo.x, pointTwo.y, color);
		}
	}
}
