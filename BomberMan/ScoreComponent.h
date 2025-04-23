#pragma once
#include <memory>
#include "Component.h"
#include "Observer.h"

namespace dae
{
	class Subject;
	class ScoreComponent : public Component, public Observer
	{
	public:
		ScoreComponent(GameObject* gameObject);

		void GainScore(int amount);

		virtual void Notify(Event event, GameObject* gameObject) override;

		Subject* GetActorScoreSubject() const { return m_pActorScoreEvent.get(); }
		int GetCurrentScore() { return m_CurrentScore; }
	private:
		int m_CurrentScore{};
		std::unique_ptr<Subject> m_pActorScoreEvent;
	};
}


