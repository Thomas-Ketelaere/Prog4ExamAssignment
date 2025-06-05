#pragma once
#include "GameActorCommand.h"
#include <glm.hpp>
namespace game
{
	class EnemyMovementComponent;
	class EnemyMovementCommand : public RamCoreEngine::GameActorCommand
	{
	public:
		EnemyMovementCommand(RamCoreEngine::GameObject* actor);
		virtual void Execute() override;
		void Start() override {}

		void SetDirection(glm::vec2 direction) { m_Direction = direction; }
	private:
		glm::vec2 m_Direction{};
		EnemyMovementComponent* m_pEnemyMovementComp{};
	};
}