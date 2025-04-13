#include "MovementCommand.h"
#include "GameObject.h"
#include "Timer.h"
#include "PlayerSpriteComponent.h"
#include "GridComponent.h"
#include "ColliderComponent.h"

dae::MoveCommand::MoveCommand(GameObject* actor) :
	GameActorCommand(actor),
	m_Speed{}
{
	m_pPlayerSpriteComponent = actor->GetComponent<PlayerSpriteComponent>();
	m_pGridComponent = actor->GetParent()->GetComponent<GridComponent>();
	m_pColliderComponent = actor->GetComponent<ColliderComponent>();
}

void dae::MoveCommand::Execute()
{
	glm::vec3 pos = GetGameActor()->GetWorldPosition();
	pos.x += m_Speed.x * Time::GetInstance().m_DeltaTime;
	pos.y += m_Speed.y * Time::GetInstance().m_DeltaTime;

	glm::vec3 posToCheck{ pos };
	//if (m_Speed.y != 0)
	//{
	//	if (m_Speed.y > 0)
	//	{
	//		posToCheck.y += m_pPlayerSpriteComponent->GetHeightSprite() / 2.5f;
	//	}
	//	else
	//	{
	//		posToCheck.y -= m_pPlayerSpriteComponent->GetHeightSprite() / 2.5f;
	//	}

	//	posToCheck.x += m_pPlayerSpriteComponent->GetWidthSprite() / 2.5f;
	//}
	//else if (m_Speed.x != 0)
	//{
	//	if (m_Speed.x > 0)
	//	{
	//		posToCheck.x += m_pPlayerSpriteComponent->GetWidthSprite() / 2.5f;
	//	}
	//	else
	//	{
	//		posToCheck.x -= m_pPlayerSpriteComponent->GetWidthSprite() / 2.5f;
	//	}

	//	posToCheck.y += m_pPlayerSpriteComponent->GetHeightSprite() / 2.5f;
	//}

	//if (m_pGridComponent->IsCellWalkable(posToCheck))
	//{
	//	GetGameActor()->SetWorldPosition(pos.x, pos.y);
	//	m_pPlayerSpriteComponent->SetDirectionSprite(m_Speed);
	//}
	
	//TODO: try to make it with collision box
	//GetGameActor()->SetWorldPosition(pos.x, pos.y);

	float colliderWidthHalf = m_pColliderComponent->GetColliderWidth() / 2;
	float colliderHeightHalf = m_pColliderComponent->GetColliderHeight() / 2;

	bool canMove{ true };

	glm::vec2 topLeft = { pos.x - colliderWidthHalf, pos.y - colliderHeightHalf };
	glm::vec2 topRight = { pos.x + colliderWidthHalf, pos.y - colliderHeightHalf };
	glm::vec2 bottomLeft = { pos.x - colliderWidthHalf, pos.y + colliderHeightHalf };
	glm::vec2 bottomRight = { pos.x + colliderWidthHalf, pos.y + colliderHeightHalf };

	if (!m_pGridComponent->IsCellWalkable(topLeft))
	{
		canMove = false;
	}
	else if (!m_pGridComponent->IsCellWalkable(topRight))
	{
		canMove = false;
	}
	else if (!m_pGridComponent->IsCellWalkable(bottomLeft))
	{
		canMove = false;
	}
	else if (!m_pGridComponent->IsCellWalkable(bottomRight))
	{
		canMove = false;
	}
	
	if (canMove)
	{
		GetGameActor()->SetWorldPosition(pos.x, pos.y);
		m_pPlayerSpriteComponent->SetDirectionSprite(m_Speed);
	}
}
