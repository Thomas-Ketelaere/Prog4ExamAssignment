#include "ScoreComponent.h"
#include "Subject.h"

dae::ScoreComponent::ScoreComponent(GameObject* gameObject):
	Component(gameObject)
{
	m_pActorScoreEvent = std::make_unique<Subject>();
}

void dae::ScoreComponent::GainScore(int amount)
{
	m_CurrentScore += amount;
	m_pActorScoreEvent->NotifyObservers(Event::PlayerGainedScore, GetGameObject());
}
