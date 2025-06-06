#pragma once
#include "Command.h"
namespace RamCoreEngine
{
	class GameObject;
	class GameActorCommand : public Command
	{
	public:
		GameActorCommand(GameObject* actor);
		~GameActorCommand() = default;
		GameActorCommand(const GameActorCommand& other) = delete;
		GameActorCommand(GameActorCommand&& other) = delete;
		GameActorCommand& operator=(const GameActorCommand& other) = delete;
		GameActorCommand& operator=(GameActorCommand&& other) = delete;
	protected:
		GameObject* GetGameActor() const { return m_GameActor; }
	private:
		GameObject* m_GameActor;
	};

}

