#pragma once
#include "GameActorCommand.h"
namespace game
{
	class OnScreenKeyboardComponent;
	class PressScreenKeyboardCommand final : public RamCoreEngine::GameActorCommand
	{
	public:
		PressScreenKeyboardCommand(RamCoreEngine::GameObject* actor);
		~PressScreenKeyboardCommand() = default;
		PressScreenKeyboardCommand(const PressScreenKeyboardCommand& other) = delete;
		PressScreenKeyboardCommand(PressScreenKeyboardCommand&& other) = delete;
		PressScreenKeyboardCommand& operator=(const PressScreenKeyboardCommand& other) = delete;
		PressScreenKeyboardCommand& operator=(PressScreenKeyboardCommand&& other) = delete;

		void Execute() override;

		void SetShouldRemove(bool shouldRemove) { m_ShouldRemove = shouldRemove; }

	private:
		bool m_ShouldRemove{};
		OnScreenKeyboardComponent* m_pKeyboardComp{};
	};
}

