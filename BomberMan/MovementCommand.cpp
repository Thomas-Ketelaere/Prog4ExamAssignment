#include "MovementCommand.h"
#include "GameObject.h"
#include "Timer.h"
#include "PlayerSpriteComponent.h"
#include "GridComponent.h"
#include "PlayerCollider.h"
#include "SceneManager.h"
#include "Hash.h"
#include "GameManager.h"

game::MoveCommand::MoveCommand(RamCoreEngine::GameObject* actor) :
	GameActorCommand(actor),
	m_Speed{}
{
	m_pPlayerSpriteComponent = actor->GetComponent<PlayerSpriteComponent>();
	m_pColliderComponent = actor->GetComponent<PlayerCollider>();
}

void game::MoveCommand::Start()
{
	RamCoreEngine::GameObject* gridObject = RamCoreEngine::SceneManager::GetInstance().GetCurrentScene()->GetFirstObjectWithTag(make_sdbm_hash("Grid"));
	m_pGridComponent = gridObject->GetComponent<GridComponent>();
	if (GameManager::GetInstance().GetGameMode() == GameMode::Coop)
	{
		std::vector<RamCoreEngine::GameObject*> players = RamCoreEngine::SceneManager::GetInstance().GetCurrentScene()->GetAllObjectsWithTag(make_sdbm_hash("Player"));
		auto it = std::find_if(players.begin(), players.end(), [&](RamCoreEngine::GameObject* player)
			{
				return player != GetGameActor();
			});

		if (it != players.end())
		{
			m_pOtherPlayer = *it;
		}
	}
	
}


void game::MoveCommand::Execute()
{
	glm::vec3 pos = GetGameActor()->GetLocalPosition();
	pos.x += m_Speed.x * RamCoreEngine::Time::GetInstance().m_DeltaTime;
	pos.y += m_Speed.y * RamCoreEngine::Time::GetInstance().m_DeltaTime;

	glm::vec3 posToCheck{ pos };

	float colliderWidthHalf = m_pColliderComponent->GetColliderWidth() / 2;
	float colliderHeightHalf = m_pColliderComponent->GetColliderHeight() / 2;

	bool canMove{ true };

	glm::vec2 topLeft = { pos.x - colliderWidthHalf, pos.y - colliderHeightHalf };
	glm::vec2 topRight = { pos.x + colliderWidthHalf, pos.y - colliderHeightHalf };
	glm::vec2 bottomLeft = { pos.x - colliderWidthHalf, pos.y + colliderHeightHalf };
	glm::vec2 bottomRight = { pos.x + colliderWidthHalf, pos.y + colliderHeightHalf };

	//tried to also for perfomance do last index and check if it changed, but hitbox is bigger and not just position so wont work
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
		glm::vec2 posToCheck2 = { GetGameActor()->GetWorldPosition().x, GetGameActor()->GetWorldPosition().y };
		if (m_pGridComponent->ShouldGridMove(posToCheck2, m_Speed.x))
		{
			glm::vec3 gridPos = m_pGridComponent->GetGameObject()->GetWorldPosition();
			glm::vec2 gridMovement = -m_Speed * RamCoreEngine::Time::GetInstance().m_DeltaTime;

			gridPos.x += gridMovement.x;

			m_pGridComponent->GetGameObject()->SetLocalPosition(gridPos);

			if (m_pOtherPlayer != nullptr) //no check in game manager for game mode cause it will always be null if it's not coop
			{
				glm::vec3 otherPlayerPos = m_pOtherPlayer->GetLocalPosition();
				glm::vec3 newOtherPlayerPos{};
				newOtherPlayerPos.x = otherPlayerPos.x + gridMovement.x;
				newOtherPlayerPos.y = otherPlayerPos.y;
				m_pOtherPlayer->SetLocalPosition(newOtherPlayerPos);
			}
		}
		else
		{
			GetGameActor()->SetLocalPosition(glm::vec3(pos.x, pos.y, 0.f));
		}
		m_pPlayerSpriteComponent->SetDirectionSprite(m_Speed);
	}
}

