#pragma once
#include "GameActorCommand.h"
#include <memory>
namespace dae
{
	class LivesComponent;
	class LoseLiveCommand: public GameActorCommand
	{
	public:
		LoseLiveCommand(GameObject* actor);
		virtual void Execute() override;

	private:
		LivesComponent* m_pLivesComponent;
	};

}


