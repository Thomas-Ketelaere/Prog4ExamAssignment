#include "ScoreTextComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "ScoreComponent.h"

game::ScoreTextComponent::ScoreTextComponent(RamCoreEngine::GameObject* gameObject):
	Component(gameObject)
{
}

void game::ScoreTextComponent::Start()
{
	m_TextComponent = GetGameObject()->GetComponent<RamCoreEngine::TextComponent>();
}

void game::ScoreTextComponent::Notify(Event event, RamCoreEngine::GameObject* gameObject)
{
	if (event.id == make_sdbm_hash("PlayerGainedScore"))
	{
		int newScore = gameObject->GetComponent<ScoreComponent>()->GetCurrentScore();
		m_TextComponent->ChangeText("Current score: " + std::to_string(newScore));
	}
}
