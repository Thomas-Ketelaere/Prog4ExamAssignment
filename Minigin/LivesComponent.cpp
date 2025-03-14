#include "LivesComponent.h"
#include "Subject.h"


dae::LivesComponent::LivesComponent(GameObject* gameObject, int maxLives):
	Component(gameObject),
	m_CurrentLives{maxLives}
{
	m_pActorDiedEvent = std::make_unique<Subject>();
}

void dae::LivesComponent::LoseLive()
{
	--m_CurrentLives;
	m_pActorDiedEvent->NotifyObservers(Event::PlayerDied, GetGameObject());
}
