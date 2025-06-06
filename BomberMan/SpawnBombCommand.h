#pragma once
#include "GameActorCommand.h"
namespace game
{
	class SpawnBombComponent;
	class SpawnBombCommand final : public RamCoreEngine::GameActorCommand
	{
	public:
		SpawnBombCommand(RamCoreEngine::GameObject* actor);
		~SpawnBombCommand() = default;
		SpawnBombCommand(const SpawnBombCommand& other) = delete;
		SpawnBombCommand(SpawnBombCommand&& other) = delete;
		SpawnBombCommand& operator=(const SpawnBombCommand& other) = delete;
		SpawnBombCommand& operator=(SpawnBombCommand&& other) = delete;

		void Execute() override;

	private:
		SpawnBombComponent* m_pSpawnBombComponent;
	};
}

