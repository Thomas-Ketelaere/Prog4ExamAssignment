#pragma once
#include <string>
#include <functional>
#include "Singleton.h"

namespace dae
{
	class Minigin
	{
	public:
		explicit Minigin(const std::string& dataPath);
		~Minigin();
		void Run(const std::function<void()>& load);

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;

	private:
		float& m_DeltaTime{ dae::Singleton<float>::GetInstance() };

		int m_MsPerFrame{ 16 }; //60 fps
		float m_FixedTimeStep{ 0.016f };
	};
}