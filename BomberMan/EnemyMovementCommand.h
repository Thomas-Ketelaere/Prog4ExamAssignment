#pragma once
#include "GameActorCommand.h"
#include <glm.hpp>
namespace game
{
	class EnemyMovementComponent;
	class EnemyMovementCommand final : public RamCoreEngine::GameActorCommand
	{
	public:
		EnemyMovementCommand(RamCoreEngine::GameObject* actor);
		~EnemyMovementCommand() = default;
		EnemyMovementCommand(const EnemyMovementCommand& other) = delete;
		EnemyMovementCommand(EnemyMovementCommand&& other) = delete;
		EnemyMovementCommand& operator=(const EnemyMovementCommand& other) = delete;
		EnemyMovementCommand& operator=(EnemyMovementCommand&& other) = delete;

		virtual void Execute() override;

		void SetDirection(glm::vec2 direction) { m_Direction = direction; }
	private:
		glm::vec2 m_Direction{};
		EnemyMovementComponent* m_pEnemyMovementComp{};
	};
}