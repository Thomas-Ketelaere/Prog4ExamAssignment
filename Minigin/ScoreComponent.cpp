#include "ScoreComponent.h"
#include "Subject.h"
#include "Achievements.h"

dae::ScoreComponent::ScoreComponent(GameObject* gameObject):
	Component(gameObject)
{
	m_pActorScoreEvent = std::make_unique<Subject>();
}

void dae::ScoreComponent::GainScore(int amount)
{
	m_CurrentScore += amount;
	m_pActorScoreEvent->NotifyObservers(Event::PlayerGainedScore, GetGameObject());

	if (m_CurrentScore >= m_ScoreToWin)
	{
		Achievements::GetInstance().SetAchievement("ACH_WIN_ONE_GAME");
	}
}
