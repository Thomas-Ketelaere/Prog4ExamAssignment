#pragma once
#include "Singleton.h"
#include <vector>
#include "Controller.h"
#include "GameActorCommand.h"
#include <memory>
#pragma comment(lib, "xinput.lib")

namespace dae
{

	enum class KeyState
	{
		Pressed,
		Up,
		Down
	};

	struct BindingStates
	{
		std::unique_ptr<GameActorCommand> m_GameBinding{ nullptr };
		KeyState m_KeyState{};
		unsigned int m_KeyBinding{};
		int m_ControllerIndex{};
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		void Start();
		bool ProcessInput();
		//template <typename Binding> Binding* AddBinding();
		void AddBinding(std::unique_ptr<GameActorCommand> binding, KeyState keyState, unsigned int keyBind, int controllerIndex);

	private:
		std::vector<std::unique_ptr<Controller>> m_ControllerVct;
		std::vector<std::unique_ptr<BindingStates>> m_GameBindingVct;

		const int m_MaxControllers{ 4 };
		
	};

}
