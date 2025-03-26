#include "LivesTextComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "LivesComponent.h"

dae::LivesTextComponent::LivesTextComponent(GameObject* gameObject):
	Component(gameObject)
{
}

void dae::LivesTextComponent::Start()
{
	m_TextComponent = GetGameObject()->GetComponent<TextComponent>();
}

void dae::LivesTextComponent::Notify(Event event, GameObject* gameObject)
{
	if (event.id == make_sdbm_hash("PlayerDied"))
	{
		int newLives = gameObject->GetComponent<LivesComponent>()->GetLives();
		m_TextComponent->ChangeText("Lives: " + std::to_string(newLives));
	}
	
}

