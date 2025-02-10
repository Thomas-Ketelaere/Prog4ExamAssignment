#pragma once
#include "Singleton.h"

namespace dae
{
	class Time final : public Singleton<Time>
	{
	public:
		static float m_DeltaTime;

	private:
		friend class Singleton<Time>;
		Time() = default;
	};
}


