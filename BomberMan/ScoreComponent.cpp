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
	Event e(make_sdbm_hash("PlayerGainedScore"));
	m_pActorScoreEvent->NotifyObservers(e, GetGameObject());
}

void dae::ScoreComponent::Notify(Event event, GameObject* )
{
	if (event.id == make_sdbm_hash("KilledBalloom"))
	{
		m_CurrentScore += 100; // TODO: HARDCODED
	}

	else if (event.id == make_sdbm_hash("KilledOneal"))
	{
		m_CurrentScore += 200; // TODO: HARDCODED
	}

	else if (event.id == make_sdbm_hash("KilledDoll"))
	{
		m_CurrentScore += 400; // TODO: HARDCODED
	}

	else if (event.id == make_sdbm_hash("KilledMinvo"))
	{
		m_CurrentScore += 800; // TODO: HARDCODED
	}

	Event e(make_sdbm_hash("PlayerGainedScore"));
	m_pActorScoreEvent->NotifyObservers(e, GetGameObject());
}
