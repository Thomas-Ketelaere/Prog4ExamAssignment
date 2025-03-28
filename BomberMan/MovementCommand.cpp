#include "MovementCommand.h"
#include "GameObject.h"
#include "Timer.h"
#include "SpriteSheetComponent.h"
#include "GridComponent.h"

dae::MoveCommand::MoveCommand(GameObject* actor) :
	GameActorCommand(actor),
	m_Speed{}
{
	m_pSpriteSheetComponent = actor->GetComponent<SpriteSheetComponent>();
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
			posToCheck.y += m_pSpriteSheetComponent->GetHeightSprite();
		}

		posToCheck.x += m_pSpriteSheetComponent->GetWidthSprite() / 2;
	}
	else if (m_Speed.x != 0)
	{
		if (m_Speed.x > 0)
		{
			posToCheck.x += m_pSpriteSheetComponent->GetWidthSprite();
		}

		posToCheck.y += m_pSpriteSheetComponent->GetHeightSprite() / 2;
	}

	

	if (m_pGridComponent->IsCellWalkable(posToCheck))
	{
		GetGameActor()->SetWorldPosition(pos.x, pos.y);
		m_pSpriteSheetComponent->SetDirectionSprite(m_Speed);
	}
	
	
}
