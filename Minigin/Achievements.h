#pragma once
#include "Singleton.h"
#include "Observer.h"

namespace dae
{
	class Achievements : public Singleton<Achievements>, public Observer
	{
	public:
		virtual void Notify(Event event, GameObject* gameObject) override;
	private:
		bool SetAchievement(const char* ID);
	};
}
