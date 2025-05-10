#pragma once
#include "GameActorCommand.h"
namespace game
{
	class OnScreenKeyboardComponent;
	class PressScreenKeyboardCommand : public RamCoreEngine::GameActorCommand
	{
	public:
		PressScreenKeyboardCommand(RamCoreEngine::GameObject* actor);
		void Execute() override;

		void Start() override {}

		void SetShouldRemove(bool shouldRemove) { m_ShouldRemove = shouldRemove; }

	private:
		bool m_ShouldRemove{};
		OnScreenKeyboardComponent* m_pKeyboardComp{};
	};
}

