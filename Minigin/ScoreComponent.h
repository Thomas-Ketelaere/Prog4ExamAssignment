#pragma once
#include <memory>
#include "Component.h"
namespace dae
{
	class Subject;
	class ScoreComponent : public Component
	{
	public:
		ScoreComponent(GameObject* gameObject);

		void GainScore(int amount);

		Subject* GetActorScoreSubject() const { return m_pActorScoreEvent.get(); }
		int GetCurrentScore() { return m_CurrentScore; }
	private:
		int m_CurrentScore{};
		int m_ScoreToWin{ 500 };
		std::unique_ptr<Subject> m_pActorScoreEvent;
	};
}


