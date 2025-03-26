#include "MovementCommand.h"
#include "GameObject.h"
#include "Timer.h"
#include "SpriteSheetComponent.h"

dae::MoveCommand::MoveCommand(GameObject* actor) :
	GameActorCommand(actor),
	m_Speed{}
{
	m_pSpriteSheetComponent = actor->GetComponent<SpriteSheetComponent>();
}

void dae::MoveCommand::Execute()
{
	auto pos = GetGameActor()->GetWorldPosition();
	pos.x += m_Speed.x * Time::GetInstance().m_DeltaTime;
	pos.y += m_Speed.y * Time::GetInstance().m_DeltaTime;
	GetGameActor()->SetWorldPosition(pos.x, pos.y);
	m_pSpriteSheetComponent->SetDirectionSprite(m_Speed);
}
