#pragma once
#include "Component.h"
#include <memory>

namespace RamCoreEngine
{
	class Subject;
}

namespace game
{
	
	class LivesComponent final: public RamCoreEngine::Component
	{
	public:
		LivesComponent(RamCoreEngine::GameObject* gameObject, int maxLives);

		void LoseLive();
		int GetLives() const { return m_CurrentLives; }
		RamCoreEngine::Subject* GetActorDiedSubject() const { return m_pActorDiedEvent.get(); }
	private:
		int m_CurrentLives;
		std::unique_ptr<RamCoreEngine::Subject> m_pActorDiedEvent;
	};

}

