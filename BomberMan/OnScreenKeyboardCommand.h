#pragma once
#include "GameActorCommand.h"
#include <glm.hpp>


namespace game
{
	class OnScreenKeyboardComponent;
	class OnScreenKeyboardCommand final : public RamCoreEngine::GameActorCommand
	{
	public:
		OnScreenKeyboardCommand(RamCoreEngine::GameObject* actor);
		~OnScreenKeyboardCommand() = default;
		OnScreenKeyboardCommand(const OnScreenKeyboardCommand& other) = delete;
		OnScreenKeyboardCommand(OnScreenKeyboardCommand&& other) = delete;
		OnScreenKeyboardCommand& operator=(const OnScreenKeyboardCommand& other) = delete;
		OnScreenKeyboardCommand& operator=(OnScreenKeyboardCommand&& other) = delete;

		void Execute() override;

		void SetDirection(glm::vec2 direction) { m_Direction = direction; }

	private:
		OnScreenKeyboardComponent* m_pKeyboardComp{};
		glm::vec2 m_Direction{};
	};
}


