#pragma once
#include "GameActorCommand.h"
#include <glm.hpp>
namespace game
{
	class PlayerSpriteComponent;
	class GridComponent;
	class PlayerCollider;
	class MoveCommand final : public RamCoreEngine::GameActorCommand
	{
	public:
		MoveCommand(RamCoreEngine::GameObject* actor, float footstepInterval);
		~MoveCommand() = default;
		MoveCommand(const MoveCommand& other) = delete;
		MoveCommand(MoveCommand&& other) = delete;
		MoveCommand& operator=(const MoveCommand& other) = delete;
		MoveCommand& operator=(MoveCommand&& other) = delete;

		virtual void Execute() override;
		void Start() override;

		void SetSpeed(glm::vec2 speed) { m_Speed = speed; }
	private:
		RamCoreEngine::GameObject* m_pOtherPlayer{};
		glm::vec2 m_Speed;
		PlayerSpriteComponent* m_pPlayerSpriteComponent;
		GridComponent* m_pGridComponent{};
		PlayerCollider* m_pColliderComponent;
		
		float m_AccumulatedTime{};
		const float m_FootstepInterval;
	};
}


