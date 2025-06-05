#pragma once
#include "GameActorCommand.h"
#include <glm.hpp>
namespace game
{
	class PlayerSpriteComponent;
	class GridComponent;
	class PlayerCollider;
	class MoveCommand : public RamCoreEngine::GameActorCommand
	{
	public:
		MoveCommand(RamCoreEngine::GameObject* actor);
		virtual void Execute() override;
		void Start() override;

		void SetSpeed(glm::vec2 speed) { m_Speed = speed; }
	private:
		RamCoreEngine::GameObject* m_pOtherPlayer{};
		glm::vec2 m_Speed;
		PlayerSpriteComponent* m_pPlayerSpriteComponent;
		GridComponent* m_pGridComponent{};
		PlayerCollider* m_pColliderComponent;
		
	};
}


