#include "ScoreTextComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "ScoreComponent.h"

dae::ScoreTextComponent::ScoreTextComponent(GameObject* gameObject):
	Component(gameObject)
{
}

void dae::ScoreTextComponent::Start()
{
	m_TextComponent = GetGameObject()->GetComponent<TextComponent>();
}

void dae::ScoreTextComponent::Notify(Event event, GameObject* gameObject)
{
	if (event == Event::PlayerGainedScore)
	{
		int newScore = gameObject->GetComponent<ScoreComponent>()->GetCurrentScore();
		m_TextComponent->ChangeText("Current score: " + std::to_string(newScore));
	}
}
