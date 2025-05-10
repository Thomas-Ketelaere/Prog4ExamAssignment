#pragma once
#include "GameActorCommand.h"
#include <glm.hpp>


namespace game
{
	class OnScreenKeyboardComponent;
	class OnScreenKeyboardCommand : public RamCoreEngine::GameActorCommand
	{
	public:
		OnScreenKeyboardCommand(RamCoreEngine::GameObject* actor);

		void Start() override {};
		void Execute() override;

		void SetDirection(glm::vec2 direction) { m_Direction = direction; }

	private:
		OnScreenKeyboardComponent* m_pKeyboardComp{};
		glm::vec2 m_Direction{};
	};
}


