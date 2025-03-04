#pragma once
#include "windows.h"
#include <Xinput.h>

namespace dae
{
	class Controller
	{
	public:
		Controller(int controllerIndex);
		void ProcessInputController();

		int GetControllerIndex() const { return m_ControllerIndex; }

		bool IsDownThisFrame(unsigned int button) const;
		bool IsUpThisFrame(unsigned int button) const;
		bool IsPressed(unsigned int button) const;

	private:
		
		XINPUT_STATE m_CurrentState;
		XINPUT_STATE m_PreviousState;

		int m_ControllerIndex;
		int m_ButtonsPressedThisFrame;
		int m_ButtonsReleasedThisFrame;
	};
}


