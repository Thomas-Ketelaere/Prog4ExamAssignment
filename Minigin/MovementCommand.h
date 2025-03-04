#pragma once
#include "GameActorCommand.h"
namespace dae
{
	class MovementComponent;
	class MoveLeftCommand : public GameActorCommand
	{
	public:
		MoveLeftCommand(GameObject* actor);
		virtual void Execute() override;

		void SetSpeed(float speed) { m_Speed = speed; }
	private:
		float m_Speed;
	};

	class MoveRightCommand : public GameActorCommand
	{
	public:
		MoveRightCommand(GameObject* actor);
		virtual void Execute() override;

		void SetSpeed(float speed) { m_Speed = speed; }
	private:
		float m_Speed;
	};

	class MoveUpCommand : public GameActorCommand
	{
	public:
		MoveUpCommand(GameObject* actor);
		virtual void Execute() override;

		void SetSpeed(float speed) { m_Speed = speed; }
	private:
		float m_Speed;
	};

	class MoveDownCommand : public GameActorCommand
	{
	public:
		MoveDownCommand(GameObject* actor);
		virtual void Execute() override;

		void SetSpeed(float speed) { m_Speed = speed; }
	private:
		float m_Speed;
	};
}


