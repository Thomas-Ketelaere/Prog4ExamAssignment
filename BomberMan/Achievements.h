#pragma once
#include "Singleton.h"
#include "Observer.h"

namespace game
{
	class Achievements : public RamCoreEngine::Singleton<Achievements>, public RamCoreEngine::Observer
	{
	public:
		virtual void Notify(Event event, RamCoreEngine::GameObject* gameObject) override;
	private:
		void SetAchievement(const char* ID);
	};
}
