#include "MovementCommand.h"
#include "GameObject.h"
#include "Timer.h"

dae::MoveCommand::MoveCommand(GameObject* actor) :
	GameActorCommand(actor),
	m_Speed{}
{

}

void dae::MoveCommand::Execute()
{
	auto pos = GetGameActor()->GetWorldPosition();
	pos.x += m_Speed.x * Time::GetInstance().m_DeltaTime;
	pos.y += m_Speed.y * Time::GetInstance().m_DeltaTime;
	GetGameActor()->SetWorldPosition(pos.x, pos.y);
}
