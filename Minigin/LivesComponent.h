#pragma once
#include "Component.h"
#include <memory>

namespace dae
{
	class Subject;
	class LivesComponent final: public Component
	{
	public:
		LivesComponent(GameObject* gameObject, int maxLives);

		void LoseLive();
		int GetLives() const { return m_CurrentLives; }
		Subject* GetActorDiedSubject() const { return m_pActorDiedEvent.get(); }
	private:
		int m_CurrentLives;
		std::unique_ptr<Subject> m_pActorDiedEvent;
	};

}

