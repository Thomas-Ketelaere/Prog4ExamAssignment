#pragma once
#include "Singleton.h"
#include <string>

namespace dae
{
	class Achievements : public Singleton<Achievements>
	{
	public:
		bool SetAchievement(const char* ID);
	private:
		friend class Singleton<Achievements>;
		Achievements() = default;
		
	};
}
