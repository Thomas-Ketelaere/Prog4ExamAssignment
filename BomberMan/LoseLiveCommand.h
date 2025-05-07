#pragma once
#include "GameActorCommand.h"
namespace game
{
	class LivesComponent;
	class LoseLiveCommand: public RamCoreEngine::GameActorCommand
	{
	public:
		LoseLiveCommand(RamCoreEngine::GameObject* actor);
		virtual void Execute() override;

		void Start() override {}

	private:
		LivesComponent* m_pLivesComponent;
	};

}


