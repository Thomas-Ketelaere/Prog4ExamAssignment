#pragma once
#include "GameActorCommand.h"
namespace dae
{
	class LivesComponent;
	class LoseLiveCommand: public GameActorCommand
	{
	public:
		LoseLiveCommand(GameObject* actor);
		virtual void Execute() override;

		void Start() override {}

	private:
		LivesComponent* m_pLivesComponent;
	};

}


