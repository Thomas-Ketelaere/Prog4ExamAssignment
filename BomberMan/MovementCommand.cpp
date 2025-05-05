#include "MovementCommand.h"
#include "GameObject.h"
#include "Timer.h"
#include "PlayerSpriteComponent.h"
#include "GridComponent.h"
#include "PlayerCollider.h"
#include "SceneManager.h"
#include "Hash.h"

dae::MoveCommand::MoveCommand(GameObject* actor) :
	GameActorCommand(actor),
	m_Speed{}
{
	m_pPlayerSpriteComponent = actor->GetComponent<PlayerSpriteComponent>();
	m_pColliderComponent = actor->GetComponent<PlayerCollider>();
}

void dae::MoveCommand::Execute()
{
	glm::vec3 pos = GetGameActor()->GetWorldPosition();
	pos.x += m_Speed.x * Time::GetInstance().m_DeltaTime;
	pos.y += m_Speed.y * Time::GetInstance().m_DeltaTime;

	glm::vec3 posToCheck{ pos };

	float colliderWidthHalf = m_pColliderComponent->GetColliderWidth() / 2;
	float colliderHeightHalf = m_pColliderComponent->GetColliderHeight() / 2;

	bool canMove{ true };

	glm::vec2 topLeft = { pos.x - colliderWidthHalf, pos.y - colliderHeightHalf };
	glm::vec2 topRight = { pos.x + colliderWidthHalf, pos.y - colliderHeightHalf };
	glm::vec2 bottomLeft = { pos.x - colliderWidthHalf, pos.y + colliderHeightHalf };
	glm::vec2 bottomRight = { pos.x + colliderWidthHalf, pos.y + colliderHeightHalf };

	if (!m_pGridComponent->IsCellWalkable(topLeft, true))
	{
		canMove = false;
	}
	else if (!m_pGridComponent->IsCellWalkable(topRight, true))
	{
		canMove = false;
	}
	else if (!m_pGridComponent->IsCellWalkable(bottomLeft, true))
	{
		canMove = false;
	}
	else if (!m_pGridComponent->IsCellWalkable(bottomRight, true))
	{
		canMove = false;
	}
	
	if (canMove)
	{
		GetGameActor()->SetWorldPosition(pos.x, pos.y);
		m_pPlayerSpriteComponent->SetDirectionSprite(m_Speed);
	}
}

void dae::MoveCommand::Start()
{
	GameObject* gridObject = SceneManager::GetInstance().GetCurrentScene()->GetFirstObjectWithTag(make_sdbm_hash("Grid"));
	m_pGridComponent = gridObject->GetComponent<GridComponent>();
}
