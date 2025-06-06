#pragma once
#include "GameActorCommand.h"
namespace game
{
	class SpawnBombComponent;
	class ExplodeBombCommand final : public RamCoreEngine::GameActorCommand
	{
	public:
		ExplodeBombCommand(RamCoreEngine::GameObject* actor);
		~ExplodeBombCommand() = default;
		ExplodeBombCommand(const ExplodeBombCommand& other) = delete;
		ExplodeBombCommand(ExplodeBombCommand&& other) = delete;
		ExplodeBombCommand& operator=(const ExplodeBombCommand& other) = delete;
		ExplodeBombCommand& operator=(ExplodeBombCommand&& other) = delete;

		void Execute() override;

	private:
		SpawnBombComponent* m_pSpawnBombComponent;
	};
}
