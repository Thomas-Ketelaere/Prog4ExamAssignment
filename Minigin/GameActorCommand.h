#pragma once
#include "Command.h"
namespace dae
{
	class GameObject;
	class GameActorCommand : public Command
	{
	public:
		GameActorCommand(GameObject* actor);
		//void SetButton(unsigned int button);

	protected:
		GameObject* GetGameActor() const { return m_GameActor; }

	private:
		GameObject* m_GameActor;
		unsigned int m_Button;
	};

}

