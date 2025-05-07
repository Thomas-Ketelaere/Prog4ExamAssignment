#include "ScoreComponent.h"
#include "Subject.h"

game::ScoreComponent::ScoreComponent(RamCoreEngine::GameObject* gameObject):
	Component(gameObject)
{
	m_pActorScoreEvent = std::make_unique<RamCoreEngine::Subject>();
}

void game::ScoreComponent::GainScore(int amount)
{
	m_CurrentScore += amount;
	Event e(make_sdbm_hash("PlayerGainedScore"));
	m_pActorScoreEvent->NotifyObservers(e, GetGameObject());
}

void game::ScoreComponent::Notify(Event event, RamCoreEngine::GameObject* )
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
