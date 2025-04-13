#pragma once
#include "GameActorCommand.h"
#include <glm.hpp>
namespace dae
{
	class PlayerSpriteComponent;
	class GridComponent;
	class ColliderComponent;
	class MoveCommand : public GameActorCommand
	{
	public:
		MoveCommand(GameObject* actor);
		virtual void Execute() override;

		void SetSpeed(glm::vec2 speed) { m_Speed = speed; }
	private:
		glm::vec2 m_Speed;
		PlayerSpriteComponent* m_pPlayerSpriteComponent;
		GridComponent* m_pGridComponent;
		ColliderComponent* m_pColliderComponent;
	};
}


