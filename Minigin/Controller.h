#pragma once
#include <memory>

namespace RamCoreEngine
{
	class Controller
	{
	public:
		Controller(int controllerIndex);
		~Controller();

		void ProcessInputController();
		int GetControllerIndex() const;

		bool IsDownThisFrame(unsigned int button) const;
		bool IsUpThisFrame(unsigned int button) const;
		bool IsPressed(unsigned int button) const;

	private:
		class ControllerImpl;
		std::unique_ptr<ControllerImpl> m_pImpl;
	};
}


