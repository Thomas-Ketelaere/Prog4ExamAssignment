#pragma once
#include "GameActorCommand.h"
namespace game
{
	class GridComponent;
	class SpawnBombCommand : public RamCoreEngine::GameActorCommand
	{
	public:
		SpawnBombCommand(RamCoreEngine::GameObject* actor);
		void Execute() override;
		void Start() override;


	private:
		GridComponent* m_pGridComponent{};
	};
}

