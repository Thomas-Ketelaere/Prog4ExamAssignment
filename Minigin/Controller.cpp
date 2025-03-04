#include "Controller.h"


dae::Controller::Controller(int controllerIndex) :
	m_ControllerIndex{ controllerIndex },
	m_ButtonsPressedThisFrame{},
	m_ButtonsReleasedThisFrame{},
	m_PreviousState{},
	m_CurrentState{}
{

}

void dae::Controller::ProcessInputController()
{
	//XInput
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(m_CurrentState));
	XInputGetState(m_ControllerIndex, &m_CurrentState);

	auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
	m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
}

bool dae::Controller::IsDownThisFrame(unsigned int button) const
{
	return m_ButtonsPressedThisFrame & button;
}

bool dae::Controller::IsUpThisFrame(unsigned int button) const
{
	return m_ButtonsReleasedThisFrame & button;
}

bool dae::Controller::IsPressed(unsigned int button) const
{
	return m_CurrentState.Gamepad.wButtons & button;
}

