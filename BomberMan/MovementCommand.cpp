#include "MovementCommand.h"
#include "GameObject.h"
#include "Timer.h"
#include "PlayerSpriteComponent.h"
#include "GridComponent.h"

dae::MoveCommand::MoveCommand(GameObject* actor) :
	GameActorCommand(actor),
	m_Speed{}
{
	m_pPlayerSpriteComponent = actor->GetComponent<PlayerSpriteComponent>();
	m_pGridComponent = actor->GetParent()->GetComponent<GridComponent>();
}

void dae::MoveCommand::Execute()
{
	glm::vec3 pos = GetGameActor()->GetWorldPosition();
	pos.x += m_Speed.x * Time::GetInstance().m_DeltaTime;
	pos.y += m_Speed.y * Time::GetInstance().m_DeltaTime;

	glm::vec3 posToCheck{ pos };
	if (m_Speed.y != 0)
	{
		if (m_Speed.y > 0)
		{
			posToCheck.y += m_pPlayerSpriteComponent->GetHeightSprite();
		}

		posToCheck.x += m_pPlayerSpriteComponent->GetWidthSprite() / 2;
	}
	else if (m_Speed.x != 0)
	{
		if (m_Speed.x > 0)
		{
			posToCheck.x += m_pPlayerSpriteComponent->GetWidthSprite();
		}

		posToCheck.y += m_pPlayerSpriteComponent->GetHeightSprite() / 2;
	}

	if (m_pGridComponent->IsCellWalkable(posToCheck))
	{
		GetGameActor()->SetWorldPosition(pos.x, pos.y);
		m_pPlayerSpriteComponent->SetDirectionSprite(m_Speed);
	}
}
