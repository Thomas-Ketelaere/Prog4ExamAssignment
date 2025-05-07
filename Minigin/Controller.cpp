#include "Controller.h"
#include "windows.h"
#include <Xinput.h>

class RamCoreEngine::Controller::ControllerImpl
{
public:
	ControllerImpl(int controllerIndex): 
		m_ControllerIndex{ controllerIndex }, 
		m_ButtonsPressedThisFrame{}, 
		m_ButtonsReleasedThisFrame{}
	{
	}

	void ProcessInputController()
	{
		CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(m_CurrentState));
		XInputGetState(m_ControllerIndex, &m_CurrentState);

		auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
		m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
	}

	int GetControllerIndex() const { return m_ControllerIndex; }

	bool IsDownThisFrame(unsigned int button) const { return (m_ButtonsPressedThisFrame & button); }
	bool IsUpThisFrame(unsigned int button) const { return (m_ButtonsReleasedThisFrame & button); }
	bool IsPressed(unsigned int button) const { return (m_CurrentState.Gamepad.wButtons & button); }

private:
	XINPUT_STATE m_CurrentState{};
	XINPUT_STATE m_PreviousState{};
	int m_ControllerIndex;
	int m_ButtonsPressedThisFrame;
	int m_ButtonsReleasedThisFrame;
};

RamCoreEngine::Controller::Controller(int controllerIndex) :
	m_pImpl{ std::make_unique<ControllerImpl>(controllerIndex) }
{
}

RamCoreEngine::Controller::~Controller() = default;

void RamCoreEngine::Controller::ProcessInputController()
{
	m_pImpl->ProcessInputController();
}

int RamCoreEngine::Controller::GetControllerIndex() const
{
	return m_pImpl->GetControllerIndex();
}

bool RamCoreEngine::Controller::IsDownThisFrame(unsigned int button) const
{
	return m_pImpl->IsDownThisFrame(button);
}

bool RamCoreEngine::Controller::IsUpThisFrame(unsigned int button) const
{
	return m_pImpl->IsUpThisFrame(button);
}

bool RamCoreEngine::Controller::IsPressed(unsigned int button) const
{
	return m_pImpl->IsPressed(button);
}

