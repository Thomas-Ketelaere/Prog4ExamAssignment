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
		~LivesComponent() = default;
		LivesComponent(const LivesComponent& other) = delete;
		LivesComponent(LivesComponent&& other) = delete;
		LivesComponent& operator=(const LivesComponent& other) = delete;
		LivesComponent& operator=(LivesComponent&& other) = delete;

		void LoseLive();
		int GetLives() const { return m_CurrentLives; }
		RamCoreEngine::Subject* GetActorDiedSubject() const { return m_pActorDiedEvent.get(); }
	private:
		int m_CurrentLives;
		std::unique_ptr<RamCoreEngine::Subject> m_pActorDiedEvent;
	};

}

