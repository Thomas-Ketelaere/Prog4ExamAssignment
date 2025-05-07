#pragma once
#include "Command.h"
namespace RamCoreEngine
{
	class GameObject;
	class GameActorCommand : public Command
	{
	public:
		GameActorCommand(GameObject* actor);
	protected:
		GameObject* GetGameActor() const { return m_GameActor; }
	private:
		GameObject* m_GameActor;
	};

}

