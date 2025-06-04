#pragma once
#include "GameActorCommand.h"
namespace game
{
	class SpawnBombComponent;
	class ExplodeBombCommand : public RamCoreEngine::GameActorCommand
	{
	public:
		ExplodeBombCommand(RamCoreEngine::GameObject* actor);
		void Execute() override;
		void Start() override;

	private:
		SpawnBombComponent* m_pSpawnBombComponent;
	};
}
