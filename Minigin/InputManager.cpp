#include <SDL.h>
#include "InputManager.h"
#include "imgui.h"
#include <backends/imgui_impl_sdl2.h>
#include "GameActorCommand.h"

void RamCoreEngine::InputManager::Start()
{
	for (int controllerIndex{}; controllerIndex < m_MaxControllers; ++controllerIndex)
	{
		auto controller = std::make_unique<Controller>(controllerIndex);
		m_ControllerVct.emplace_back(std::move(controller));
	}

	for (const auto& binding : m_GameBindingVct)
	{
		binding->m_GameBinding->Start();
	}
}

bool RamCoreEngine::InputManager::ProcessInput()
{
	//GamePad
	for (const auto& controller : m_ControllerVct)
	{
		controller->ProcessInputController();
		int controllerIndex = controller->GetControllerIndex();

		for (const auto& binding : m_GameBindingVct)
		{
			if (binding->m_ControllerIndex == controllerIndex)
			{
				switch (binding->m_KeyState)
				{
				case KeyState::Pressed:
					if (controller->IsPressed(binding->m_KeyBinding))
					{
						binding->m_GameBinding->Execute();
					}
					break;
				case KeyState::Down:
					if (controller->IsDownThisFrame(binding->m_KeyBinding))
					{
						binding->m_GameBinding->Execute();
					}
					break;
				case KeyState::Up:
					if (controller->IsUpThisFrame(binding->m_KeyBinding))
					{
						binding->m_GameBinding->Execute();
					}
					break;
				}
			}
		}
	}

	//SDL
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			return false;
		}

		for (const auto& binding : m_GameBindingVct)
		{
			if (binding->m_ControllerIndex == -1) // controller index is -1 when it's on keyboard
			{
				if (e.key.keysym.sym != static_cast<SDL_KeyCode>(binding->m_KeyBinding)) continue; //check if the right button is pressed

				switch (binding->m_KeyState)
				{
				case KeyState::Down:
					if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
					{
						binding->m_GameBinding->Execute();
					}
					break;
				case KeyState::Up:
					if (e.type == SDL_KEYUP)
					{
						binding->m_GameBinding->Execute();
					}
					break;
				}

				//process event for ImGui
				ImGui_ImplSDL2_ProcessEvent(&e);
			}
		}
	}
	
	// this will check if the button is getting held down (by checking every loop if it is pressed or not)
	const Uint8* keyStates = SDL_GetKeyboardState(NULL);
	for (const auto& binding : m_GameBindingVct)
	{
		if (binding->m_ControllerIndex == -1)
		{
			if (binding->m_KeyState != KeyState::Pressed) continue; 

			if (keyStates[SDL_GetScancodeFromKey(binding->m_KeyBinding)])
			{
				binding->m_GameBinding->Execute();
			}
		}
	}

	return true;
}

void RamCoreEngine::InputManager::AddBinding(std::unique_ptr<Command> binding, KeyState keyState, unsigned int keyBind, int controllerIndex)
{
	auto newBinding = std::make_unique<BindingStates>();
	newBinding->m_GameBinding = std::move(binding);
	newBinding->m_KeyState = keyState;
	newBinding->m_KeyBinding = keyBind;
	newBinding->m_ControllerIndex = controllerIndex;

	m_GameBindingVct.emplace_back(std::move(newBinding));
}

void RamCoreEngine::InputManager::ClearBindings()
{
	m_GameBindingVct.clear();
	m_ControllerVct.clear();
}

void RamCoreEngine::InputManager::SetControllerRumble(int index, float percentLeft, float percentRight)
{
	m_ControllerVct[index]->SetControllerRumble(percentLeft, percentRight);
}
