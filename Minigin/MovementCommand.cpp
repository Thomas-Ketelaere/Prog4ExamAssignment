#include "MovementCommand.h"
#include "GameObject.h"
#include "Time.h"

dae::MoveLeftCommand::MoveLeftCommand(GameObject* actor) :
	GameActorCommand(actor),
	m_Speed{}
{
	
}

void dae::MoveLeftCommand::Execute()
{
	auto pos = GetGameActor()->GetWorldPosition();
	pos.x -= m_Speed * Time::GetInstance().m_DeltaTime;
	GetGameActor()->SetWorldPosition(pos.x, pos.y);
}

dae::MoveRightCommand::MoveRightCommand(GameObject* actor) :
	GameActorCommand(actor),
	m_Speed{}
{

}

void dae::MoveRightCommand::Execute()
{
	auto pos = GetGameActor()->GetWorldPosition();
	pos.x += m_Speed * Time::GetInstance().m_DeltaTime;
	GetGameActor()->SetWorldPosition(pos.x, pos.y);
}

dae::MoveUpCommand::MoveUpCommand(GameObject* actor) :
	GameActorCommand(actor),
	m_Speed{}
{
}

void dae::MoveUpCommand::Execute()
{
	auto pos = GetGameActor()->GetWorldPosition();
	pos.y -= m_Speed * Time::GetInstance().m_DeltaTime;
	GetGameActor()->SetWorldPosition(pos.x, pos.y);
}

dae::MoveDownCommand::MoveDownCommand(GameObject* actor) :
	GameActorCommand(actor),
	m_Speed{}
{
}

void dae::MoveDownCommand::Execute()
{
	auto pos = GetGameActor()->GetWorldPosition();
	pos.y += m_Speed * Time::GetInstance().m_DeltaTime;
	GetGameActor()->SetWorldPosition(pos.x, pos.y);
}
